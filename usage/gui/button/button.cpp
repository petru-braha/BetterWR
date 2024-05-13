#include <graphics.h>
#include <direct.h>

#include "button.h"
#include "../text_format.h"

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

///default button
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

///actual buttons
//exit button
button_0* button_0::instance = nullptr;

void button_0::visual(short unit)
{
    setcolor(color_dark_gray);
    settextstyle(text_font, HORIZ_DIR, back_font_size);

    setfillstyle(SOLID_FILL, color_blue);
    bar(this->top_left.x, this->top_left.y, this->bottom_right.x, this->bottom_right.y);
    setfillstyle(SOLID_FILL, color_light_blue);
    bar(this->top_left.x + unit, this->top_left.y + unit, this->bottom_right.x - unit, this->bottom_right.y - unit); unit*=2;
    setfillstyle(SOLID_FILL, color_black);
    bar(this->top_left.x + unit, this->top_left.y + unit, this->bottom_right.x - unit, this->bottom_right.y - unit); unit*=2;
    outtextxy(this->top_left.x + unit, this->top_left.y + unit, this->text);
    settextstyle(text_font, HORIZ_DIR, menu_font_size);
}

void button_0::execute()// please remove files
{
    //remove temp files + delete all new //prevent all memory leaks
    closegraph();
    exit(0);
}

//back button
void button_1::visual(short unit)
{
    setcolor(color_dark_gray);
    setfillstyle(SOLID_FILL, color_blue);
    bar(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
    setfillstyle(SOLID_FILL, color_light_blue);
    bar(top_left.x + unit, top_left.y + unit, bottom_right.x - unit, bottom_right.y - unit); unit*=2;
    setfillstyle(SOLID_FILL, color_black);
    bar(top_left.x + unit, top_left.y + unit, bottom_right.x - unit, bottom_right.y - unit); unit*=2;

    settextstyle(text_font, HORIZ_DIR, back_font_size);
    outtextxy(top_left.x + unit, top_left.y + unit, text);
    settextstyle(text_font, HORIZ_DIR, expl_font_size);
}

//menu buttons
button_menu_0* button_menu_0::instance = nullptr;
button_menu_1* button_menu_1::instance = nullptr;
button_menu_2* button_menu_2::instance = nullptr;

//expl buttons
button_expl_0* button_expl_0::instance = nullptr;
void button_expl_static::execute()
{
    setcolor(color_cyan);
    char* temp = get_text();
    point tl = get_point(0), br = get_point(1);
    this->set_values(tl.x, tl.y, br.x, br.y, option);
    option = temp;

    point tempo("unit");
    short unit = tempo.x;
    settextstyle(text_font, HORIZ_DIR, expl_font_size);
    this->visual(unit);
}
