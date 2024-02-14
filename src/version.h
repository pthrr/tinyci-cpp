#pragma once

#include <string>
#include <string_view>

#include <fmt/core.h>

#include "types.h"

namespace version {

static constexpr i8 PROJECT_VERSION_MAJOR{ 0 };
static constexpr i8 PROJECT_VERSION_MINOR{ 1 };
static constexpr i8 PROJECT_VERSION_PATCH{ 0 };

struct Version
{
    i8 major = -1;
    i8 minor = -1;
    i8 patch = -1;
};

static constexpr Version PROJECT_VERSION{
    PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH };

#ifdef NDEBUG
static constexpr bool IS_DEBUG = false;
#else
static constexpr bool IS_DEBUG = true;
#endif

static constexpr std::string_view BUILD_VERSION{ "<COMMIT_SHA>" };
static constexpr std::string_view BUILD_TYPE{ IS_DEBUG ? "DEBUG" : "RELEASE" };

auto getVersionInfo() -> std::string
{
    return fmt::format( "{}.{}.{}", PROJECT_VERSION.major, PROJECT_VERSION.minor, PROJECT_VERSION.patch );
}

auto getBuildInfo() -> std::string
{
    std::string version{ BUILD_VERSION };
    std::string type{ BUILD_TYPE };

    if( version == "<COMMIT_SHA>" or version.empty() ) {
        return type;
    }

    return fmt::format( "{}-{}", version, type );
}

} // namespace version
