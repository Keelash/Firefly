cmake_minimum_required(VERSION 2.8)


#Project Configuration
set(targetName Firefly)
project(${targetName})

set(EXECUTABLE_OUTPUT_PATH ${PWD})
set(CMAKE_CXX_FLAGS "-std=c++0x")

#QT inclusion
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_USE_QTOPENGL TRUE)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

#GLM Inclusion
include_directories(lib/glm)

#ASSIMP Inclusion
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_SAMPLES OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)

add_subdirectory(lib/assimp-3.3.1)
include_directories(lib/assimp-3.3.1/include)

#OpenMesh Inclusion
set(DBUILD_APPS OFF)

add_subdirectory(lib/openMesh)
include_directories(lib/openMesh/src)

#find Shader File and copy it near the binary
file(GLOB SHDR shader/*)

file(MAKE_DIRECTORY shader)
file(COPY ${SHDR} DESTINATION shader)

#Find Source File
file(GLOB_RECURSE SRCS src/*)

add_executable(${targetName} ${SRCS} ${SHDR})

target_link_libraries(${targetName}
    assimp
    OpenMeshCore
    OpenMeshTools
)

QT5_USE_MODULES(${targetName} Widgets Declarative OpenGL)
