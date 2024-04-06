#include <graphics.h>
#include "../../graphics_functions.h"
#include "../../global_variables.h"

struct point{
    int x, y;
} mouse;

void commands_firstStep_menu(int &which_button)
{
    while(which_button==0)
    {
        getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y);
        if(mouse.x!=-1 && mouse.y!=-1)
        {
            //1. ESC
            if(click_on_button(mouse.x, mouse.y, 3))
            {
                highlight(coordo[3][0], coordo[3][1], coordo[3][2], coordo[3][3]);
                delay(100);
                closegraph();
                exit(0);
            }
            //2. MENUbuton
            for(int i=0; i<3; i++)
                if(click_on_button(mouse.x, mouse.y, i))
                {
                    highlight(coordo[i][0], coordo[i][1], coordo[i][2], coordo[i][3]);
                    delay(100);
                    which_button=i+1;
                    break;
                }
        }
    }
}

#include <windows.h>
void file_explorer();

void commands_secondStep_decideOperation(char file_accessedPATH[], int which_button, bool &first_command, char& alg)
{
    if(file_accessedPATH[0] == 0 && which_button)
    {
        if(which_button==3)
        {
            start_graphics(0);
            setcolor(15);
            settextstyle(DEFAULT_FONT, 0, 2);
            outtextxy(coordo[0][0], coordo[0][1], "Cititi fisierul: readME.txt");
            delay(1500);
            system("readME.txt");
        }
        else
        {
            if(first_command)
            {
                file_explorer();
                first_command=0;
            }
            if(which_button==1)///arhivare
            {
                graphics_ALGbuttons();
                if(alg=='H')
                    highlight(coordo[10][0], coordo[10][1], coordo[10][2], coordo[10][3]);
                if(alg=='L')
                    highlight(coordo[11][0], coordo[11][1], coordo[11][2], coordo[11][3]);
                setcolor(15);
                settextstyle(SMALL_FONT, 0, 8);
                outtextxy(340, 50, "ALEGE FISIERE PENTRU COMPRIMARE");
            }
            else///dezarhivare
            {
                setcolor(15);
                settextstyle(SMALL_FONT, 0, 8);
                outtextxy(300, 50, "ALEGE ARHIVA (UNA SINGURA)");
            }
            graphics_GLOBALbuttons(5);
        }
        graphics_GLOBALbuttons(4);
    }
}
