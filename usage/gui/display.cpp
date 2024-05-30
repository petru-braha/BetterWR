#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <graphics.h>
#include <filesystem>
#include "constants.h"
#include "../middle/middle.h"
#include "../../admin/pack.h"

void print_box(short x1, short y1, short x2, short y2, const char* text, short unit, int color, int text_size)
{
    setcolor(color);
    settextstyle(text_font, HORIZ_DIR, text_size);

    setfillstyle(SOLID_FILL, color_light_cyan);
    bar(x1, y1, x2, y2);
    setfillstyle(SOLID_FILL, color_light_blue);
    bar(x1 + unit, y1 + unit, x2 - unit, y2 - unit); unit*=2;
    setfillstyle(SOLID_FILL, color_black);
    bar(x1 + unit, y1 + unit, x2 - unit, y2 - unit); unit*=2;
    outtextxy(x1 + unit, y1 + unit, (char*)text);
}

void visual_menu_explorer(point measure, short unit) // called just when "stored files" is pressed
{
    point screen("fullscreen");
    readimagefile("constant files/media/layout/background.jpg", 0, 0, screen.x, screen.y);
    //readimagefile("constant files/media/layout/explorer layout.jpg", 0, 0, screen.x, screen.y);

    setcolor(color_brown);
    settextstyle(text_font, HORIZ_DIR, expl_font_size);
    B_OPTN->visual(unit);
    B_ALGO->visual(unit);

    //print_box(2*measure.x, 3*measure.y, 7*measure.x, 11*measure.y, "files", unit, color_brown, expl_font_size);
    //print_box(8*measure.x, 3*measure.y, 13*measure.x, 11*measure.y, "files", unit, color_brown, expl_font_size);
    print_box(13*measure.x, 3*measure.y, 18*measure.x, 11*measure.y, "", unit, 0, 0);
    //print_box(12*measure.x, 5*measure.y, 18*measure.x, 11*measure.y, "status box:", unit, color_dark_gray, menu_font_size - 3);

    B_STOP->visual(unit);
    B_BACK_MENU->visual(unit);
    B_BACK_EXPL->visual(unit);
    setcolor(color_white);
    B_SLCT->visual(unit);
    B_ACTN->visual(unit);
}

#include "functional_help.h"
void functional_menu_explorer(point measure, short unit)
{
    for(size_t i = 0; i < max_nr_paths_selectedd; i++)
        selected_files[i] = nullptr;
    point mouse;
    std::string accessed_path = "";

    std::string status = ""; // if status != "" => a dir has been accessed
    screen_path* pressedd_file = nullptr;
    display_paths(measure, unit, ""); // partitions

    bool condition = false;
    while(condition == false) // when true back to menu
    {
        // global
        getmouseclick(outside_left_click, (int&)mouse.x, (int&)mouse.y);
        if(mouse.x == -1)
            getmouseclick(outside_double_click, (int&)mouse.x, (int&)mouse.y);

        B_STOP->functional(mouse, unit);
        B_OPTN->functional(mouse, unit);
        B_ALGO->functional(mouse, unit);

        // back
        if(accessed_path == "")
            condition = B_BACK_MENU->functional(mouse, unit);
        else if(B_BACK_EXPL->functional(mouse, unit))
        {
            delete_dir_accessed(accessed_path);
            display_paths(measure, unit, accessed_path);
        }

        // path manipulation / execution
        path_manipulation(mouse, measure, unit, pressedd_file, accessed_path, status);

        // select
        if(pressedd_file && B_SLCT->functional(mouse, unit))
        {
            add_to_selected_files(pressedd_file, accessed_path);
            for(size_t i = 0; selected_files[i]; i++)
                selected_files[i]->visual();
            pressedd_file->visual();
            pressedd_file->selected = false;
            pressedd_file = nullptr;
        }

        visual_delete_selected(mouse, measure, unit);

        if(B_ACTN->functional(mouse, unit))
            action_button(measure, unit, condition);
    }

    for(size_t i = 0; explorer_files[i]; i++)
        delete explorer_files[i];
    for(size_t i = 0; selected_files[i]; i++)
        delete selected_files[i];
}

///menu
void visual_menu(point measure, short unit)
{
    //background
    point screen("fullscreen");
    readimagefile("constant files/media/layout/background.jpg", 0, 0, screen.x, screen.y);
    //readimagefile("constant files/media/layout/menu layout.jpg", 0, 0, screen.x, screen.y);

    //title
    print_box(5*measure.x, 2*measure.y, 15*measure.x, 3*measure.y, "*data compression app1*", unit, color_white, menu_font_size);

    //buttons
    settextstyle(text_font, HORIZ_DIR, menu_font_size);
    b_set_values(measure);
    setcolor(color_white);
    B_EXPL->visual(unit);
    B_INFO->visual(unit);
    B_TEST->visual(unit);
    B_STOP->visual(unit);
}

void functional_menu(point measure, short unit)
{
    point mouse;
    short menu_decision = -1;
    while(true)
    {
        //menu decision
        button* menu_buttons[4] = {B_STOP, B_EXPL, B_INFO, B_TEST};
        while(menu_decision == -1)
        {
            getmouseclick(outside_left_click, (int&)mouse.x, (int&)mouse.y);
            for(int i=0; i<4; i++)
                if(menu_buttons[i]->functional(mouse, unit))
                    menu_decision = i;
        }

        switch(menu_decision)
        {
        case 1:
            visual_menu_explorer(measure, unit);
            functional_menu_explorer(measure, unit);
            break;
        case 2:
            //visual_menu_info();
            break;
        case 3:
            //visual_menu_test();
            break;
        default:
            break;
        }

        visual_menu(measure, unit);
        menu_decision = -1;
    }
}
