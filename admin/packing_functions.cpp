#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <direct.h>
#define MAX 300

const char typed_end_of_file[] = "\n\n*EOF_no_more_content_to_be_displayed*\n\n";
const char typed_end_of_directory[] = "EOD_no_more_files_to_be_analysed_";

void change_extension(char type[], char path_output[]) //are ca input un fisier tar corect
{
    if(std::filesystem::path(path_output).extension()==".txt")
        strcpy(strstr(path_output, ".txt"), type);
    else
        strcpy(strchr(path_output, '.'), ".txt");
}

char* get_FILEname(char source_path[])
{
    size_t length = strlen(source_path), index_context = 0;
    for(size_t i = 0; i < length - 1; i++)
        if(source_path[i]=='/')
            index_context = i;
    return source_path + index_context + 1;
}

//output is in temp
void help_build(char path_of_file[], FILE* p_bar, FILE* p_components, char identation[])
{
    const std::filesystem::path path(path_of_file); std::error_code ec;
    if (std::filesystem::is_directory(path, ec))//folder
    {
        //pun in fisier numele folderului
        fputs(identation, p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
        fputs("\n", p_bar);
        strcat(identation, "\t\0");

        for (auto& p : std::filesystem::directory_iterator(path_of_file))//ia fisierele alfabetic
        {
            if (p.path().empty() == false)
            {
                //transformare din string in char(BUGS!)
                char file_name_from_folder[MAX];
                strcpy(file_name_from_folder, p.path().string().c_str());
                for (size_t i = 0; i < strlen(file_name_from_folder); i++)
                    if (file_name_from_folder[i] == 92)
                        file_name_from_folder[i] = '/';
                file_name_from_folder[strlen(file_name_from_folder)] = '\0';

                help_build(file_name_from_folder, p_bar, p_components, identation);
                memset(file_name_from_folder, 0, sizeof(file_name_from_folder));
            }
        }

        //END
        identation[strlen(identation) - 1] = '\0';
        fputs(identation, p_bar);
        fputs(typed_end_of_directory, p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
        fputs("/\n", p_bar);
    }
    else //normal file
    {
        p_components = fopen(path_of_file, "rb");
        if (p_components == nullptr)
        {
            std::cout << "error - composition: missing/corrupted file";
            return;
        }

        fputs(identation, p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
        fputs("\n\n", p_bar);

        char temp;
        while ((temp = fgetc(p_components)) != EOF)
            fputc(temp, p_bar);
        fputs(typed_end_of_file, p_bar);

        fclose(p_components);
    }
}
void build_tar(short nr_paths, char** paths_input)
{
    char identation[MAX] = { 0 };
    FILE* p_bar = nullptr, * p_components = nullptr;
    p_bar = fopen("files/temp.bin", "wb");
    if (p_bar == nullptr)
    {
        std::cout << "error - composition: the requested file is missing.\n";
        return;
    }

    for(int i=0; i < nr_paths; i++)
        help_build(paths_input[i], p_bar, p_components, identation);

    fclose(p_bar);
}

void help_decompose(char line[], char destination[], FILE* p_bar, FILE* p_components, bool condition)
{
    char file_separator[MAX] = "*5EPArAToR*";
    if (condition == 0)
    {
        line[strlen(line) - 1] = '\0';
        while (line[0] == '\t')
            strcpy(line, line + 1);
        if (line[strlen(line) - 1] == '/')//NUME FOLDER
        {
            char previous_line[MAX];
            strcpy(previous_line, line);

            char new_destination[MAX];
            strcpy(new_destination, destination);
            //creare folder
            strcat(new_destination, line);
            mkdir(new_destination);

            fgets(line, MAX, p_bar);
            while (strstr(line, "end_oF_") == NULL && strstr(line, previous_line) == NULL)
            {
                help_decompose(line, new_destination, p_bar, p_components, 0);
                fgets(line, MAX, p_bar);
            }
            return;
        }
        else//NUME FISIER
        {
            char new_destination[MAX];
            strcpy(new_destination, destination);
            strcat(new_destination, line);
            condition = 1;
            fgets(line, MAX, p_bar);
            help_decompose(line, new_destination, p_bar, p_bar, 1);
        }
    }
    else///content
    {
        p_components = fopen(destination, "w");
        if (p_components)
        {
            while (1)//adauga la final de fisier "\n\n"
            {
                fgets(line, MAX, p_bar);
                if (strstr(line, file_separator))
                {
                    fgets(line, MAX, p_bar);
                    break;
                }
                fputs(line, p_components);
            }
        }
        else
        {
            std::cout << "error - decomposition: can not write the files.\n";
            return;
        }
        condition = 0;
        fclose(p_components);
    }
}
void decompose_tar(char* path_output, char* output_name)
{
    char* path_input = "files/temp.txt";
    FILE* p_bar = nullptr, * p_components = nullptr;
    p_bar = fopen(path_input, "rb");
    if (p_bar == nullptr)
    {
        std::cout << "error - decomposition: the requested file is missing.\n";
        return;
    }

    path_output = strcat(path_output, output_name); //revision please
    mkdir(path_output);

    //prima oara citesteste calea, afisarea pana la intalnirea file_separator
    char line[MAX];
    while (fgets(line, MAX, p_bar))
        help_decompose(line, path_output, p_bar, p_components, 0);
    /*
    0-NU STIU, prima linie
    1-DACA FIX INAINTE A FOST ANUNTAT NUME DE CEVA
    */
    fclose(p_bar);
}
