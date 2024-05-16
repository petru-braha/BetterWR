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

void display_paths(point measure, short unit, std::string accessed_path)
{
    //delete visual
    print_box(2*measure.x, 3*measure.y, 13*measure.x, 11*measure.y, "", unit, color_black, 0);
    //delete functional
    for(size_t i = 0 ; i < max_nr_paths_displayed; i++)
    {
        delete explorer_files[i];
        explorer_files[i] = nullptr;
    }

    size_t index = 0;
    if(accessed_path == "") // display volumes
    {
        std::vector<std::string> drives = list_volumes();
        for(std::string current : drives)
        {
            screen_path* previous = (index == 0 ? nullptr : explorer_files[index - 1]);
            explorer_files[index] = new screen_path(previous, (char*)current.c_str());
            explorer_files[index]->visual();
            index++;
        }

        print_box(2*measure.x, 2*measure.y, 18*measure.x, 3*measure.y, accessed_path.c_str(), unit, color_brown, expl_font_size);
        settextstyle(text_font, HORIZ_DIR, expl_font_size);
        return;
    }

    for(auto & p : std::filesystem::directory_iterator(accessed_path))
    {
        char s[MAX] = "\0";
        strcpy(s, p.path().string().c_str()); std::string temp = get_file_name(s);
        strcpy(s, temp.c_str());
        if(std::filesystem::is_directory(p.path()))
           strcat(s, "/\0");

        screen_path* previous = index == 0 ? nullptr : explorer_files[index-1];
        explorer_files[index] = new screen_path(previous, s);
        explorer_files[index]->visual();
        index++;

        if(index == max_nr_paths_displayed)
            break;
    }
    print_box(2*measure.x, 2*measure.y, 18*measure.x, 3*measure.y, accessed_path.c_str(), unit, color_brown, expl_font_size);
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

    //print_box(10*measure.x, measure.y, 11*measure.x, 2*measure.y, "sel", unit, color_brown, expl_font_size);
    print_box(11*measure.x, measure.y, 12*measure.x, 2*measure.y, "mkd", unit, color_brown, expl_font_size);
    print_box(12*measure.x, measure.y, 13*measure.x, 2*measure.y, "del", unit, color_brown, expl_font_size);
    print_box(14*measure.x, measure.y, 15*measure.x, 2*measure.y, "fpn", unit, color_brown, expl_font_size);

    //print_box(2*measure.x, 3*measure.y, 7*measure.x, 11*measure.y, "files", unit, color_brown, expl_font_size);
    //print_box(8*measure.x, 3*measure.y, 13*measure.x, 11*measure.y, "files", unit, color_brown, expl_font_size);

    print_box(13*measure.x, 3*measure.y, 18*measure.x, 11*measure.y, "", unit, color_brown, expl_font_size);
    print_box(14*measure.x +4*unit, 10*measure.y, 16*measure.x - 4*unit, 11*measure.y - 4*unit, "action", unit, color_brown, expl_font_size);
    //print_box(12*measure.x, 5*measure.y, 18*measure.x, 11*measure.y, "status box:", unit, color_dark_gray, menu_font_size - 3);

    B_STOP->visual(unit);
    B_BACK_MENU->visual(unit);
    B_BACK_EXPL->visual(unit);
    B_SLCT->visual(unit);
}

/// helpers for functional_menu_explorer
void path_manipulation(point mouse, point measure, short unit, screen_path*& pressedd_file, std::string & accessed_path, std::string & status)
{
    if(pressedd_file == nullptr)
    {
        for(size_t i = 0; explorer_files[i] && pressedd_file == nullptr; i++)
            pressedd_file = explorer_files[i]->functional(mouse, status);
        return;
    }

    screen_path* temp = nullptr;
    for(size_t i = 0; explorer_files[i] && temp == nullptr; i++)
        temp = explorer_files[i]->functional(mouse, status);
    if(temp == pressedd_file) // double click
    {
        accessed_path += status;
        if(std::filesystem::is_directory(accessed_path))
        {
            display_paths(measure, unit, accessed_path);
            pressedd_file = nullptr;
        }
        else // just txt and exe
        {
            std::string execution_path = "";
            execution_path += accessed_path;
            system(execution_path.c_str());
        }
    }
    else if(temp) // click on something else
    {
        pressedd_file->visual(); // erase highlight
        pressedd_file->selected = false;
        pressedd_file = temp;
        // ready for selection
    }
}

void visual_delete_selected(point mouse, point measure, short unit)
{
    if(selected_files[0] == nullptr)
        return;

    selected_screen_path* flag = nullptr; // if deleted
    short i = 0;
    for(; selected_files[i] && i < max_nr_paths_selectedd; i++)
    {
        if(selected_files[i]->functional(mouse))
        {
            flag = selected_files[i];
            break;
        }
    }

    if(i == max_nr_paths_selectedd)
    {
        printf("error - visual: can not delete selected files.\n");
        return;
    }
    if(flag == nullptr)
        return;

    // movement of the data !!!! TO DO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(short j = i; selected_files[j + 1]; j++)
    {
        delete selected_files[j];
        selected_screen_path temp(selected_files[j + 1]);

        selected_files[j] = & temp;
        selected_files[j]->visual();
    }

    // display
    print_box(13*measure.x, 3*measure.y, 18*measure.x, 11*measure.y, "", unit, color_brown, expl_font_size);
    for(short i = 0; selected_files[i]; i++)
            selected_files[i]->visual();
}

void functional_menu_explorer(point measure, short unit)
{
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

        //mkdir del fopen

        // path manipulation
        path_manipulation(mouse, measure, unit, pressedd_file, accessed_path, status);

        // select
        if(pressedd_file && B_SLCT->functional(mouse, unit))
        {
            pressedd_file->visual();
            add_to_selected_files(pressedd_file, accessed_path);
            for(size_t i = 0; selected_files[i]; i++)
                selected_files[i]->visual();
            pressedd_file->selected = false;
            pressedd_file = nullptr;
        }

        //delete selected
        visual_delete_selected(mouse, measure, unit);

        //action
    }
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

    //status box
    print_box(12*measure.x, 5*measure.y, 18*measure.x, 11*measure.y, "status box:", unit, color_dark_gray, menu_font_size - 3);

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

    //very_last_step(operation, algorithm, nr_paths, paths_input, path_output, output_name);
}
