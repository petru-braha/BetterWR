#include <graphics.h>
#define MAX 300
#define nr_buttons 13
short int width=1536, height=960;
short int coordo[13][4];
short int file_coordo[MAX][4];
short int unit=0;

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
}

void graphic_button(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, 9); //the edge of rectangles
    bar(x1, y1, x2, y2);
    setfillstyle(SLASH_FILL, 1);
    bar(x1+5, y1+5, x2-5, y2-5);
}

void graphic_x(int x1, int y1, int x2, int y2)
{
    setcolor(4);
    line(x1, y2, x2, y1);
    line(x1, y1, x2, y2);
}

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

void start_graphics(bool first_exe)
{
    //background
    if(first_exe)
        readimagefile("photos/1.jpg", 0, 0, width, height);
    else
        readimagefile("photos/2.jpg", 0, 0, width, height);
    first_exe=1;
    setcolor(9);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(1000, 200, "Algorithms:");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(1050, 250, "-Huffman trees");
    outtextxy(1050, 270, "-Lempel-Ziv-Welch");

    graphics_GLOBALbuttons(3);
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

void graphics_selected(char file_name[], int nr_files_for_tar)
{
    setcolor(15);
    line(1040, 195+unit, 1440, 195+unit);
    file_coordo[nr_files_for_tar-1][0]=1000;
    file_coordo[nr_files_for_tar-1][1]=195+unit;
    file_coordo[nr_files_for_tar-1][2]=1440;

    settextstyle(SMALL_FONT, 0, 10);
    outtextxy(1040, 200+unit, file_name);

    if(strchr(file_name, '.')==NULL)
        readimagefile("photos/folder2.jpg", 1010, 200+unit, 1035, 235+unit);
    else
        readimagefile("photos/txt2.jpg", 1010, 200+unit, 1035, 235+unit);
    unit+=45;
    line(1040, 195+unit, 1440, 195+unit);
    file_coordo[nr_files_for_tar-1][3]=195+unit;
    graphics_GLOBALbuttons(5);
}

bool click_on_file(int x, int y, int which_button)
{
    if(x>=file_coordo[which_button][0] && x<=file_coordo[which_button][2])
        if(y>=file_coordo[which_button][1] && y<=file_coordo[which_button][3])
            return 1;
    return 0;
}
bool click_on_button(int x, int y, int which_button)
{
    if(x>=coordo[which_button][0] && x<=coordo[which_button][2])
        if(y>=coordo[which_button][1] && y<=coordo[which_button][3])
            return 1;
    return 0;
}
