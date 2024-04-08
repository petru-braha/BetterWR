#include <graphics.h>
//puntea dintre main_gui si foldere

void explorer(char mode[])
{
    //sterge highlight
    setfillstyle(SOLID_FILL, 0);
    bar(230, 143, 976, 920);

    int y=0;
    file_nr_visible = 0;
    settextstyle(SMALL_FONT, 0, 8);
    if(strcmp(mode, "partitive")==0)
    {
        char last_partitive=0;
        for(int i='A'; i<='Z'; i++)
        {
            char s[5]="\0";
            s[0]=char(i);
            s[1]=':';
            s[2]='/';
            s[3]='\0';
            if(is_folder(s))
            {
                setcolor(15);
                line(230, 143+y, 974, 143+y);

                file_coordo[11+i-'C'][0]=230;
                file_coordo[11+i-'C'][1]=143+y;
                file_coordo[11+i-'C'][2]=974;

                setcolor(9);
                readimagefile("photos/folder2.jpg", 235, 150+y, 260, 150+y+25);
                outtextxy(270, 150+y, s);
                y+=40;

                file_coordo[11+i-'C'][3]=143+y;
                file_nr_visible++;

                strcpy(file_visible[11+i-'C'], s);
            }
        }
        setcolor(15);
        line(230, 143+y, 974, 143+y);
    }
    else
    {
        if(strcmp(mode, "directory_iterator")==0)
        {
            //calea unde ai ajuns
            graphic_button(320, 90, 960, 130);
            setcolor(9);
            settextstyle(SMALL_FONT, 0, 8);
            outtextxy(330, 100, file_accessedPATH);
            int index=0;
            for(auto & p : std::filesystem::directory_iterator(file_accessedPATH))
                if(index<19)
                {
                    //gen las sa se vada doar 15 elemente maxim
                    char s[MAX]="\0";
                    strcpy(s, p.path().string().c_str());

                    strcpy(file_visible[11+index++], get_FILEname(s));
                    setcolor(15);
                    line(230, 143+y, 974, 143+y);

                    file_coordo[10+index][0]=230;
                    file_coordo[10+index][1]=143+y;
                    file_coordo[10+index][2]=974;

                    setcolor(9);
                    if(is_folder(s))
                        readimagefile("photos/folder2.jpg", 235, 150+y, 260, 150+y+25);
                    else
                        readimagefile("photos/txt2.jpg", 235, 150+y, 260, 150+y+25);
                    outtextxy(270, 150+y, file_visible[11+index-1]);
                    y+=40;

                    file_coordo[10+index][3]=143+y;
                    file_nr_visible++;
                }
            setcolor(15);
            line(230, 143+y, 974, 143+y);
        }
    }
}

void file_explorer()
{
    readimagefile("photos/file explorer.jpg", 0, 0, width, height);
    graphics_EXPLbuttons();
    explorer("partitive");
    graphics_GLOBALbuttons(3);
}
