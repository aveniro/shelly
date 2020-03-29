//
// Created by Nathan Seymour on 28/03/2020.
//

#ifndef SHELLY_NCURSESEX_H
#define SHELLY_NCURSESEX_H

namespace ncex {
    enum {
        CENTER_ALIGN = -1
    };

    void makebox(int y, int x, int height, int width, const char* title = "");
    void slowprint(int y, int x, const char* text, double seconds = 2);
    void writestr(int y, int x, const char* text);
}

#endif //SHELLY_NCURSESEX_H
