#include <iostream>
#include "game_manager.h"
#include "screens/screen_main.h"

int main(int argc, char** argv)
{
    auto game = std::make_shared<game_manager>();
    auto start_screen = std::make_shared<screen_main>(std::ref(game->state));

    game->set_screen(start_screen);

    game->wait_for_screen_init();
    game->wait_for_keypress();

    return 0;
}
