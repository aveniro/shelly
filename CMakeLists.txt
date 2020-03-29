cmake_minimum_required(VERSION 3.15)
project(shelly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g")

include_directories(lib/mariadbpp/include)

add_subdirectory(lib/mariadbpp)

add_executable(shelly src/main.cpp src/player/player.cpp src/player/player.h src/game_manager.cpp src/game_manager.h src/shelly.h src/screens/game_screen.cpp src/screens/game_screen.h src/screens/screen_main.cpp src/screens/screen_main.h src/game_state.cpp src/game_state.h src/ncursesex.cpp src/ncursesex.h src/game_state.h)

target_link_libraries(shelly mariadbclientpp ncurses)
