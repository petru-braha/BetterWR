#include "../../admin/libraries.h"
#include "constants.h"
#include <wtypes.h>

//back button implementation: execution of
//called in visual_test visual_info

void define_fullscreen(short& x, short& y){
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);
    x = desktop.right;
    y = desktop.bottom;
}

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

void visual_menu_explorer(point measure, short unit)
{
    point screen;
    define_fullscreen(screen.x, screen.y);

    //readimagefile("constant files/media/layout/explorer layout.jpg", 0, 0, screen.x, screen.y);
    readimagefile("constant files/media/layout/background.jpg", 0, 0, screen.x, screen.y);

    print_box(2*measure.x, measure.y, 3*measure.x, 2*measure.y, "cps", unit, color_brown, expl_font_size);
    print_box(3*measure.x, measure.y, 4*measure.x, 2*measure.y, "dcs", unit, color_brown, expl_font_size);

    print_box(5*measure.x, measure.y, 6*measure.x, 2*measure.y, "huf", unit, color_brown, expl_font_size);
    print_box(6*measure.x, measure.y, 7*measure.x, 2*measure.y, "lzw", unit, color_brown, expl_font_size);

    print_box(10*measure.x, measure.y, 11*measure.x, 2*measure.y, "sel", unit, color_brown, expl_font_size);
    print_box(12*measure.x, measure.y, 13*measure.x, 2*measure.y, "mkd", unit, color_brown, expl_font_size);
    print_box(14*measure.x, measure.y, 15*measure.x, 2*measure.y, "fpn", unit, color_brown, expl_font_size);
    print_box(16*measure.x, measure.y, 17*measure.x, 2*measure.y, "del", unit, color_brown, expl_font_size);

    print_box(2*measure.x, 2*measure.y, 18*measure.x, 3*measure.y, "path", unit, color_brown, expl_font_size);
    print_box(2*measure.x, 3*measure.y, 7*measure.x, 11*measure.y, "files", unit, color_brown, expl_font_size);
    print_box(8*measure.x, 3*measure.y, 13*measure.x, 11*measure.y, "files", unit, color_brown, expl_font_size);

    print_box(13*measure.x, 3*measure.y, 17*measure.x, 11*measure.y, "selected files", unit, color_brown, expl_font_size);

    print_box(12*measure.x, 5*measure.y, 18*measure.x, 11*measure.y, "status box:", unit, color_dark_gray, menu_font_size - 3);
    getch();
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
void visual_menu(point measure, short unit)
{
    //background
    point screen;
    define_fullscreen(screen.x, screen.y);
    readimagefile("constant files/media/layout/background.jpg", 0, 0, screen.x, screen.y);
    //readimagefile("constant files/media/layout/menu layout.jpg", 0, 0, screen.x, screen.y);

    //title
    print_box(5*measure.x, 2*measure.y, 15*measure.x, 3*measure.y, "*data compression app1*", unit, color_white, menu_font_size);

    //buttons
    b_set_values(measure.x, measure.y);
    B_STOP->visual(unit);
    B_EXPL->visual(unit);
    B_INFO->visual(unit);
    B_TEST->visual(unit);

    //status box
    print_box(12*measure.x, 5*measure.y, 18*measure.x, 11*measure.y, "status box:", unit, color_dark_gray, menu_font_size - 3);
}

void functional_menu(point measure, short unit)
{
    point mouse;
    short menu_decision = -1;
    while(true)
    {
        //menu decision
        button* menu_buttons[3] = {B_EXPL, B_INFO, B_TEST};
        while(menu_decision == -1)
        {
            getmouseclick(outside_left_click, (int&)mouse.x, (int&)mouse.y);
            for(int i=0; i<3; i++)
                if(menu_buttons[i]->functional(mouse, unit))
                    menu_decision = i;
        }

        switch(menu_decision)
        {
        case 0:
            visual_menu_explorer(measure, unit);
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

        visual_menu(measure, unit);
        menu_decision = -1;
    }
    //very_last_step(operation, algorithm, nr_paths, paths_input, path_output, output_name);
}
