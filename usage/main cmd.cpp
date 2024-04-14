#include "middle/middle.h"
void graphical_user_interface();

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        graphical_user_interface();
        return 0;
    }

    if(argument_verification(argc, argv) == false) //checks if the arguments are valid
        return 1;

    char* operation = argv[1];
    char* algorithm = argv[2];

    short nr_paths = 0;
    if(argv[3][1]) nr_paths = 10;
    else nr_paths = argv[3][0] - '0';

    char** paths_input = new char* [nr_input_paths];
    for(int i = 0; i < nr_paths; i++)
        paths_input[i] = argv[i+4];
    char* path_output = argv[argc - 2];
    char* output_name = argv[argc - 1];

    //very_last_step(operation, algorithm, nr_paths, paths_input, path_output, output_name);
    return 0;
}
