#ifndef FUNCTIONAL_HELP_H_INCLUDED
#define FUNCTIONAL_HELP_H_INCLUDED

void display_paths(point measure, short unit, std::string accessed_path, bool first_execution)
{
    //delete visual
    print_box(2*measure.x, 3*measure.y, 13*measure.x, 11*measure.y, "", unit, color_black, 0);
    //delete functional
    for(size_t i = 0 ; i < max_nr_paths_displayed && first_execution == false; i++)
    {
        delete explorer_files[i];
        explorer_files[i] = nullptr;
    }

    size_t index = 0;
    if(accessed_path == "") // display volumes
    {
        std::vector<std::string> drives = list_volumes();
        for(std::string current : drives)
        {
            screen_path* previous = (index == 0 ? nullptr : explorer_files[index - 1]);
            explorer_files[index] = new screen_path(previous, (char*)current.c_str());
            explorer_files[index]->visual();
            index++;
        }

        print_box(2*measure.x, 2*measure.y, 18*measure.x, 3*measure.y, accessed_path.c_str(), unit, color_brown, expl_font_size);
        settextstyle(text_font, HORIZ_DIR, expl_font_size);
        return;
    }

    for(auto & p : std::filesystem::directory_iterator(accessed_path))
    {
        char s[MAX] = "\0";
        strcpy(s, p.path().string().c_str()); std::string temp = get_file_name(s);
        strcpy(s, temp.c_str());
        if(std::filesystem::is_directory(p.path()))
           strcat(s, "/\0");

        screen_path* previous = index == 0 ? nullptr : explorer_files[index-1];
        explorer_files[index] = new screen_path(previous, s);
        explorer_files[index]->visual();
        index++;

        if(index == max_nr_paths_displayed)
            break;
    }
    print_box(2*measure.x, 2*measure.y, 18*measure.x, 3*measure.y, accessed_path.c_str(), unit, color_brown, expl_font_size);
}

void path_manipulation(point mouse, point measure, short unit, screen_path*& pressedd_file, std::string & accessed_path, std::string & status)
{
    if(pressedd_file == nullptr)
    {
        for(size_t i = 0; explorer_files[i] && pressedd_file == nullptr; i++)
            pressedd_file = explorer_files[i]->functional(mouse, status);
        return;
    }

    screen_path* temp = nullptr;
    for(size_t i = 0; explorer_files[i] && temp == nullptr; i++)
        temp = explorer_files[i]->functional(mouse, status);
    if(temp == nullptr)
        return;

    if(temp == pressedd_file) // double click
    {
        accessed_path += status;
        if(std::filesystem::is_directory(accessed_path))
        {
            display_paths(measure, unit, accessed_path, false);
            pressedd_file = nullptr;
        }
        else // just txt and exe
        {
            std::string execution_path = "";
            execution_path += accessed_path;
            system(execution_path.c_str());
        }
    }
    else // click on something else
    {
        pressedd_file->visual(); // erase highlight
        pressedd_file->selected = false;
        pressedd_file = temp;
        pressedd_file->selected = true;
    }
}

void visual_delete_selected(point mouse, point measure, short unit)
{
    if(selected_files[0] == nullptr)
        return;

    selected_screen_path* flag = nullptr; // if deleted
    short i = 0;
    for(; selected_files[i] && i < max_nr_paths_selectedd; i++)
    {
        if(selected_files[i]->functional(mouse))
        {
            flag = selected_files[i];
            break;
        }
    }

    if(i == max_nr_paths_selectedd || flag == nullptr)
        return;

    short j = i;
    while(selected_files[j + 1])
    {
        selected_files[j]->mmcpy(selected_files[j + 1]);
        j++;
    }
    delete selected_files[j];
    selected_files[j] = nullptr;

    // display
    print_box(13*measure.x, 3*measure.y, 18*measure.x, 11*measure.y, "", unit, color_brown, expl_font_size);
    setcolor(color_white);
    B_ACTN->visual(unit);
    for(short i = 0; i < j; i++)
        selected_files[i]->visual();
}

/// well implemented function, old library

/*
char* choose_output_path()
{
    // init visual
    char* output_path = new char[MAX]{0};
    point screen("fullscreen"), measure("square_measure");
    short unit = point("unit").x;
    int new_window = initwindow(screen.x, screen.y, "", -3, -3);
    readimagefile("constant files/media/layout/background.jpg", 0, 0, screen.x, screen.y);

    // visual
    print_box(13*measure.x, 3*measure.y, 18*measure.x, 11*measure.y, "", unit, 0, 0);
    B_BACK_EXPL->visual(unit);
    B_ACTN->visual(unit);

    // functional
    screen_path* new_explorer_files[max_nr_paths_displayed];
    for(size_t i = 0; i < max_nr_paths_displayed; i++)
        new_explorer_files[i] = nullptr;
    point mouse;
    std::string accessed_path = "";
    std::string status = "";
    screen_path* pressedd_file = nullptr;
    display_paths(measure, unit, "");

    bool condition = false;
    while(condition == false)
    {
        getmouseclick(outside_left_click, (int&)mouse.x, (int&)mouse.y);
        if(mouse.x == -1)
            getmouseclick(outside_double_click, (int&)mouse.x, (int&)mouse.y);

        if(B_BACK_EXPL->functional(mouse, unit))
        {
            if(accessed_path == "")
            {
                delete output_path;
                output_path = nullptr;
                break;
            }

            delete_dir_accessed(accessed_path);
            display_paths(measure, unit, accessed_path);
        }

        path_manipulation(mouse, measure, unit, pressedd_file, accessed_path, status);
        if(B_ACTN->functional(mouse, unit))
        {
            condition = true;
            strcpy(output_path, accessed_path.c_str());
        }
    }

    for(size_t i = 0; new_explorer_files[i]; i++)
        delete new_explorer_files[i];

    closegraph(new_window);
    return output_path;
}
*/

void action_button(point measure, short unit, bool & condition)
{
    // decide option, algorithm, paths_input
    size_t nr_paths = 0;
    for(; selected_files[nr_paths]; nr_paths++);

    if(nr_paths == 0) return;
    char** paths_input = new char*[nr_paths];
    for(size_t i = 0; selected_files[i]; i++)
        paths_input[i] = selected_files[i]->full_path;

    //char* path_output = choose_output_path();
    std::cout << "please type the desired location (absolute path) of the output :\n";
    std::cout << "(if you changed your mind, press enter)\n";
    char* path_output = new char[MAX]{0};
    std::cin.getline(path_output, MAX);
    if(strlen(path_output) == 0 || std::filesystem::exists(path_output) == 0)
    {
        system("cls");
        delete[] path_output;
        return;
    }

    // decide visual_limits
    // 19 == 6 + 7 + 6
    // 12 == 4 + 4 + 4

    // decide name
    char* output_name = nullptr;
    const short x1 = 6*measure.x, y1 = 5*measure.y, x2 = 13*measure.x, y2 = 7*measure.y;
    pop_up P(point(x1, y1), point(x2, y2));
    P.functional();
    output_name = P.text;

    if(output_name == nullptr)
    {
        system("cls");
        delete[] path_output;
        return;
    }

    condition = true;
    very_last_step(B_ACTN->get_text(), B_ALGO->get_text(), nr_paths, paths_input, path_output, output_name);

    system("cls");
    delete[] paths_input;
    delete[] path_output;
}

#endif // FUNCTIONAL_HELP_H_INCLUDED
