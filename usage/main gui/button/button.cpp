#include <graphics.h>
#include "button.h"
#include <dos.h>    //for delay()
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

button::button()
{
    top_left.x = 0;
    top_left.y = 0;
    define_fullscreen(bottom_right.x, bottom_right.y);
}

button::button(short xx, short xy, short yx, short yy)
{
    top_left.x = xx;
    top_left.y = xy;
    bottom_right.x = yx;
    bottom_right.y = yy;
}

point button::get_coordinates(bool which_one)
{
    if(which_one == 0)
        return top_left;
    return bottom_right;
}

void button::visual_appearance()
{
    ///rectangle
    setfillstyle(SOLID_FILL, 9); //the edge of rectangles
    bar(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
    setfillstyle(SOLID_FILL, 1);
    bar(top_left.x + 5, top_left.y + 5, bottom_right.x - 5, bottom_right.y - 5);
}

void button::click(short mouse_x, short mouse_y)
{
    if(mouse_x >= top_left.x && mouse_x <= bottom_right.x)
        if(mouse_y >= top_left.y && mouse_y <= bottom_right.y)
        {
            highlight(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
            visual_appearance();
            execute();
            return true;
        }
    return false;
}

//to be defined
void button_00::execute() //compress
{
    //option is set to compress
    //opens explorer
}

void button_01::execute() //decompress
{
    //option is set to decompress
}

void button_02::execute() //more info
{

}

void button_03::execute()
{
    //inchid graful
    exit(0);
}
void button_04::execute();
void button_05::execute();
void button_06::execute();
void button_07::execute();
void button_08::execute();
void button_09::execute();
void button_10::execute();
void button_11::execute();
void button_12::execute();


void graphics_MENUbuttons()
{
    setcolor(9);
    int x1=60, y1=height/4, temp=60, y2=y1+temp, x2=x1+380;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    for(int i=0; i<3; i++)
    {
        switch (i)
        {
        case 0:
            graphic_button(x1, y1, x2, y2);
            outtextxy(x1+15, y1+15, "compress");
            break;

        case 1:
            graphic_button(x1, y1, x2, y2);
            outtextxy(x1+15, y1+15, "decompress");
            break;

        case 2:
            graphic_button(x1, y1, x2, y2);
            outtextxy(x1+15, y1+15, "more info");
            break;

        case 3:
            graphic_button(x1, y1, x2, y2);
            outtextxy(x1+15, y1+15, "test");
            break;

        default:
            break;
        }
        coordo[i][0]=x1;
        coordo[i][1]=y1;
        coordo[i][2]=x2;
        coordo[i][3]=y2;

        y1=y2+10;
        y2=y1+temp;
    }
}

void graphics_GLOBALbuttons(int value)
{
    switch(value)
    {
    case 3:
        setcolor(4);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        graphic_button(1350, 40, 1500, 100);
        outtextxy(1375, 60, "STOP");
        coordo[3][0]=1350;
        coordo[3][1]=40;
        coordo[3][2]=1500;
        coordo[3][3]=100;
        break;
    case 4:
        setcolor(9);
        settextstyle(DEFAULT_FONT, 0, 2);
        graphic_button(30, 880, 130, 930);
        outtextxy(36, 895, "inapoi");
        coordo[4][0]=30;
        coordo[4][1]=880;
        coordo[4][2]=130;
        coordo[4][3]=930;
        break;
    case 5:
        setcolor(4);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        graphic_button(1270, 840, 1470, 900);
        outtextxy(1312, 860, "GATA");
        coordo[5][0]=1270;
        coordo[5][1]=840;
        coordo[5][2]=1470;
        coordo[5][3]=900;
        break;
    }
}

void graphics_EXPLbuttons()
{
    setcolor(9);
    settextstyle(SMALL_FONT, 0, 9);
    int y=height/6;
    //selectare
    graphic_button(60, y-5, 180, y+35);
    outtextxy(70, y, "Select");
    coordo[6][0]=60;
    coordo[6][1]=y-5;
    coordo[6][2]=180;
    coordo[6][3]=y+35;
    y+=35;

    ///accesarea se va face din doublu clic (folder/fisier)
    //add folder
    graphic_button(60, y-5, 180, y+35);
    outtextxy(70, y, "Mkdir");
    coordo[7][0]=60;
    coordo[7][1]=y-5;
    coordo[7][2]=180;
    coordo[7][3]=y+35;
    y+=35;
    ///adauga fisier
    graphic_button(60, y-5, 180, y+35);
    outtextxy(70, y, "Fopen");
    coordo[8][0]=60;
    coordo[8][1]=y-5;
    coordo[8][2]=180;
    coordo[8][3]=y+35;
    y+=35;
    ///sterge
    graphic_button(60, y-5, 180, y+35);
    outtextxy(70, y, "Delete");
    coordo[9][0]=60;
    coordo[9][1]=y-5;
    coordo[9][2]=180;
    coordo[9][3]=y+35;
}

void graphics_ALGbuttons()
{
    setcolor(15);
    settextstyle(SMALL_FONT, 0, 8);
    graphic_button(50, 30, 125, 75);
    outtextxy(58, 40, "HUF");
    coordo[10][0]=50;
    coordo[10][1]=30;
    coordo[10][2]=125;
    coordo[10][3]=75;
    graphic_button(125, 30, 200, 75);
    outtextxy(133, 40, "LZW");
    coordo[11][0]=125;
    coordo[11][1]=30;
    coordo[11][2]=200;
    coordo[11][3]=75;
}

