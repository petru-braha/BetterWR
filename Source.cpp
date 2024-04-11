#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <filesystem>//verific foldere
#include <direct.h>//creare foldere

#define MAX_VALUE 300
using namespace std;

struct stack {
    int nr_elem;
    char folder_names[MAX_VALUE][MAX_VALUE];
} S;

int nr_files_for_tar = 2;

char input_for_paths[MAX_VALUE][MAX_VALUE] = { "C:/Users/PETRU/Desktop/IP/files/element 1/","C:/Users/PETRU/Desktop/IP/files/element 2/" };

char file_separator[MAX_VALUE] = "RobertsiCuPetrusunt-CEi+mai=taariiDinaceasta_gakl0r-fp[zie]1ru928.g";
char identation[MAX_VALUE];

char path_of_tar[MAX_VALUE] = "C:/Users/PETRU/Desktop/IP/myfiles.txt";
char path_decompose[] = "C:/Users/PETRU/Desktop/IP/";
char decompose_name[] = "unpack/";//NUME FOLDER FISIERE DECOMPRIMATE

char file_name[MAX_VALUE];

void get_FILEname(char source_path[])
{
    memset(file_name, 0, sizeof file_name);
    for (int i = strlen(source_path) - 1; i; i--)
    {
        if (source_path[i] == 47)
        {
            if (i != strlen(source_path) - 1)
                break;
        }
        else
            file_name[strlen(file_name)] = source_path[i];
    }
    file_name[strlen(file_name)] = '\0';
    strcpy(file_name, strrev(file_name));
    file_name[strlen(file_name)] = '\0';
}

bool is_folder(char path[])
{
    if (filesystem::exists(filesystem::path(path)) && filesystem::path(path).extension() == "")
        return 1;
    return 0;
}

void help_build(char path_of_file[], FILE* p_bar, FILE* p_components);
void build_tar();
void help_decompose(char line[], char destioantion[], FILE* p_bar, FILE* p_components, bool condition);
void decompose_tar();

int main()
{
    decompose_tar();
    return 0;
}



//pentru numele fisierelor se va face identare, nu si pt continutul lor! vezi comentariul de final pentru a vedea cum se va face treaba
void help_build(char path_of_file[], FILE* p_bar, FILE* p_components)
{
    if (is_folder(path_of_file))//folder
    {
        //pun in stack
        get_FILEname(path_of_file);
        strcpy(S.folder_names[++S.nr_elem], file_name);
        //pun in fisier numele folderului
        fputs(identation, p_bar);
        fputs(file_name, p_bar);
        fputs("/\n", p_bar);
        strcat(identation, "\t\0");

        for (auto& p : filesystem::directory_iterator(path_of_file))//ia fisierele alfabetic
        {
            if (p.path().empty() == false)
            {
                //transformare din string in char(BUGS!)
                char IN_folder[MAX_VALUE];
                strcpy(IN_folder, p.path().string().c_str());
                for (int i = 0; i < strlen(IN_folder); i++)
                    if (IN_folder[i] == 92)
                        IN_folder[i] = '/';
                IN_folder[strlen(IN_folder)] = '\0';

                help_build(IN_folder, p_bar, p_components);
                memset(IN_folder, 0, sizeof IN_folder);
            }
        }

        //a ajuns la final
        strcpy(S.folder_names[S.nr_elem--], "\0");
        identation[strlen(identation) - 1] = '\0';
        fputs(identation, p_bar);
        fputs("end_oF_", p_bar);
        get_FILEname(path_of_file);
        fputs(file_name, p_bar);
        fputs("/\n", p_bar);
    }
    else//fisier normal
    {
        p_components = fopen(path_of_file, "r");
        if (p_components == NULL) ///i love my girlfriend!!!
        {
            cout << "error\n";
            return;
        }

        get_FILEname(path_of_file);
        fputs(identation, p_bar);
        fputs(file_name, p_bar);
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
void build_tar()
{
    char path_of_file[MAX_VALUE];
    FILE* p_bar, * p_components;
    p_bar = fopen(path_of_tar, "w");
    if (p_bar == NULL)
    {
        cout << "error";
        return;
    }

    int index = 0, k = nr_files_for_tar;
    while (index < k)
    {
        strcpy(path_of_file, input_for_paths[index]);
        help_build(path_of_file, p_bar, p_components);
        index++;
    }

    fclose(p_bar);
}

void help_decompose(char line[], char destination[], FILE* p_bar, FILE* p_components, bool condition)
{
    if (condition == 0)
    {
        line[strlen(line) - 1] = '\0';
        while (line[0] == '\t')
            strcpy(line, line + 1);
        if (line[strlen(line) - 1] == '/')//NUME FOLDER
        {
            char previous_line[MAX_VALUE];
            strcpy(previous_line, line);

            char new_destination[MAX_VALUE];
            strcpy(new_destination, destination);
            //creare folder
            strcat(new_destination, line);
            mkdir(new_destination);
            strcpy(S.folder_names[++S.nr_elem], new_destination);

            fgets(line, MAX_VALUE, p_bar);
            while (strstr(line, "end_oF_") == NULL && strstr(line, previous_line) == NULL)
            {
                help_decompose(line, new_destination, p_bar, p_components, 0);
                fgets(line, MAX_VALUE, p_bar);
            }

            strcpy(S.folder_names[S.nr_elem--], "\0");
            return;
        }
        else//NUME FISIER
        {
            char new_destination[MAX_VALUE];
            strcpy(new_destination, destination);
            strcat(new_destination, line);
            condition = 1;
            fgets(line, MAX_VALUE, p_bar);
            help_decompose(line, new_destination, p_bar, p_bar, 1);
        }
    }
    else//vorbim de continut aici
    {
        p_components = fopen(destination, "w");
        if (p_components)
        {
            int ok = 0;
            bool first = 1;
            while (1)
            {
                fgets(line, MAX_VALUE, p_bar);
                if (strstr(line, file_separator))
                {
                    fgets(line, MAX_VALUE, p_bar);
                    break;
                }
                else
                {
                    if ((strcmp(line, "\n") == 0))
                        ok++;
                    else
                    {
                        if (first == 0)
                            fputs("\n", p_components);
                        first = 0;
                        while (ok)
                        {
                            fputs("\n", p_components);
                            ok--;
                        }
                        line[strlen(line) - 1] = '\0';
                        fputs(line, p_components);
                    }
                }
            }
        }
        else
        {
            cout << "error";
            return;
        }
        condition = 0;
        fclose(p_components);
    }
}
void decompose_tar()
{
    FILE* p_bar, * p_components;
    p_bar = fopen(path_of_tar, "r");
    if (p_bar == NULL)
    {
        cout << "error";
        return;
    }

    char path[MAX_VALUE];
    strcpy(path, path_decompose);
    strcat(path, decompose_name);
    mkdir(path);
    //prima oara citesteste calea, afisarea pana la intalnirea file_separator
    char line[MAX_VALUE];
    while (fgets(line, MAX_VALUE, p_bar))
        help_decompose(line, path, p_bar, p_components, 0);
    /*
    0-NU STIU, prima linie
    1-DACA FIX INAINTE A FOST ANUNTAT NUME DE CEVA
    */
    fclose(p_bar);
}