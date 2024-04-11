#pragma once
#define nr_buttons 13
class button{
    point top_left;
    point bottom_right;
    virtual void execute() {} // if = 0 then it would have been an abstract class can i couldn't make 'button' instances
public:
    short index;
    button();
    button(short xx, short xy, short yx, short yy);
    point get_coordinates(bool which_one);
    void visual_appearance();

    bool click(short mouse_x, short mouse_y); //highlight, execute, i love my wife<3
}

//all buttons are singletons
class button_00 : public button{
    static button_00* instance = nullptr;
    button_00();
    void execute();
public:
    static button_00* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_00();
        return instance;
    }
};
class button_01 : public button{
    static button_01* instance = nullptr;
    button_01();
    void execute();
public:
    static button_01* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_01();
        return instance;
    }
};
class button_02 : public button{
    static button_02* instance = nullptr;
    button_02();
    void execute();
public:
    static button_02* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_02();
        return instance;
    }
};
class button_03 : public button{
    static button_03* instance = nullptr;
    button_03();
    void execute();
public:
    static button_03* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_03();
        return instance;
    }
};
class button_04 : public button{
    static button_04* instance = nullptr;
    button_04();
    void execute();
public:
    static button_04* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_04();
        return instance;
    }
};
class button_05 : public button{
    static button_05* instance = nullptr;
    button_05();
    void execute();
public:
    static button_05* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_05();
        return instance;
    }
};
class button_06 : public button{
    static button_06* instance = nullptr;
    button_06();
    void execute();
public:
    static button_06* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_06();
        return instance;
    }
};
class button_07 : public button{
    static button_07* instance = nullptr;
    button_07();
    void execute();
public:
    static button_07* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_07();
        return instance;
    }
};
class button_08 : public button{
    static button_08* instance = nullptr;
    button_08();
    void execute();
public:
    static button_08* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_08();
        return instance;
    }
};
class button_09 : public button{
    static button_09* instance = nullptr;
    button_09();
    void execute();
public:
    static button_09* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_09();
        return instance;
    }
};
class button_10 : public button{
    static button_10* instance = nullptr;
    button_10();
    void execute();
public:
    static button_10* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_10();
        return instance;
    }
};
class button_11 : public button{
    static button_11* instance = nullptr;
    button_11();
    void execute();
public:
    static button_11* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_11();
        return instance;
    }
};
class button_12 : public button{
    static button_12* instance = nullptr;
    button_12();
    void execute();
public:
    static button_12* GetInstance()
    {
        if(instance == nullptr)
            instance = new button_12();
        return instance;
    }
};
