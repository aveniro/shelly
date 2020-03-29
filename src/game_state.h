//
// Created by Nathan Seymour on 28/03/2020.
//

#ifndef SHELLY_GAME_STATE_H
#define SHELLY_GAME_STATE_H

#include <mutex>
#include <queue>
#include "player/player.h"

typedef struct {
    const int min_cols = 35;
    const int min_rows = 140;

    std::mutex m_current_player;
    std::shared_ptr<player> current_player;

    std::mutex m_update_notifier;
    std::condition_variable update_notifier;

    std::atomic<bool> game_running = true;

    std::queue<char> character_queue;
    std::mutex m_keypress_notifier;
    std::condition_variable keypress_notifier;
} game_state;

#endif //SHELLY_GAME_STATE_H
