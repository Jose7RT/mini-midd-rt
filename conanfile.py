from conan import ConanFile

class MiniMiddlewareConan(ConanFile):
    name = "mini-middleware"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    requires = (
        "drogon/1.9.0",
        "spdlog/1.12.0",
        "nlohmann_json/3.11.2",
        "gtest/1.13.0"
    )
    generators = "CMakeDeps", "CMakeToolchain"
    default_options = {}