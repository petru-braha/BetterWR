short int file_coordo[MAX][4];

bool click_on_file(int x, int y, int which_button)
{
    if(x>=file_coordo[which_button][0] && x<=file_coordo[which_button][2])
        if(y>=file_coordo[which_button][1] && y<=file_coordo[which_button][3])
            return 1;
    return 0;
}

void graphics_selected_file(char file_name[], int nr_files_for_tar)
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

void delete_selected_file(int x1, int y1, int x2, int y2)
{
    setcolor(4);
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
