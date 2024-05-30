#pragma once
#define nr_buttons 13
#include "../point.h"

class button
{
protected:
    char* text = nullptr;
    point top_left;
    point bottom_right;
    virtual void execute(){}
public:
    void set_values(short xx, short xy, short yx, short yy, char* name);
    virtual void visual(short unit);
    virtual bool functional(point mouse, short unit); //highlight, execute, i love my wife<3

    virtual ~button(){ delete text; }

    //if panic
    point get_point(bool which_one)const    { return which_one == false ? this->top_left : this->bottom_right; }
    char* get_text()const                   { return text; }
};

class button_0 : public button
{
    static button_0* instance;
    button_0();
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

class button_1 : public button{ public: void visual(short unit); };

class button_menu_0 : public button
{
    static button_menu_0* instance;
    button_menu_0();
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
    button_menu_1();
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
    button_menu_2();
public:
    static button_menu_2* get_instance()
    {
        if(instance == nullptr)
            instance = new button_menu_2();
        return instance;
    }
};

class button_expl_static : public button
{
    char* option;
    void execute();
public:
    button_expl_static(){ this->set_values(0, 0, 0, 0, nullptr); }
    void set_option(char* idea){ option = idea; }
};

class button_expl_0 : public button
{
    static button_expl_0* instance;
    button_expl_0();
public:
    static button_expl_0* get_instance()
    {
        if(instance == nullptr)
            instance = new button_expl_0();
        return instance;
    }
};

class button_expl_1 : public button
{
    static button_expl_1* instance;
    button_expl_1();
public:
    static button_expl_1* get_instance()
    {
        if(instance == nullptr)
            instance = new button_expl_1();
        return instance;
    }
};
