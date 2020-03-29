//
// Created by Nathan Seymour on 27/03/2020.
//

#ifndef SHELLY_SCREEN_MAIN_H
#define SHELLY_SCREEN_MAIN_H

#include "game_screen.h"

class screen_main : public game_screen {
public:
    void initialize() override;
    void draw() override;

    using game_screen::game_screen;
};

#endif //SHELLY_SCREEN_MAIN_H
