#include "../../admin/libraries.h"
#include "constants.h"

//extra function
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


void visual_menu_explorer()
{

}

void functional_menu_explorer()
{

}

void visual_menu_info()
{

}

void functional_menu_info()
{

}

void visual_menu_test()
{

}

void functional_menu_test()
{

}

///menu
void visual_menu(short unit_x, short unit_y)
{
    //define unit
    short unit = unit_y;
    while(unit > 10)
        unit /= 10;
    if(unit > 5)
        unit /= 2;

    print_box(5*unit_x, 2*unit_y, 15*unit_x, 3*unit_y, "*data compression app1*", unit, color_white, menu_font_size);

    b_set_values(unit_x, unit_y);
    B_STOP->visual(unit);
    B_EXPL->visual(unit);
    B_INFO->visual(unit);
    B_TEST->visual(unit);

    print_box(12*unit_x, 5*unit_y, 18*unit_x, 11*unit_y, "status box:", unit, color_dark_gray, menu_font_size - 3);
}

void functional_menu()
{
    short menu_decision = -1;
    while(true)
    {
        //menu decision
        //button* menu_buttons[3] = {B_EXPL, B_INFO, B_TEST};
        while(menu_decision == -1)
        {
            getmouseclick(outside_left_click, (int&)mouse.x, (int&)mouse.y);
            //for(int i=0; i<3; i++)
                //if(menu_buttons[i]->functional(mouse.x, mouse.y))
                    //menu_decision = i;
        }

        switch(menu_decision)
        {
        case 0:
            visual_menu_explorer();
            break;
        case 1:
            visual_menu_info();
            break;
        case 2:
            visual_menu_test();
            break;
        default:
            break;
        }


    }
    //very_last_step(operation, algorithm, nr_paths, paths_input, path_output, output_name);
}
