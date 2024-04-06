// g++ -std=c++17 main.cpp huffmanFunctions.cpp lzwFunctions.cpp -o "exe_name"
#include <iostream>
#include <cstring>
#include <graphics.h>
#include <filesystem>
#include "../admin/packing_functions.h"

#include "middle/middle.h"
#include "gui/main_gui.h"

void display_instructions_bash() {
    std::cout << "Usage: " << "<operation> <algorithm> <nr_input_files> <input_file_paths> <output_path>\n";
    std::cout << "Check for syntax errors:\n";
    std::cout << "operations: 'compress' / 'decompress'\n";
    std::cout << "algorithms: 'HUF' / 'LZW'\n";
    std::cout << "check if the number of paths given is < 10 and is equal with nr_input_files.\ncheck if the paths are valid.\n\n";
}
bool verification(int argc, char** argv){
    if (argc < 7)
    {
        std::cout << "Usage: " << "<operation> <algorithm> <nr_input_files> <input_file_paths> <output_path> <output_name>\n";
        return false;
    }

    if (strcmp(argv[1], "compress") && strcmp(argv[1], "decompress"))
    {
        std::cout << "error: invalid first argument.\n\n";
        display_instructions_bash();
        return false;
    }

    if (strcmp(argv[2], "HUF") && strcmp(argv[2], "LZW"))
    {
        std::cout << "error: invalid second argument.\n\n";
        display_instructions_bash();
        return false;
    }

    int nr = 0;
    for (int i = 0; argv[3][i]; i++)
        nr = nr * 10 + (argv[3][i] - '0');
    if (nr + 5 != argc || nr <= 0 || nr > 10)
    {
        std::cout << "error: invalid third argument.\n\n";
        display_instructions_bash();
        return false;
    }

    //validation of paths
    for (int i = 0; i < nr; i++)
        if (std::filesystem::exists(argv[i + 4]) == 0)
        {
            std::cout << "error: invalid input_path argument.\n\n";
            display_instructions_bash();
            return false;
        }

    if (std::filesystem::exists(argv[argc - 2]) == 0)
    {
        std::cout << "error: invalid output_path argument.\n\n";
        display_instructions_bash();
        return false;
    }

    for (int i = 0; i < strlen(argv[argc - 1]); i++)
        if (argv[argc - 1][i] < 'A' || argv[argc - 1][i] > 'Z' || (argv[argc - 1][i] > 'Z' && argv[argc - 1][i] < 'a'))
        {
            std::cout << "error: invaid name.\n\n";
            return false;
        }
    return true;
}

void main(int argc, char** argv)
{
    ///GUI
    if(argc == 1)
    {
        graphical_user_interface();
        return;
    }

    if(verification(argc, argv) == false) //checks if the arguments are valid
        return;

    ///complex bash commands
    //initialisations
    //verification not necessary <= verification function does it
    operation = argv[1];
    algorithm = argv[2];

    if(argv[3][1]) nr_paths = 10;
    else nr_paths = argv[3][0] - '0';

    for(int i=0; i< nr_paths; i++)
        paths_input[i] = argv[i+4];
    path_output = argv[argc - 2];
    output_name = argv[argc - 1];

    last_step(operation, algorithm, nr_paths, paths_input, path_output, output_name);
    return;
}
