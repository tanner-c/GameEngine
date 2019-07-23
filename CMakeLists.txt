cmake_minimum_required(VERSION 3.15)
project(GameEngine)
list(APPEND CMAKE_MODULE_PATH "${GameEngine_SOURCE_DIR}/CMake")

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(WIN32)
    set(GLEW_USE_STATIC_LIBS ON)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)

if (NOT OPENGL_FOUND AND (NOT TARGET OpenGL::GL OR NOT OPENGL_INCLUDE_DIR))
    message(SEND_ERROR "IMPORTANT: OpenGL was unable to be located. Please ensure that OPENGL_opengl_LIBRARY and OPENGL_INCLUDE_DIR are set.")
endif()

if (NOT GLEW_FOUND AND (NOT TARGET GLEW::GLEW))
    if (WIN32)
        message(SEND_ERROR "IMPORTANT: GLEW was unable to be located. Please ensure that GLEW_INCLUDE_DIR and GLEW_STATIC_LIBRARY_* are set.")
    else()
        message(SEND_ERROR "IMPORTANT: GLEW was unable to be located. Please ensure that GLEW_INCLUDE_DIR and GLEW_SHARED_LIBRARY_* are set.")
    endif()
endif()

add_subdirectory(src)

file(GLOB_RECURSE ASSET_FILES assets/**/*)
source_group(Assets ${ASSET_FILES})