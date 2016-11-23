cmake_minimum_required(VERSION 2.8)


#Project Configuration
project(Firefly)

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
include_directories(lib/assimp-3.3.1/include)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_SAMPLES OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)

add_subdirectory(lib/assimp-3.3.1)

#find Shader File and copy it near the binary
file(GLOB SHDR shader/*)

file(MAKE_DIRECTORY shader)
file(COPY ${SHDR} DESTINATION shader)


#Find Source File
file(GLOB_RECURSE SRCS src/*)



add_executable(firefly	${SRCS} ${SHDR})

target_link_libraries(firefly assimp)

QT5_USE_MODULES(firefly Widgets Declarative OpenGL)
