#pragma once
#include <wtypes.h>
#include <cstring>

#define nr_squares_x 19
#define nr_squares_y 12

struct point
{
    short x, y;
    point(): x(0), y(0){}
    point(short x, short y): x(x), y(y){}
    point(const char* mode)
    {
        RECT desktop;
        const HWND hDesktop = GetDesktopWindow();
        GetWindowRect(hDesktop, &desktop);
        point temp(desktop.right, desktop.bottom);
        if(strcmp(mode, "square_measure") == 0)
        {
            temp.x /= nr_squares_x;
            temp.y /= nr_squares_y;
        }

        if(strcmp(mode, "unit") == 0)
        {
            short unit = temp.y / nr_squares_y;
            while(unit > 10) unit /= 10;
            if(unit > 5) unit /= 2;
            temp.x = unit; temp.y = unit;
        }

        this->x = temp.x;
        this->y = temp.y;
    }

    void operator = (point random)
    {
        this->x = random.x;
        this->y = random.y;
    }

    void operator = (int value)
    {
        this->x = value;
        this->y = value;
    }
};
//measure - one block
//short unit;
