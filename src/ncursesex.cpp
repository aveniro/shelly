//
// Created by Nathan Seymour on 28/03/2020.
//

#include <ncurses.h>
#include <cstring>
#include <chrono>
#include <thread>
#include "ncursesex.h"

void ncex::makebox(int y, int x, int height, int width, const char *title)
{
    mvaddch(y, x,'+');
    mvaddch(y, x + width, '+');
    mvaddch(y + height, x, '+');
    mvaddch(y + height, x + width, '+');

    // Top Line
    for(int cx = x + 1; cx < width + x; cx++)
    {
        mvaddch(y, cx,'-');
    }

    // Bottom Line
    for(int cx = x + 1; cx < width + x; cx++)
    {
        mvaddch(y + height, cx,'-');
    }

    // Left Line
    for(int cy = y + 1; cy < height + y; cy++)
    {
        mvaddch(cy, x, '|');
    }

    // Right Line
    for(int cy = y + 1; cy < height + y; cy++)
    {
        mvaddch(cy, x + width, '|');
    }

    mvaddstr(y, x + 1, title);
}

void ncex::slowprint(int y, int x, const char *text, double seconds)
{
    if(x == ncex::CENTER_ALIGN) x = (COLS/2) - (strlen(text)/2);

    int characters = strlen(text);
    for(int i = 0; i < characters; i++)
    {
        mvaddch(y, x + i, text[i]);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds((int)((seconds/(double)characters) * 1000)));
    }
}

void ncex::writestr(int y, int x, const char *text)
{
    if(x == ncex::CENTER_ALIGN) x = (COLS/2) - (strlen(text)/2);
    mvaddstr(y, x, text);
}
