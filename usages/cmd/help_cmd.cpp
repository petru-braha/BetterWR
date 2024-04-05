#include "help_cmd.h"

void etern_gui()//all gui in one place
{
    short screen_x = 0, screen_y = 0;
    define_fullscreen(screen_x, screen_y);
    if(screen_x==0 || screen_y==0)
        exit(1);

    initwindow(screen_x, screen_y, "", -3, -3);
    start_graphics(1);
    graphics_MENUbuttons();
    commands();
    closegraph();
}

void display_instructions_bash(){
    std::cout << "Usage: " << "<operation> <algorithm> <nr_input_files> <input_file_paths> <output_path>\n";
    std::cout << "Check for syntax errors:\n";
    std::cout << "operations: 'compress' / 'decompress'\n";
    std::cout << "algorithms: 'HUF' / 'LZW'\n";
    std::cout << "check if the number of paths given is < 10 and is equal with nr_input_files.\ncheck if the paths are valid.\n\n";
}
#include <filesystem>
bool verification(int argc, char** argv)
{
    if (argc < 6)
    {
        std::cout << "Usage: " << "<operation> <algorithm> <nr_input_files> <input_file_paths> <output_path>\n";
        return false;
    }

    if(strcmp(argv[1], "compress") && strcmp(argv[1], "decompress"))
    {
        std::cout<<"error: invalid first argument.\n\n";
        display_instructions_bash();
        return false;
    }

    if(strcmp(argv[2], "HUF") && strcmp(argv[2], "LZW"))
    {
        std::cout<<"error: invalid second argument.\n\n";
        display_instructions_bash();
        return false;
    }

    int nr = 0;
    for(int i = 0; argv[3][i]; i++)
        nr = nr * 10 + (argv[3][i] - '0');
    if(nr + 5 != argc || nr <= 0 || nr > 10)
    {
        std::cout<<"error: invalid third argument.\n\n";
        display_instructions_bash();
        return false;
    }

    //validation of paths
    for(int i=0; i<nr; i++)
        if(std::filesystem::exists(argv[i + 4]) == 0)
        {
            std::cout<<"error: invalid input_path argument.\n\n";
            display_instructions_bash();
            return false;
        }

    if(std::filesystem::exists(argv[argc - 1]) == 0)
    {
        std::cout<<"error: invalid output_path argument.\n\n";
        display_instructions_bash();
        return false;
    }

    return true;
}
