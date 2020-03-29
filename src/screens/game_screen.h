//
// Created by Nathan Seymour on 25/03/2020.
//

#ifndef SHELLY_GAME_SCREEN_H
#define SHELLY_GAME_SCREEN_H

#include <memory>
#include <ncurses.h>
#include "../game_state.h"

class game_screen {
protected:
    game_state& state;

    void post_init();
    void post_draw();

public:
    std::mutex m_initialize_notifier;
    std::condition_variable initialize_notifier;

    std::mutex m_draw_notifier;
    std::condition_variable draw_notifier;

    std::atomic<bool> initialized = false;

    virtual void initialize() {};
    virtual void draw() {};

    explicit game_screen(game_state& state) : state(state) {};
};

#endif //SHELLY_GAME_SCREEN_H
