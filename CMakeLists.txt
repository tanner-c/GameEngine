cmake_minimum_required(VERSION 3.15)
project(GameEngine)
list(APPEND CMAKE_MODULE_PATH "${GameEngine_SOURCE_DIR}/CMake")

set(GAME_ASSETS_DIR "${GameEngine_SOURCE_DIR}/assets" CACHE PATH "Path to the game assets directory")
set(GAME_ASSETS_MANIFEST "${GAME_ASSETS_DIR}/manifest" CACHE FILEPATH "Path to the game assets manifest")

file(GLOB_RECURSE GAME_ASSETS_SHADERS "${GAME_ASSETS_DIR}/shaders/*")
file(GLOB_RECURSE GAME_ASSETS_MESHES "${GAME_ASSETS_DIR}/meshes/*")

set(COMAND_COPY_ASSETS "${CMAKE_COMMAND} -E copy_directory ${GAME_ASSETS_DIR} ${GAME_BINARY_DIR}/assets")

find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)

add_subdirectory(deps)
add_subdirectory(src)

get_property(GAME_BINARY_DIR TARGET game PROPERTY BINARY_DIR)
source_group(shaders FILES ${GAME_ASSETS_SHADERS})
source_group(meshes FILES ${GAME_ASSETS_MESHES})

add_custom_target(assets SOURCES ${GAME_ASSETS_MANIFEST} ${GAME_ASSETS_SHADERS} ${GAME_ASSETS_MESHES})


