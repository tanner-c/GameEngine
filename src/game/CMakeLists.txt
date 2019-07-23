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

add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets
                ${CMAKE_CURRENT_BINARY_DIR}/assets
        )