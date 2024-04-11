#include "middle/middle.h"

#include <wtypes.h> //for full_screen_size
void define_fullscreen(short& x, short& y){
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);
    x = desktop.right;
    y = desktop.bottom;
    //16 inch my pc
}
explorer();

void graphical_user_interface() // start of the menu this is
{
    //boot graphics
    short screen_x = 0, screen_y = 0;
    define_fulls    creen(screen_x, screen_y);
    if (screen_x == 0 || screen_y == 0)
        exit(1);
    initwindow(screen_x, screen_y, "", -3, -3);
    //background
    //3 menu buttons => explorer, info exemples, test string

    char* operation,* algorithm;
    short nr_paths = 0;
    char** paths_input = new char* [nr_input_paths];
    char* path_output = argv[argc - 2];
    char* output_name = argv[argc - 1];

    ///manipulate

    very_last_step(operation, algorithm, nr_paths, paths_input, path_output, output_name);
    closegraph();
}

