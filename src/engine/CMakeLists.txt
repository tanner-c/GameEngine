set(ENGINE_NS_ASSETS
        asset.h
        assetmanager.cpp
        assetmanager.h
        mesh.cpp
        mesh.h
        shaderprogram.cpp
        shaderprogram.h
        CACHE INTERNAL "All files under Engine::Assets namespace")

set(ENGINE_NS_UTILITIES
        io.cpp
        io.h
        CACHE INTERNAL "All files under Engine::Utilities namespace")

set(ENGINE_NS_GRAPHICS
        shader.cpp
        shader.h
        windowmanager.cpp
        windowmanager.h
        gfxpipeline.cpp
        gfxpipeline.h
        CACHE INTERNAL "All files under Engine::Graphics namespace")

source_group(Source\\Engine\\Assets ${ENGINE_NS_ASSETS})
source_group(Source\\Engine\\Utilities ${ENGINE_NS_UTILITIES})
source_group(Source\\Engine\\Graphics ${ENGINE_NS_GRAPHICS})

add_library(engine STATIC ${ENGINE_NS_ASSETS} ${ENGINE_NS_UTILITIES} ${ENGINE_NS_GRAPHICS})

set_property(TARGET engine PROPERTY CXX_STANDARD 11)
set_property(TARGET engine PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(engine OpenGL::GL GLFW::GLFW)
target_include_directories(engine PRIVATE .)

if (WIN32)
    target_link_libraries(engine GLEW::glew_s)
    add_compile_definitions(GLEW_STATIC)
else()
    target_link_libraries(engine GLEW::glew)
endif()

