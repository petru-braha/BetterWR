#include <graphics.h>

#include "../../admin/libraries.h"
#include "../middle/middle.h"
#include "packing_functions.h"

#include "graphics_functions.h"
#include "usage/explorer.h"

struct point{
    int x, y;
} mouse;

void gui_commands_STOP()
{
    if(click_on_button(mouse.x, mouse.y, 3))
    {
        highlight(coordo[3][0], coordo[3][1], coordo[3][2], coordo[3][3]);
        delay(100);
        closegraph();
        exit(0);
    }
}

void gui_commands_go_back(int& which_button, bool& first_command)
{
    if(file_accessedPATH[0])
    {
        if(strlen(file_accessedPATH)<4)
        {
            if(click_on_button(mouse.x, mouse.y, 4))
            {
                highlight(coordo[4][0], coordo[4][1], coordo[4][2], coordo[4][3]);
                delay(100);
                graphics_GLOBALbuttons(4);
                strcpy(file_accessedPATH, "\0");
                strcpy(file_lastOPENED, "\0");
                file_explorer();

                unit=0;
                for(int i=0; i<nr_files_for_tar; i++)
                {
                    char file_name[MAX];
                    strcpy(file_name, get_FILEname(input_for_paths[i]));
                    setcolor(15);
                    line(1040, 195+unit, 1440, 195+unit);

                    settextstyle(SMALL_FONT, 0, 10);
                    outtextxy(1040, 200+unit, file_name);

                    if(strchr(file_name, '.')==NULL)
                        readimagefile("photos/folder2.jpg", 1010, 200+unit, 1035, 235+unit);
                    else
                        readimagefile("photos/txt2.jpg", 1010, 200+unit, 1035, 235+unit);
                    unit+=45;
                    line(1040, 195+unit, 1440, 195+unit);
                }
            }
        }
        else
        {
            if(click_on_button(mouse.x, mouse.y, 4))
            {
                highlight(coordo[4][0], coordo[4][1], coordo[4][2], coordo[4][3]);
                delay(100);

                graphics_GLOBALbuttons(4);
                strcpy(file_lastOPENED, get_FILEname(file_accessedPATH));
                strcpy(strstr(file_accessedPATH, file_lastOPENED), "\0");
                strcpy(file_lastOPENED, get_FILEname(file_accessedPATH));
                std::cout<<file_accessedPATH<<'\n';
                explorer("directory_iterator");
            }
        }
    }
    else
    {
        if(click_on_button(mouse.x, mouse.y, 4))
        {
            highlight(coordo[4][0], coordo[4][1], coordo[4][2], coordo[4][3]);
            delay(100);
            which_button=0;
            first_command=1;
            alg=0;
            //delete data
            for(int i=0; i<nr_files_for_tar; i++)
                memset(input_for_paths[i], 0, sizeof input_for_paths[i]);
            nr_files_for_tar=0;
            start_graphics(0);
            graphics_MENUbuttons();
        }
    }
}

void gui_commands_alg(int& which_button)
{
    if(which_button==1)
    {
        if(click_on_button(mouse.x, mouse.y, 10))
        {
            alg='H';
            graphics_ALGbuttons();
            highlight(coordo[10][0], coordo[10][1], coordo[10][2], coordo[10][3]);
        }
        else
        {
            if(click_on_button(mouse.x, mouse.y, 11))
            {
                alg='L';
                graphics_ALGbuttons();
                highlight(coordo[11][0], coordo[11][1], coordo[11][2], coordo[11][3]);
            }
        }
    }
}

