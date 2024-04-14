#include <graphics.h>
#include "middle/middle.h"

struct point
{
    short x, y;
};

void define_fullscreen(short& x, short& y);
void visual_menu(point measure, short unit);
void functional_menu(point measure, short unit);

void graphical_user_interface()
{
    //boot graphics
    point screen;
    define_fullscreen(screen.x, screen.y);
    initwindow(screen.x, screen.y, "", -3, -3);
    readimagefile("constant files/media/layout/background.jpg", 0, 0, screen.x, screen.y);

    point measure; measure.x = screen.x / 19; measure.y = screen.y / 12;

    short unit = measure.y;
    while(unit > 10)
        unit /= 10;
    if(unit > 5) unit /= 2;

    visual_menu(measure, unit);
    functional_menu(measure, unit);
    closegraph();
}
