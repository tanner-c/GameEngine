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

source_group(Engine\\Assets FILES ${ENGINE_NS_ASSETS})
source_group(Engine\\Utilities FILES ${ENGINE_NS_UTILITIES})
source_group(Engine\\Graphics FILES ${ENGINE_NS_GRAPHICS})

add_library(engine STATIC ${ENGINE_NS_ASSETS} ${ENGINE_NS_UTILITIES} ${ENGINE_NS_GRAPHICS})

set_property(TARGET engine PROPERTY CXX_STANDARD 11)
set_property(TARGET engine PROPERTY CXX_STANDARD_REQUIRED ON)

set(ENGINE_LINK_LIBRARIES OpenGL::GL GLFW::GLFW glad)

if(APPLE)
  list(APPEND ENGINE_LINK_LIBRARIES "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()

target_link_libraries(engine ${ENGINE_LINK_LIBRARIES})

target_include_directories(engine PRIVATE .)