void gui_commands_deselect()
{
    for(int i=0; i<11; i++)
        if(click_on_file(mouse.x, mouse.y, i))
        {
            graphic_x(file_coordo[i][0], file_coordo[i][1], file_coordo[i][2], file_coordo[i][3]);
            delay(200);
            strcpy(input_for_paths[i], "\0");
            nr_files_for_tar--;
            for(int j=i; j<nr_files_for_tar; j++)
                strcpy(input_for_paths[j], input_for_paths[j+1]);
            setcolor(0);
            setfillstyle(SOLID_FILL, 0);
            bar(1000, 195, 1450,890);
            unit=0;
            for(int i=0; i<nr_files_for_tar; i++)
            {
                char file_name[MAX];
                strcpy(file_name, get_FILEname(input_for_paths[i]));
                get_FILEname(input_for_paths[i]);
                setcolor(15);
                line(1040, 195+unit, 1440, 195+unit);
                file_coordo[i][0]=1000;
                file_coordo[i][1]=195+unit;
                file_coordo[i][2]=1440;

                settextstyle(SMALL_FONT, 0, 10);
                outtextxy(1040, 200+unit, file_name);

                if(strchr(file_name, '.')==NULL)
                    readimagefile("photos/folder2.jpg", 1010, 200+unit, 1035, 235+unit);
                else
                    readimagefile("photos/txt2.jpg", 1010, 200+unit, 1035, 235+unit);
                unit+=45;
                line(1040, 195+unit, 1440, 195+unit);
                file_coordo[i][3]=195+unit;
            }
            graphics_GLOBALbuttons(5);
            break;
        }
}
void gui_commands_ready(int& which_button)/// este de fapt ce se intampla la boot!!!! //trebuie impartita in functii mai mici
{
    if(click_on_button(mouse.x, mouse.y, 5))
    {
        highlight(coordo[5][0], coordo[5][1], coordo[5][2], coordo[5][3]);
        delay(100);
        graphics_GLOBALbuttons(5);
        if(nr_files_for_tar==0 && (alg!='H' && alg!='L'))
        {
            std::cout<<nr_files_for_tar;
            std::cout<<"error: please choose an algorithm";
        }
        else
        //
        last_step=1;
    }
}
void gui_commands_sidebar()
{
    for(int i=6; i<10; i++)
    {
        if(click_on_button(mouse.x, mouse.y, i))
        {
            highlight(coordo[i][0], coordo[i][1], coordo[i][2], coordo[i][3]);
            delay(100);
            graphics_EXPLbuttons();

            ///annocement_button(mode de scris/mode de inchis)
            char new_name[MAX], temp[MAX];
            std::cin>>new_name;
            strcpy(temp, file_accessedPATH);
            strcat(temp, new_name);

            switch(i)
            {
            case 7:
                mkdir(temp);
                explorer("directory_iterator");
                break;
            case 8:
                system(temp); //deschizi fisierul
                explorer("directory_iterator");
                break;
            }
            break;
        }
    }
}

