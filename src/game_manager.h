//
// Created by Nathan Seymour on 25/03/2020.
//

#ifndef SHELLY_GAME_MANAGER_H
#define SHELLY_GAME_MANAGER_H

#include <mariadb++/connection.hpp>
#include <thread>
#include <queue>
#include "game_state.h"
#include "screens/game_screen.h"
#include "player/player.h"

void run_gui(std::shared_ptr<game_screen>& current_game_screen, std::mutex& m_current_game_screen, game_state& state, std::mutex& m_state);
void keyboard_input(game_state& state, std::mutex& m_state);

class game_manager {
private:
    mariadb::account_ref db_account;
    mariadb::connection_ref db_connection;

    std::mutex m_current_game_screen;
    std::shared_ptr<game_screen> current_game_screen;

    std::thread gui_thread;
    std::thread comm_thread;
    std::thread input_thread;
public:
    void set_screen(std::shared_ptr<game_screen> screen);

    void clear_key_buffer();

    void wait_for_screen_init();
    void wait_for_keypress();

    void wait_for_key(char key);

    std::mutex m_state;
    game_state state;

    game_manager();
    ~game_manager();
};

#endif //SHELLY_GAME_MANAGER_H
