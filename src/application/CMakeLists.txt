add_library(application STATIC 
    TelemetryManager.cpp
)

target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Linkamos spdlog como PRIVATE porque solo lo usamos en el .cpp
# Linkamos domain como PUBLIC porque el Manager expone tipos de Domain en su .hpp
target_link_libraries(application 
    PUBLIC 
        domain
    PRIVATE 
        spdlog::spdlog
)