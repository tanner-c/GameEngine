cmake_minimum_required(VERSION 3.15)
project(GameEngine)
list(APPEND CMAKE_MODULE_PATH "${GameEngine_SOURCE_DIR}/CMake")

set(GAME_ASSET_COPY OFF CACHE BOOL "Copy assets to game directory upon build")
set(GAME_ASSETS_DIR "${GameEngine_SOURCE_DIR}/assets" CACHE PATH "Path to the game assets directory")
set(GAME_ASSETS_MANIFEST "${GAME_ASSETS_DIR}/manifest" CACHE FILEPATH "Path to the game assets manifest")

file(GLOB_RECURSE GAME_ASSETS_SHADERS "${GAME_ASSETS_DIR}/shaders/*")

set(COMAND_COPY_ASSETS "${CMAKE_COMMAND} -E copy_directory ${GAME_ASSETS_DIR} ${GAME_BINARY_DIR}/assets")

if(WIN32)
    set(GLEW_USE_STATIC_LIBS ON)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)

add_subdirectory(src)

get_property(GAME_BINARY_DIR TARGET game PROPERTY BINARY_DIR)
source_group(shaders FILES ${ASSETS_SHADERS})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(GAME_ASSETS_COPY ON)
endif()

if(GAME_ASSETS_COPY)
    add_custom_target(assets ALL SOURCES ${GAME_ASSETS_MANIFEST} ${GAME_ASSETS_SHADERS})
else()
    add_custom_target(assets ALL SOURCES ${GAME_ASSETS_MANIFEST} ${GAME_ASSETS_SHADERS} COMMAND ${COMMAND_COPY_ASSETS})
endif()