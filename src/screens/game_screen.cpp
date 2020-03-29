//
// Created by Nathan Seymour on 25/03/2020.
//

#include "game_screen.h"

void game_screen::post_init()
{
    refresh();
    this->initialized = true;

    {
        std::lock_guard<std::mutex> lock(this->m_initialize_notifier);
    }
    this->initialize_notifier.notify_all();
}

void game_screen::post_draw()
{
    refresh();

    {
        std::lock_guard<std::mutex> lock(this->m_draw_notifier);
    }
    this->draw_notifier.notify_all();
}