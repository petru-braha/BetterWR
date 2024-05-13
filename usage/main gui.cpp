#include <graphics.h>
#include "middle/middle.h"

#include "gui/point.h"
void visual_menu(point measure, short unit);
void functional_menu(point measure, short unit);

void graphical_user_interface()
{
    point screen("fullscreen");
    initwindow(screen.x, screen.y, "", -3, -3);
    readimagefile("constant files/media/layout/background.jpg", 0, 0, screen.x, screen.y);

    point measure("square_measure");
    point unit("unit");

    visual_menu(measure, unit.x);
    functional_menu(measure, unit.x);
    closegraph();
}
