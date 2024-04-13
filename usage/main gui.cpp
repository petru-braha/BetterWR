#include <graphics.h>
#include <wtypes.h>
#include "middle/middle.h"

void visual_menu(short unit_x, short unit_y);
void functional_menu();

void define_fullscreen(short& x, short& y){
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);
    x = desktop.right;
    y = desktop.bottom;
}

void graphical_user_interface() // menu
{
    //boot graphics
    short screen_x = 0, screen_y = 0;
    define_fullscreen(screen_x, screen_y);
    if (screen_x == 0 || screen_y == 0)
        exit(1);
    initwindow(screen_x, screen_y, "", -3, -3);
    readimagefile("constant files/media/layout/background.jpg", 0, 0, screen_x, screen_y);

    short unit_x = screen_x / 19, unit_y = screen_y / 12;
    visual_menu(unit_x, unit_y);
    functional_menu();
    closegraph();
}
