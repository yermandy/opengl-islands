cmake_minimum_required(VERSION 3.15)
project(OpenGLworld)

set(CMAKE_CXX_STANDARD 20)

find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
find_library(assimp_LIBRARIES NAMES assimp)

set(
        ALL_LIBS
        glfw
        GLEW::glew
        glm
        ${assimp_LIBRARIES}
)


file(
        GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*/*/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*/*/*/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*/*/*/*/*.cpp
)

file(
        GLOB HEADERS
        ${PROJECT_SOURCE_DIR}/*.h
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/src/*/*.h
        ${PROJECT_SOURCE_DIR}/src/*/*/*.h
        ${PROJECT_SOURCE_DIR}/src/*/*/*/*.h
        ${PROJECT_SOURCE_DIR}/src/*/*/*/*/*.h
)

include_directories(src)

add_executable(Application ${SOURCES} ${HEADERS})

include_directories(${ASSIMP_INCLUDE_DIR})

target_link_libraries(Application ${ALL_LIBS})