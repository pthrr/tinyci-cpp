import shutil
import os
import json

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain


class Project(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "catch2/3.4.0",
        "spdlog/1.12.0",
        "nlohmann_json/3.11.3",
        "cli11/2.3.2",
        "drogon/1.9.3",
        "sqlite3/3.45.1",
        "fmt/10.1.1",
    ]
    default_options = {
        "boost/*:without_locale": True,
        "boost/*:without_stacktrace_addr2line": True,
        "boost/*:without_stacktrace_backtrace": True,
    }
    generators = "CMakeDeps"

    def generate(self) -> None:
        ninja_available: bool = shutil.which("ninja") is not None
        generator = "Ninja" if ninja_available else None
        tc = CMakeToolchain(self, generator=generator)
        tc.generate()
        self.patch_cmake_presets()

    def patch_cmake_presets(self):
        cmake_presets_path = os.path.join(self.recipe_folder, "CMakePresets.json")
        presets = json.dumps(
            {
                "version": 6,
                "include": [
                    f"build/{self.settings.build_type}/generators/CMakePresets.json"
                ],
            }
        )

        with open(cmake_presets_path, "w") as presets_file:
            presets_file.write(presets)

    def layout(self) -> None:
        self.folders.source = "src"
        self.folders.build = f"build/{self.settings.build_type}"
        self.folders.generators = f"build/{self.settings.build_type}/generators"

    def build(self) -> None:
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
