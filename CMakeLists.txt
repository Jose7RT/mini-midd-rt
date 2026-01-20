cmake_minimum_required(VERSION 3.20)
project(mini_middleware VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Buscar dependencias externas (CMakeDeps from conan will create config files)
find_package(Drogon CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# 2. Añadir nuestras sub-librerías (CMake buscará los archivos en esas carpetas)
add_subdirectory(src/domain)
add_subdirectory(src/application)
add_subdirectory(src/infrastructure)

# 3. Crear el ejecutable final
add_executable(rocket_backend src/main.cpp)

# 4. El "Gran Enlace"
# El ejecutable solo necesita 'conocer' a las capas superiores, 
# CMake se encarga de traer el resto por transitividad.
target_link_libraries(rocket_backend PRIVATE
    application
    infrastructure
    spdlog::spdlog
)

option(BUILD_TESTING "Build the testing suite" ON)

if(BUILD_TESTING)
    # 1. Activamos el motor de tests de CMake
    enable_testing()
    
    # 2. Buscamos GTest (Instalado vía Conan)
    find_package(GTest CONFIG REQUIRED)

    # 3. Creamos el ejecutable de pruebas
    add_executable(unit_tests tests/UnitTests.cpp)

    # 4. Enlazamos las librerías que queremos probar
    # IMPORTANTE: Enlazamos con GTest::gtest_main para que NO tengas que escribir un main() en el test
    target_link_libraries(unit_tests PRIVATE
        domain
        application
        GTest::gtest_main
    )

    # 5. Registramos el test para que aparezca en 'ctest'
    add_test(NAME BackendTests COMMAND unit_tests)
endif()
