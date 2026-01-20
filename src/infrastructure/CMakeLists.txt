# src/infrastructure/CMakeLists.txt
add_library(infrastructure STATIC 
    RocketSimulator.cpp
    WebStreamController.cpp
)

target_include_directories(infrastructure PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(infrastructure 
    PUBLIC 
        application  # Necesita TelemetryManager.hpp
        Drogon::Drogon
    PRIVATE 
        spdlog::spdlog
)