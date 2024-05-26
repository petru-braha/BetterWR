#include <stdio.h>
#include <direct.h>
#include <graphics.h>
#include "../text_format.h"
#include "../../../admin/pack.h"
#include "visual_path.h"

// headers
const short nr_icons = 6;
const char  icon_path[]   = "constant files/media/icons/";
const char* icon_imag[nr_icons] = {"dir.jpg", "unknown.jpg", "bin.jpg", "huf.jpg", "lzw.jpg", "txt.jpg"};
const char*  extnsions[26] = {"txt", "huf", "lzw", "bin",
                            "jpg", "png", "gif", "bmp",
                            "mp4", "mkv", "avi", "mov",
                            "mp3", "aac", "wav", "flac",
                            "pdf", "doc", "xls",
                            "zip", "rar", "7z", "tar",
                            "exe", "dll", "so"};


// helpers
void file_highlight(int x1, int y1, int x2, int y2, int color)
{
    setcolor(color);
    for(int i=0; i<2; i++)
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
}
point visual_measure("square_measure"), visual_unit("unit");
short bigger_unit = visual_unit.x * 4;

// help asking
const short visual_iterator_y = visual_measure.y / 3;
const point border_left_up(2*visual_measure.x + bigger_unit, 3*visual_measure.y + bigger_unit);
const point border_rght_up(8*visual_measure.x + bigger_unit, 3*visual_measure.y + bigger_unit);

const point border_left_down(2*visual_measure.x + bigger_unit, 11*visual_measure.y - bigger_unit);
const point border_rght_down(8*visual_measure.x + bigger_unit, 11*visual_measure.y - bigger_unit);

const short border_left_last_path_x = border_left_up.y + (max_nr_paths_displayed / 2 - 1) * visual_iterator_y;

screen_path::screen_path(screen_path* path_displayed_above, char* text)
{
    this->text = new char[MAX];
    strcpy(this->text, text);
    this->selected = false;
    if(path_displayed_above == nullptr)
    {
        this->top_left.x = border_left_up.x;
        this->top_left.y = border_left_up.y;
        this->bottom_right.x = border_left_up.x + path_measure_x * visual_measure.x;
        this->bottom_right.y = border_left_up.y + visual_iterator_y;
        this->visual_icon.set_values(this->top_left, this->bottom_right, visual_unit.x, 0);
        this->visual_text.set_values(this->top_left, this->bottom_right, visual_unit.x, 1);
        return;
    }

    // it is not mandatory to check if all the positions are filled up
    // because of the dimension if the array of displayed paths

    if(path_displayed_above->top_left.x == border_left_up.x)
    {
        if(path_displayed_above->top_left.y >= border_left_last_path_x) // first to be printed to the right side
        {
            this->top_left.x = border_rght_up.x;
            this->top_left.y = border_rght_up.y;
            this->bottom_right.x = border_rght_up.x + path_measure_x * visual_measure.x;
            this->bottom_right.y = border_rght_up.y + visual_iterator_y;
        }
        else // print on the left side
        {
            this->top_left.x = border_left_up.x;
            this->top_left.y = path_displayed_above->bottom_right.y;
            this->bottom_right.x = border_left_up.x + path_measure_x * visual_measure.x;
            this->bottom_right.y = this->top_left.y + visual_iterator_y;
        }
    }
    else
    {
        this->top_left.x = border_rght_up.x;
        this->top_left.y = path_displayed_above->bottom_right.y;
        this->bottom_right.x = border_rght_up.x + path_measure_x * visual_measure.x;
        this->bottom_right.y = this->top_left.y + visual_iterator_y;
    }

    this->visual_icon.set_values(this->top_left, this->bottom_right, visual_unit.x, 0);
    this->visual_text.set_values(this->top_left, this->bottom_right, visual_unit.x, 1);
}

// visual
#define visual_text_max_len 25
void print_text(screen_path* obj, short x1, short y1)
{
    char* new_text = new char[MAX];
    strcpy(new_text, obj->text);
    if(strlen(new_text) > visual_text_max_len)
        strcpy(new_text + visual_text_max_len, "error\0");

    outtextxy(x1, y1, new_text);
    delete new_text;
    settextstyle(text_font, HORIZ_DIR, expl_font_size);
}

