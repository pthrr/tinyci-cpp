#include <exception>
#include <fstream>
#include <string>
#include <thread>

#include <CLI/CLI.hpp>
#include <drogon/drogon.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "types.h"
#include "version.h"

auto main( int argc, char** argv ) -> int
{
    CLI::App app{ "My awesome CLI app" };

    bool debug{ false };
    app.add_flag( "-d,--debug", debug, "Enable debug mode" );

    std::string config{ "config.txt" };
    app.add_option( "-c,--config", config, "Path to the config file" );

    CLI11_PARSE( app, argc, argv );

    spdlog::level::level_enum log_level{ spdlog::level::info };

    if( debug ) {
        log_level = spdlog::level::debug;
    }

    std::ifstream file{ config };
    nlohmann::json json_config{};
    std::string app_name{};
    std::string log_path{};
    std::string ip_address{};
    u64 port{};
    const auto num_threads{ std::thread::hardware_concurrency() };

    try {
        file >> json_config;
        app_name = json_config["app"]["name"].get< std::string >();
        log_path = json_config["app"]["log_path"].get< std::string >();
        ip_address = json_config["app"]["ip_address"].get< std::string >();
        port = json_config["app"]["port"].get< u64 >();
    }
    catch( const nlohmann::json::exception& err ) {
        SPDLOG_ERROR( "Error parsing config: {}", err.what() );
        return 1;
    }

    spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] [%s:%#] %v" );
    spdlog::set_level( log_level );
    SPDLOG_INFO( "Starting {} v{} ..", app_name, version::getVersionInfo() );
    drogon::app()
        .setLogPath( log_path )
        .setLogLevel( debug ? trantor::Logger::kDebug : trantor::Logger::kInfo )
        .addListener( ip_address, port )
        .setThreadNum( not static_cast< bool >( num_threads ) ? num_threads : 1 )
        .run();
    SPDLOG_INFO( "Done." );
    return 0;
}
