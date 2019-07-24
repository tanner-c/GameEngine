set(GAME_NS_GAME
        app.cpp
        app.h
        main.cpp
        CACHE INTERNAL "Files under Game:: namespace")

source_group(Game FILES ${GAME_NS_GAME})

add_executable(game ${GAME_NS_GAME})
target_link_libraries(game engine)

target_include_directories(game PRIVATE .)

set_property(TARGET game PROPERTY CXX_STANDARD 11)
set_property(TARGET game PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET game PROPERTY VS_DEBUGGER_COMMAND_ARGUMENTS "--assets_dir ${GAME_ASSETS_DIR}")