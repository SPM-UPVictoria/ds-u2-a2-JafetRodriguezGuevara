cmake_minimum_required(VERSION 3.10)
project(SistemaMensajeria VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directorios de headers
include_directories(include)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/Ciudad.cpp
    src/Ruta.cpp
    src/Paquete.cpp
    src/GestorRutas.cpp
    src/GestorPaquetes.cpp
    src/SistemaMensajeria.cpp
)

# Ejecutable
add_executable(SistemaMensajeria ${SOURCES})

# Opciones de compilacion
target_compile_options(SistemaMensajeria PRIVATE -Wall -Wextra)

message(STATUS "Proyecto configurado: SistemaMensajeria v${PROJECT_VERSION}")
