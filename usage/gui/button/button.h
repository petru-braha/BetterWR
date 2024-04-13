#pragma once
#define nr_buttons 13

struct point
{
    short x, y;
} mouse;

class button
{
    char* text;
    point top_left;
    point bottom_right;
    virtual void execute(); // if =0 => abstract => no instances => no singletons
public:
    button();
    void set_values(short xx, short xy, short yx, short yy, const char* name);
    virtual void visual(short unit);
    bool functional(short mouse_x, short mouse_y); //highlight, execute, i love my wife<3

    //if panic
    point get_point(bool which_one);
    char* get_text() { return text; }
};

class button_0 : public button
{
    static button_0* instance;
    button_0():button(){}
    void execute();
public:
    void visual(short unit);
    static button_0* get_instance()
    {
        if(instance == nullptr)
            instance = new button_0();
        return instance;
    }
};

class button_menu_0 : public button
{
    static button_menu_0* instance;
    button_menu_0():button(){}
    void execute();
public:
    static button_menu_0* get_instance()
    {
        if(instance == nullptr)
            instance = new button_menu_0();
        return instance;
    }
};

class button_menu_1 : public button
{
    static button_menu_1* instance;
    button_menu_1():button(){}
    void execute();
public:
    static button_menu_1* get_instance()
    {
        if(instance == nullptr)
            instance = new button_menu_1();
        return instance;
    }
};

class button_menu_2 : public button
{
    static button_menu_2* instance;
    button_menu_2():button(){}
    void execute();
public:
    static button_menu_2* get_instance()
    {
        if(instance == nullptr)
            instance = new button_menu_2();
        return instance;
    }
};

