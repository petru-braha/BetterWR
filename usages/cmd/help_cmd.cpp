#include "help_cmd.h"

void etern_gui()//all gui in one place
{
    short screen_x = 0, screen_y = 0;
    define_fullscreen(screen_x, screen_y);
    if(screen_x==0 || screen_y==0)
        exit(1);

    initwindow(screen_x, screen_y, "", -3, -3);
    start_graphics(1);
    graphics_MENUbuttons();
    commands();
    closegraph();
}
