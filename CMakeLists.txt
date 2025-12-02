cmake_minimum_required(VERSION 3.20)
project(mini_middleware VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Conan generated toolchain + find modules are used (conan install will create these)
# Create executable
add_executable(backend src/main.cpp)

# Find packages (CMakeDeps from conan will create config files)
find_package(Drogon CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(backend PRIVATE
    Drogon::Drogon
    spdlog::spdlog
    nlohmann_json::nlohmann_json
)

# Simple install target
install(TARGETS backend DESTINATION bin)
