#include <graphics.h>
#include "../graphics_functions.h"
#include "../global_variables.h"

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
