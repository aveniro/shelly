//
// Created by Nathan Seymour on 27/03/2020.
//

#include <ncurses.h>
#include "../ncursesex.h"
#include "screen_main.h"

void screen_main::initialize()
{
    clear();

    curs_set(1);
    int y = 10;
    ncex::slowprint(y++, ncex::CENTER_ALIGN, "  /$$$$$$  /$$   /$$ /$$$$$$$$ /$$       /$$   /$$     /$$ ", 0.2);
    ncex::slowprint(y++, ncex::CENTER_ALIGN, " /$$__  $$| $$  | $$| $$_____/| $$      | $$  |  $$   /$$/ ", 0.2);
    ncex::slowprint(y++, ncex::CENTER_ALIGN, "| $$  \\__/| $$  | $$| $$      | $$      | $$   \\  $$ /$$/ ", 0.2);
    ncex::slowprint(y++, ncex::CENTER_ALIGN, "|  $$$$$$ | $$$$$$$$| $$$$$   | $$      | $$    \\  $$$$/  ", 0.2);
    ncex::slowprint(y++, ncex::CENTER_ALIGN, " \\____  $$| $$__  $$| $$__/   | $$      | $$     \\  $$/   ", 0.2);
    ncex::slowprint(y++, ncex::CENTER_ALIGN, " /$$  \\ $$| $$  | $$| $$      | $$      | $$      | $$    ", 0.2);
    ncex::slowprint(y++, ncex::CENTER_ALIGN, "|  $$$$$$/| $$  | $$| $$$$$$$$| $$$$$$$$| $$$$$$$$| $$     ", 0.2);
    ncex::slowprint(y, ncex::CENTER_ALIGN, " \\______/ |__/  |__/|________/|________/|________/|__/    ", 0.2);

    curs_set(0);
    ncex::writestr(LINES - 10, ncex::CENTER_ALIGN, "Press any key to continue...");

    this->post_init();
}

void screen_main::draw()
{
    this->post_draw();
}