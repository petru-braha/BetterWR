#pragma once
const int text_font = 8;
const int text_font_2 = 3;
const int menu_font_size = 6;
const int expl_font_size = 3;

const int color_black   = 0;
const int color_blue    = 1;
const int color_green   = 2;
const int color_cyan    = 3;
const int color_red     = 4;
const int color_magenta = 5;
const int color_brown   = 6;
const int color_light_gray    = 7;
const int color_dark_gray     = 8;
const int color_light_blue    = 9;
const int color_light_green   = 10;
const int color_light_cyan    = 11;
const int color_light_red     = 12;
const int color_light_magenta = 13;
const int color_yellow = 14;
const int color_white  = 15;

const int outside_left_click = WM_LBUTTONDOWN; //513
const int outside_tab = 0; //???

#include "button/button.h"
button_0*      B_STOP = button_0::get_instance();
button_menu_0* B_EXPL = button_menu_0::get_instance();
button_menu_1* B_INFO = button_menu_1::get_instance();
button_menu_2* B_TEST = button_menu_2::get_instance();

void b_set_values(short unit_x, short unit_y)
{
    B_STOP->set_values(17*unit_x, 0, 19*unit_x, unit_y, "exit");
    B_EXPL->set_values(unit_x, 4*unit_y, 7*unit_x, 5*unit_y, "stored files");
    B_INFO->set_values(unit_x, 6*unit_y, 7*unit_x, 7*unit_y, "+information");
    B_TEST->set_values(unit_x, 8*unit_y, 7*unit_x, 9*unit_y, "with strings");
}
