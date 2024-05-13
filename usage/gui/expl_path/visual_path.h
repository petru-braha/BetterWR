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

struct visual_element // icon and text
{
    point top_left, bottom_right;
    void set_values(point one, point two, short unit, bool iconORtext)
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
};

struct screen_path
{
protected:
    point top_left, bottom_right;
public:
    bool selected;
    char* text;
    visual_element visual_icon, visual_text;

    screen_path(){}
    screen_path(screen_path* path_displayed_above, char* text);
    void visual(); // icon + text
    screen_path* functional(point mouse, std::string & status);
    virtual ~screen_path(){ delete text; }
};

struct selected_screen_path : public screen_path
{
    char* full_path;
    selected_screen_path(selected_screen_path* previous, screen_path* & path, std::string full_path);
    bool functional(point mouse);
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

