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

void start_graphics(){
    short width = 0, height = 0;
    define_fullscreen(width, height);

    readimagefile("photos/1.jpg", 0, 0, width, height);

    setcolor(9);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(1000, 200, "Algorithms:");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(1050, 250, "-Huffman trees");
    outtextxy(1050, 270, "-Lempel-Ziv-Welch");

    //display stop and menu buttons
    x/*
    stop_button.visual_appearance();
    compress_button.visual_appearance();
    decompress_button.visual_appearance();
    more_info_button.visual_appearance();
    test_button.visual_appearance();
    */
}


void graphical_user_interface()
{
    //boot graphics
    short screen_x = 0, screen_y = 0;
    define_fulls    creen(screen_x, screen_y);
    if (screen_x == 0 || screen_y == 0)
        exit(1);
    initwindow(screen_x, screen_y, "", -3, -3);
    start_graphics(1);

    char* operation,* algorithm;
    short nr_paths = 0;
    char** paths_input = new char* [nr_input_paths];
    char* path_output = argv[argc - 2];
    char* output_name = argv[argc - 1];

    ///manipulate

    very_last_step(operation, algorithm, nr_paths, paths_input, path_output, output_name);
    closegraph();
}