void gui_commands_folder_manipulation()
{
    for(int i=11; i<11+file_nr_visible; i++)
        if(click_on_file(mouse.x, mouse.y, i))
        {
            highlight(file_coordo[i][0], file_coordo[i][1], file_coordo[i][2], file_coordo[i][3]);
change_MYMIND:
            while(1)
            {
                bool ok=0, change_of_mind=0;
                getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y);
                if(mouse.x!=-1 && mouse.y!=-1)
                {
                    //se schimba input
                    for(int j=11; j<11+file_nr_visible; j++)
                        if(click_on_file(mouse.x, mouse.y, j) && i!=j)
                        {
                            if(file_accessedPATH[0]==0)
                                explorer("partitive");
                            else
                                explorer("directory_iterator");
                            highlight(file_coordo[j][0], file_coordo[j][1], file_coordo[j][2], file_coordo[j][3]);
                            change_of_mind=1;
                            i=j;
                            break;
                        }
                    if(change_of_mind)
                        goto change_MYMIND;
                    if(click_on_button(mouse.x, mouse.y, 3))//stop
                    {
                        highlight(coordo[3][0], coordo[3][1], coordo[3][2], coordo[3][3]);
                        delay(100);
                        closegraph();
                        exit(0);
                    }
                    if(click_on_button(mouse.x, mouse.y, 4))//inapoi
                    {
                        highlight(coordo[4][0], coordo[4][1], coordo[4][2], coordo[4][3]);
                        delay(100);
                        graphics_GLOBALbuttons(4);
                        ok=1;
                        if(file_accessedPATH[0]==0)
                            explorer("partitive");
                        else
                            explorer("directory_iterator");
                    }
                    if(click_on_button(mouse.x, mouse.y, 6) && file_accessedPATH[0] && nr_files_for_tar<11)//selecteaza
                    {
                        ///de tradus, aranjat, gata_button
                        bool dir=0;
                        highlight(coordo[6][0], coordo[6][1], coordo[6][2], coordo[6][3]);
                        delay(100);
                        graphics_EXPLbuttons();

                        strcpy(file_lastOPENED, file_visible[i]);
                        char temp[MAX];
                        strcpy(temp, file_accessedPATH);
                        strcat(temp, file_lastOPENED);
                        if(is_folder(temp))
                        {
                            strcat(temp, "/");
                            dir=1;
                        }

                        strcpy(input_for_paths[nr_files_for_tar++], temp);
                        graphics_selected(get_FILEname(temp), nr_files_for_tar);
                        explorer("directory_iterator");
                        ok=1;
                    }
                    if(click_on_button(mouse.x, mouse.y, 9) && file_accessedPATH[0]) //delete
                    {
                        highlight(coordo[9][0], coordo[9][1], coordo[9][2], coordo[9][3]);
                        delay(100);
                        graphics_EXPLbuttons();

                        strcpy(file_lastOPENED, file_visible[i]);
                        char temp[MAX];
                        strcpy(temp, file_accessedPATH);
                        strcat(temp, file_lastOPENED);

                        if(is_folder(temp))
                            rmdir(temp);
                        else
                            remove(temp);
                        explorer("directory_iterator");
                        ok=1;
                    }

                    if(click_on_file(mouse.x, mouse.y, i))//accesez calea
                    {
                        ok=1;
                        strcpy(file_lastOPENED, file_visible[i]);
                        strcat(file_accessedPATH, file_lastOPENED);
                        if(is_folder(file_accessedPATH))
                        {
                            if(strlen(file_accessedPATH)>=4)
                                strcat(file_accessedPATH, "/");
                            std::cout<<file_accessedPATH<<'\n';
                            explorer("directory_iterator");
                        }
                        else
                        {
                            char exe[MAX];
                            strcpy(exe, file_accessedPATH);
                            strcpy(strstr(file_accessedPATH, file_lastOPENED), "\0");
                            strcpy(file_lastOPENED, get_FILEname(file_accessedPATH));
                            std::cout<<file_accessedPATH<<'\n';
                            explorer("directory_iterator");
                            system(exe);
                        }
                    }
                }
                if(ok)
                    break;
            }
            break;//pt for
        }
}


void gui_commands_firstStep_menu(int &which_button){
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
void gui_commands_secondStep_decideOperation(char file_accessedPATH[], int which_button, bool &first_command, char& alg){
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

void gui_command_thirdStep(int& which_button, bool& first_command){
    while(last_step == false)
    {
        getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y);
        if(mouse.x!=-1 && mouse.y!=-1)
        {
            commands_STOP();
            commands_go_back(which_button, first_command);
            commands_alg(which_button);
            commands_deselect();
            commands_ready(which_button);
            commands_sidebar();
            commands_folder_manipulation();
        }
    }
}

void gui_commands(){
    bool first_command = true, last_step = false;
    int which_button = 0;

    while(last_step == false)
    {
        commands_firstStep_menu(which_button);
        commands_secondStep_decideOperation(file_accessedPATH, which_button, first_command, alg);
        command_thirdStep(which_button, first_command);
    }
}

void graphical_user_interface(){
    short screen_x = 0, screen_y = 0;
    define_fullscreen(screen_x, screen_y);
    if (screen_x == 0 || screen_y == 0)
        exit(1);

    initwindow(screen_x, screen_y, "", -3, -3);
    start_graphics(1);
    graphics_MENUbuttons();
    gui_commands();
    closegraph();
}
