# Dependencias
```sh
sudo apt install clang
clang --version
Ubuntu clang version 18.1.3 (1ubuntu1)

sudo apt install cmake
cmake --version
cmake version 3.28.1

pipx install conan
conan --version
Conan version 2.23.0
```


# Build local (conan + cmake)
```sh
# 1) Crear carpeta build
mkdir -p build/release

# 2) Instalar dependencias con Conan v2
#    Esto generará toolchain, CMakeDeps y scripts de entorno
conan install . --profile=gcc20 --build=missing -of build/release

# 3) Configurar CMake (conan generará la toolchain automáticamente)
cmake --preset conan-release

# 4) Compilar
cmake --build --preset conan-release
```


# Probar el backend localmente
Ejecuta desde mini-middleware/backend/build:
```sh
./build/release/rocket_backend
```

Prueba en terminal:
```sh
wscat -c ws://localhost:8080/telemetry
```