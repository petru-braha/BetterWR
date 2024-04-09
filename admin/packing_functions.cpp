#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <direct.h>
#define MAX 300

void change_extension(char type[], char path_output[]) //are ca input un fisier tar corect
{
    if(std::filesystem::path(path_output).extension()==".txt")
        strcpy(strstr(path_output, ".txt"), type);
    else
        strcpy(strchr(path_output, '.'), ".txt");
}

char* get_FILEname(char source_path[])
{
    int length=strlen(source_path);
    int index_context=0;
    for(int i=0; i<length-1; i++)
        if(source_path[i]=='/')
            index_context=i;
    return source_path+index_context+1;
}

//output is in temp
void help_build(char path_of_file[], FILE* p_bar, FILE* p_components, char identation[])
{
    char file_separator[MAX] = "*5EPArAToR*";
    const std::filesystem::path path(path_of_file); std::error_code ec;
    if (std::filesystem::is_directory(path, ec))//folder
    {
        //pun in fisier numele folderului
        fputs(identation, p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
        fputs("/\n", p_bar);
        strcat(identation, "\t\0");

        for (auto& p : std::filesystem::directory_iterator(path_of_file))//ia fisierele alfabetic
        {
            if (p.path().empty() == false)
            {
                //transformare din string in char(BUGS!)
                char IN_folder[MAX];
                strcpy(IN_folder, p.path().string().c_str());
                for (size_t i = 0; i < strlen(IN_folder); i++)
                    if (IN_folder[i] == 92)
                        IN_folder[i] = '/';
                IN_folder[strlen(IN_folder)] = '\0';

                help_build(IN_folder, p_bar, p_components, identation);
                memset(IN_folder, 0, sizeof IN_folder);
            }
        }

        //END
        identation[strlen(identation) - 1] = '\0';
        fputs(identation, p_bar);
        fputs("end_oF_", p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
        fputs("/\n", p_bar);
    }
    else//normal file
    {
        p_components = fopen(path_of_file, "r");
        if (p_components == NULL) ///i love my girlfriend!!!
        {
            std::cout << "error - composition: missing/corrupted file";
            return;
        }

        fputs(identation, p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
        fputs("\n\n", p_bar);

        //copierea informatiei
        char temp;
        while ((temp = fgetc(p_components)) != EOF)
            fputc(temp, p_bar);

        fputs("\n\n", p_bar);
        fputs(file_separator, p_bar);
        fputs("\n\n", p_bar);

        fclose(p_components);
    }
}
void build_tar(short nr_paths, char** paths_input)
{
    char identation[MAX] = { 0 };
    char path_of_file[MAX];
    FILE* p_bar = nullptr, * p_components = nullptr;
    p_bar = fopen("files/temp.txt", "wb");
    if (p_bar == nullptr)
    {
        std::cout << "error - composition: the requested file is missing.\n";
        return;
    }

    int index = 0, k = nr_paths;
    while (index < k)
    {
        strcpy(path_of_file, paths_input[index]);
        help_build(path_of_file, p_bar, p_components, identation);
        index++;
    }

    fclose(p_bar);
}

//input is in temp
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
void decompose_tar(char* path_input)
{
    FILE* p_bar = nullptr, * p_components = nullptr;
    p_bar = fopen(path_input, "r");
    if (p_bar == nullptr)
    {
        std::cout << "error - decomposition: the requested file is missing.\n";
        return;
    }

    char path[MAX];
    strcpy(path, "/files/decoded/unpack");
    mkdir(path);

    //prima oara citesteste calea, afisarea pana la intalnirea file_separator
    char line[MAX];
    while (fgets(line, MAX, p_bar))
        help_decompose(line, path, p_bar, p_components, 0);
    /*
    0-NU STIU, prima linie
    1-DACA FIX INAINTE A FOST ANUNTAT NUME DE CEVA
    */
    fclose(p_bar);
}