void screen_path::visual()
{
    setfillstyle(SOLID_FILL, color_black);
    bar(this->top_left.x, this->top_left.y, this->bottom_right.x, this->bottom_right.y);
    // icon
    int index_context = 0;
    char character = this->text[strlen(this->text) - 1];
    if(character == '/' || character == 92) // folder
        index_context = dir;
    else
    {
        for(size_t i = 0; i < strlen(this->text); i++)
            if(this->text[i] == '.')
                index_context = i;

        char* extension = this->text + index_context + 1;
        index_context = -1;

        for(size_t i = 0; extnsions[i]; i++)
            if(strcmp(extension, extnsions[i]) == 0)
                index_context = i;

        switch(index_context)
        {
        case -1: // unknown
            index_context = unknown;
            break;
        case 0: // txt
            index_context = txt;
            break;
        case 1: // huf
            index_context = huf;
            break;
        case 2: // lzw
            index_context = lzw;
            break;
        default: // bin
            index_context = bin;
            break;
        }
    }

    short x1, y1, x2, y2;
    x1 = this->visual_icon.top_left.x;
    y1 = this->visual_icon.top_left.y;
    x2 = this->visual_icon.bottom_right.x;
    y2 = this->visual_icon.bottom_right.y;
    char temp[MAX] = "\0"; strcpy(temp, icon_path); strcat(temp, icon_imag[index_context]);
    readimagefile(temp, x1, y1, x2, y2);

    // text
    setcolor(color_light_blue);
    settextstyle(text_font, HORIZ_DIR, expl_font_size - 2);
    x1 = this->visual_text.top_left.x;
    y1 = this->visual_text.top_left.y;
    print_text(this, x1, y1);
}

screen_path* screen_path::functional(point mouse, std::string & status)
{
    // verification
    if(mouse.x < this->top_left.x || mouse.x > this->bottom_right.x || mouse.x == -1)
        return nullptr;
    if(mouse.y < this->top_left.y || mouse.y > this->bottom_right.y || this == nullptr)
        return nullptr;

    // second click
    if(this->selected)
    {
        this->selected = false;
        status = this->text;
        return this;
    }

    // first_click
    this->selected = true;
    file_highlight(this->top_left.x, this->top_left.y, this->bottom_right.x, this->bottom_right.y, color_white);
    status = "";
    return this;
}

// selected files
const point border_sele_up(13*visual_measure.x + bigger_unit, 3*visual_measure.y + bigger_unit);

selected_screen_path::selected_screen_path(selected_screen_path* previous, screen_path* & path, std::string full_path)
{
    this->full_path = new char[MAX];
    strcpy(this->full_path, full_path.c_str());

    this->text = new char[MAX];
    strcpy(this->text, path->text);
    this->selected = false;

    if(previous == nullptr)
    {
        this->top_left.x = border_sele_up.x;
        this->top_left.y = border_sele_up.y;
        this->bottom_right.x = border_sele_up.x + path_measure_x * visual_measure.x;
        this->bottom_right.y = border_sele_up.y + visual_iterator_y;

        this->visual_icon.set_values(this->top_left, this->bottom_right, visual_unit.x, 0);
        this->visual_text.set_values(this->top_left, this->bottom_right, visual_unit.x, 1);
        return;
    }

    this->top_left.x = border_sele_up.x;
    this->top_left.y = previous->bottom_right.y;
    this->bottom_right.x = border_sele_up.x + path_measure_x * visual_measure.x;
    this->bottom_right.y = this->top_left.y + visual_iterator_y;

    this->visual_icon.set_values(this->top_left, this->bottom_right, visual_unit.x, 0);
    this->visual_text.set_values(this->top_left, this->bottom_right, visual_unit.x, 1);
}

bool selected_screen_path::functional(point mouse)
{
    if(mouse.x < this->top_left.x || mouse.x > this->bottom_right.x || mouse.x == -1)
        return false;
    if(mouse.y < this->top_left.y || mouse.y > this->bottom_right.y || this == nullptr)
        return false;

    file_highlight(this->top_left.x, this->top_left.y, this->bottom_right.x, this->bottom_right.y, color_red);
    delay(100);
    // the actual deletion will be done in a different function
    return true;
}

void selected_screen_path::mmcpy(selected_screen_path* from)
{
    strcpy(this->text, from->text);
    strcpy(this->full_path, from->full_path);
}
