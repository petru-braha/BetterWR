#include <graphics.h>
#include "button.h"
#include <direct.h>    //for delay()

const int text_font = 8;
const int menu_font_size = 6;

const int color_black = 0;
const int color_blue = 1;
const int color_green = 2;
const int color_cyan = 3;
const int color_red = 4;
const int color_magenta = 5;
const int color_brown = 6;
const int color_light_gray = 7;
const int color_dark_gray = 8;
const int color_light_blue = 9;
const int color_light_green = 10;
const int color_light_cyan = 11;
const int color_light_red = 12;
const int color_light_magenta = 13;
const int color_yellow = 14;
const int color_white = 15;

void highlight(int x1, int y1, int x2, int y2)
{
    setcolor(15);
    for(int i=0; i<10; i++)
    {
        x1++;
        y1++;
        x2--;
        y2--;
        line(x1, y1, x2, y1);
        line(x1, y1, x1, y2);
        line(x1, y2, x2, y2);
        line(x2, y1, x2, y2);
    }
    delay(100);
}

void button::execute(){}

///default button
button::button()
{
    this->top_left.x = 0;
    this->top_left.y = 0;
    this->bottom_right.x = 0;
    this->bottom_right.y = 0;
    this->text = nullptr;
}

void button::set_values(short xx, short xy, short yx, short yy, char* name)
{
    top_left.x = xx;
    top_left.y = xy;
    bottom_right.x = yx;
    bottom_right.y = yy;
    text = name;
}

void button::visual(short unit)
{
    setcolor(color_white);
    settextstyle(text_font, HORIZ_DIR, menu_font_size);

    setfillstyle(SOLID_FILL, color_blue);
    bar(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
    setfillstyle(SOLID_FILL, color_light_blue);
    bar(top_left.x + unit, top_left.y + unit, bottom_right.x - unit, bottom_right.y - unit); unit*=2;
    setfillstyle(SOLID_FILL, color_black);
    bar(top_left.x + unit, top_left.y + unit, bottom_right.x - unit, bottom_right.y - unit); unit*=2;
    outtextxy(top_left.x + unit, top_left.y + unit, text);
}

bool button::functional(point mouse, short unit)
{
    if(mouse.x >= this->top_left.x && mouse.x <= this->bottom_right.x && mouse.x != -1)
        if(mouse.y >= this->top_left.y && mouse.y <= this->bottom_right.y)
        {
            highlight(this->top_left.x, this->top_left.y, this->bottom_right.x, this->bottom_right.y);
            this->visual(unit);
            this->execute();
            return true;
        }
    return false;
}

point button::get_point(bool which_one)
{
    if(which_one)
        return bottom_right;
    return top_left;
}

///actual buttons
//exit button
button_0* button_0::instance = nullptr;
button_0::button_0()
{
    this->set_values(0, 0, 0, 0, nullptr);
}
void button_0::visual(short unit)
{
    setcolor(color_dark_gray);
    settextstyle(text_font, HORIZ_DIR, menu_font_size);

    point tl = get_point(0);
    point br = get_point(1);

    setfillstyle(SOLID_FILL, color_blue);
    bar(tl.x, tl.y, br.x, br.y);
    setfillstyle(SOLID_FILL, color_light_blue);
    bar(tl.x + unit, tl.y + unit, br.x - unit, br.y - unit); unit*=2;
    setfillstyle(SOLID_FILL, color_black);
    bar(tl.x + unit, tl.y + unit, br.x - unit, br.y - unit); unit*=2;
    outtextxy(tl.x + unit, tl.y + unit, get_text());
}

void button_0::execute()// please remove files
{
    //remove temp files + delete all new //prevent all memory leaks
    closegraph();
    exit(0);
}

//menu buttons
button_menu_0* button_menu_0::instance = nullptr;
button_menu_1* button_menu_1::instance = nullptr;
button_menu_2* button_menu_2::instance = nullptr;
