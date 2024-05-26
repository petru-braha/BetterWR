#pragma once
#include <string>
#include "../point.h"
#define max_nr_paths_displayed 46
#define max_nr_paths_selectedd 10
#define nr_paths_in_measure 3 // there are 16 measures = > 3 * 16 == 48 places

// additional values (not that useful tbh)
#define path_measure_x 4
#define path_measure_y 1
#define MAX 500

void print_box(short x1, short y1, short x2, short y2, const char* text, short unit, int color, int text_size);

struct visual_element // icon and text
{
    point top_left, bottom_right;
    //visual_element(): top_left(zro), bottom_right(zro){}

    void set_values(const point& one, const point& two, const short& unit)
    {
        this->top_left.y = one.y + unit;
        this->bottom_right.y = two.y - unit;
        this->top_left.x = one.x + unit;
        this->bottom_right.x = two.x - unit;
    }

    void set_values(const point& one, const point& two, const short& unit, bool iconORtext)
    {
        this->top_left.y = one.y + unit;
        this->bottom_right.y = two.y - unit;
        short length = two.y - one.y - 2 * unit;

        switch(iconORtext)
        {

        case false: // icon

            this->top_left.x = one.x + unit;
            this->bottom_right.x = this->top_left.x + length;
            this->bottom_right.y = this->top_left.y + length;
            break;

        case true:  // text

            this->top_left.x = one.x + unit + length + 2*unit;
            this->bottom_right.x = two.x - unit;
            break;
        }
    }

    void operator = (const visual_element& value)
    {
        this->top_left = value.top_left;
        this->bottom_right = value.bottom_right;
    }

    void visual_print()
    {
        short unit = point("unit").x;

        const short x1 = top_left.x;
        const short y1 = top_left.y;
        const short x2 = bottom_right.x;
        const short y2 = bottom_right.y;

        setfillstyle(SOLID_FILL, color_blue);
        bar(x1, y1, x2, y2);
        setfillstyle(SOLID_FILL, color_light_blue);
        bar(x1 + unit, y1 + unit, x2 - unit, y2 - unit); unit*=2;
        setfillstyle(SOLID_FILL, color_black);
        bar(x1 + unit, y1 + unit, x2 - unit, y2 - unit); unit*=2;
    }

    bool inside(const point& random)
    {
        if(random.x < top_left.x || random.x > bottom_right.x)
            return false;
        if(random.y < top_left.y || random.y > bottom_right.y)
            return false;
        return true;
    }

    void highlight()
    {
        short x1 = top_left.x;
        short y1 = top_left.y;
        short x2 = bottom_right.x;
        short y2 = bottom_right.y;

        setcolor(color_white);
        for(int i=0; i < 3; i++)
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
        this->visual_print();
    }
};

struct screen_path
{
protected:
    point top_left, bottom_right;
public:
    bool selected;
    char* text;
    visual_element visual_icon, visual_text;

    screen_path(){} // helps selected_screen_path to copy
    screen_path(screen_path* path_displayed_above, char* text);
    void visual(); // icon + text
    screen_path* functional(point mouse, std::string & status);
    ~screen_path(){ delete[] text; }
};

struct selected_screen_path : public screen_path
{
    char* full_path;
    selected_screen_path(selected_screen_path* previous, screen_path* & path, std::string full_path);
    void mmcpy(selected_screen_path* from);
    bool functional(point mouse);
    ~selected_screen_path(){ delete[] full_path; delete[] text; }
};

enum
{
    dir = 0,
    unknown,
    bin,
    huf,
    lzw,
    txt
};

class pop_up
{
    point top_left, bottom_right;
public:
    char* title, *text;
    visual_element visual_text, visual_exit, visual_redy;

    pop_up(const point& a, const point& b);
    void functional();
    ~pop_up();
};
