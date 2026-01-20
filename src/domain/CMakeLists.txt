# Creamos la librería estática 'domain'
add_library(domain STATIC 
    FlightLogic.cpp
)

# Definimos dónde están sus headers para que otros los encuentren
target_include_directories(domain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})