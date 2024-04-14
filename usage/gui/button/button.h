#pragma once
#define nr_buttons 13

struct point
{
    short x, y;
    point():x(0), y(0){}
};

class button
{
    char* text;
    point top_left;
    point bottom_right;
    virtual void execute(); // if =0 => abstract => no instances => no singletons
public:
    button();
    void set_values(short xx, short xy, short yx, short yy, char* name);
    virtual void visual(short unit);
    virtual bool functional(point mouse, short unit); //highlight, execute, i love my wife<3

    //if panic
    point get_point(bool which_one);
    char* get_text() { return text; }
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

class button_menu_0 : public button
{
    static button_menu_0* instance;
    button_menu_0(){ this->set_values(0, 0, 0, 0, nullptr); }
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
    button_menu_1() { this->set_values(0, 0, 0, 0, nullptr); }
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
    button_menu_2(){ this->set_values(0, 0, 0, 0, nullptr); }
public:
    static button_menu_2* get_instance()
    {
        if(instance == nullptr)
            instance = new button_menu_2();
        return instance;
    }
};

/*class button_expl_0 : public button
{
    static button_expl_0* instance;
    button_expl_0(){ this->set_values(0, 0, 0, 0, nullptr); }
    char* execute(); //return
public:


};
*/
