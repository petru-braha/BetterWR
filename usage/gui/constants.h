#pragma once
#include "text_format.h"
#include "button/button.h"

button_0*      B_STOP = button_0::get_instance();
button_1*      B_BACK_MENU = new button_1;
button_1*      B_BACK_EXPL = new button_1;

button_menu_0* B_EXPL = button_menu_0::get_instance();
button_menu_1* B_INFO = button_menu_1::get_instance();
button_menu_2* B_TEST = button_menu_2::get_instance();

button_expl_static* B_OPTN = new button_expl_static;
button_expl_static* B_ALGO = new button_expl_static;
button_expl_0* B_SLCT = button_expl_0::get_instance();
button_expl_1* B_ACTN = button_expl_1::get_instance();

void b_set_values(point measure)
{
    point temp("unit"); short unit = temp.x;

    B_STOP->set_values(17*measure.x, 0 + 4*unit, 19*measure.x - 2*unit, measure.y, (char*)" exit");
    B_BACK_MENU->set_values(0 + 4*unit, 11*measure.y, 2*measure.x, 12*measure.y - 4*unit, (char*)" back");
    B_BACK_EXPL->set_values(0 + 4*unit, 11*measure.y, 2*measure.x, 12*measure.y - 4*unit, (char*)" back");

    B_EXPL->set_values(measure.x, 4*measure.y, 7*measure.x, 5*measure.y, (char*)"stored files");
    B_INFO->set_values(measure.x, 6*measure.y, 7*measure.x, 7*measure.y, (char*)"+information");
    B_TEST->set_values(measure.x, 8*measure.y, 7*measure.x, 9*measure.y, (char*)"with strings");

    B_OPTN->set_values(2*measure.x, measure.y, 3*measure.x, 2*measure.y, (char*)"cpr"); B_OPTN->set_option((char*)"dcp");
    B_ALGO->set_values(3*measure.x, measure.y, 4*measure.x, 2*measure.y, (char*)"huf"); B_ALGO->set_option((char*)"lzw");

    B_SLCT->set_values(10*measure.x, measure.y, 11*measure.x, 2*measure.y, (char*)"sel");
    B_ACTN->set_values(14*measure.x +4*unit, 10*measure.y, 17*measure.x - 4*unit, 11*measure.y - 4*unit, (char*)"   action");
}

void b_del_values()
{
    delete B_STOP;
    delete B_BACK_MENU;
    delete B_BACK_EXPL;

    delete B_EXPL;
    delete B_INFO;
    delete B_TEST;

    delete B_OPTN;
    delete B_ALGO;

    delete B_SLCT;
    delete B_ACTN;
}

std::vector<std::string> list_volumes();
void delete_dir_accessed(std::string & str);

#include "expl_path/visual_path.h"
screen_path* explorer_files[max_nr_paths_displayed];
selected_screen_path* selected_files[max_nr_paths_selectedd];
short add_to_selected_files(screen_path*& path, std::string full_path)
{
    if(full_path == "")
    {
        printf("error - selection: can not use partitions for an action.\n");
        return -1;
    }

    path->selected = false;
    short i = 0;
    while(selected_files[i] && i < max_nr_paths_selectedd)
    {
        if(strcmp(selected_files[i]->text, path->text) == 0)
        {
            printf("error - selection: can not add the same element twice.\n");
            return -1;
        }
        i++;
    }

    if(i == max_nr_paths_selectedd)
    {
        printf("error - selection: the stack of selected files is full.\n");
        return -1;
    }

    selected_screen_path* previous = i > 0 ? selected_files[i - 1] : nullptr;
    selected_files[i] = new selected_screen_path(previous, path, full_path);
    return i;
}

/*
#define visual_limitPOPUP.tl.x
#define visual_limitPOPUP.tl.y
#define visual_limitPOPUP.br.x
#define visual_limitPOPUP.br.y
*/
