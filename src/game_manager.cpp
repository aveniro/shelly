//
// Created by Nathan Seymour on 25/03/2020.
//

#include "game_manager.h"
#include "shelly.h"
#include <iostream>
#include <exception>
#include <ncurses.h>
#include <cstdio>

void run_gui(std::shared_ptr<game_screen>& current_game_screen, std::mutex& m_current_game_screen, game_state& state, std::mutex& m_state)
{
    // Initialize screen
    initscr();
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    clear();

    refresh();

    bool fully_initialized = false;
    do
    {
        std::unique_lock<std::mutex> lock_update(state.m_update_notifier);

        if(!fully_initialized)
        {
            fully_initialized = true;
            state.update_notifier.notify_one();
        }

        {
            std::lock_guard<std::mutex> lock_screen(m_current_game_screen);

            if (current_game_screen != nullptr)
            {
                if (!current_game_screen->initialized.load())
                {
                    current_game_screen->initialize();
                }

                current_game_screen->draw();
            } else {
                mvaddstr(0, 0, "No screen is currently loaded...");
                refresh();
            }
        }

        state.update_notifier.wait(lock_update);
    } while(state.game_running.load());

    endwin();
}

void keyboard_input(game_state& state, std::mutex& m_state)
{
    do
    {
        char character = getchar();

        {
            std::lock_guard<std::mutex> lock(state.m_keypress_notifier);
            state.character_queue.push(character);
        }
        state.keypress_notifier.notify_all();
    } while(state.game_running.load());
}

game_manager::~game_manager()
{
    {
        std::lock_guard<std::mutex> lock(this->state.m_update_notifier);
        this->state.game_running = false;
    }
    this->state.update_notifier.notify_all();

    if(this->gui_thread.joinable()) this->gui_thread.join();
    if(this->comm_thread.joinable()) this->comm_thread.join();

    std::cout << "Press the enter key to exit..." << std::endl;
    if(this->input_thread.joinable()) this->input_thread.join();
}

game_manager::game_manager()
{
    try {
        this->db_account = mariadb::account::create(DB_HOST_NAME, DB_USER_NAME, DB_PASSWORD, DB_DATABASE);
        this->db_connection = mariadb::connection::create(this->db_account);
    }
    catch(std::exception& e)
    {
        std::cerr << "The game_manager could not successfully instantiate a database connection" << std::endl;
        std::cerr << e.what() << std::endl;

        std::terminate();
    }

    // Start gui
    this->gui_thread = std::thread(run_gui,
            std::ref(this->current_game_screen),
            std::ref(this->m_current_game_screen),
            std::ref(this->state),
            std::ref(this->m_state));

    // Wait for the full initialization of the GUI thread before continuing
    std::unique_lock<std::mutex> lock(this->state.m_update_notifier);
    this->state.update_notifier.wait(lock);

    // Start input thread
    this->input_thread = std::thread(keyboard_input,
            std::ref(this->state),
            std::ref(this->m_state));
}

void game_manager::set_screen(std::shared_ptr<game_screen> screen)
{
    std::lock_guard<std::mutex> lock_screen(this->m_current_game_screen);

    this->current_game_screen = screen;

    std::lock_guard<std::mutex> lock_update(this->state.m_update_notifier);
    this->state.update_notifier.notify_all();
}

void game_manager::wait_for_screen_init()
{
    if(this->current_game_screen == nullptr) return;
    if(this->current_game_screen->initialized.load()) return;

    std::unique_lock<std::mutex> lock(this->current_game_screen->m_initialize_notifier);
    this->current_game_screen->initialize_notifier.wait(lock);
}

void game_manager::wait_for_keypress()
{
    std::unique_lock<std::mutex> lock(this->state.m_keypress_notifier);
    this->state.keypress_notifier.wait(lock);
}

void game_manager::clear_key_buffer()
{
    int size = this->state.character_queue.size();
    for(int i = 0; i < size; i++) this->state.character_queue.pop();
}

void game_manager::wait_for_key(char key)
{
    this->clear_key_buffer();

    do
    {
        std::unique_lock<std::mutex> lock(this->state.m_keypress_notifier);
        this->state.keypress_notifier.wait(lock);
    } while(this->state.character_queue.front() != key);
}
