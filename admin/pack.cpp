#include <iostream>
#include <cstring>
#include <stdio.h>
#include <filesystem>
#include <direct.h>
#define MAX 300

//tar is in ascii
const char temp_location[] = "constant files/test files/temp.tar";
const char typed_end_of_file[] = "\n\n*EOF_no_more_content_to_be_displayed*\n\n";
const char typed_end_of_directory[] = "EOD_no_more_files_to_be_analysed_";

void change_extension(char* file_path, const char* extension) //are ca input un fisier tar corect
{
    std::filesystem::path f_p(file_path);
    if(std::filesystem::is_directory(f_p) && extension[0] == '.')
        strcpy(strstr(file_path, "."), extension);
}

char* get_file_name(char source_path[])
{
    size_t length = strlen(source_path), index_context = 0;
    for(size_t i = 0; i < length - 1; i++)
        if(source_path[i]=='/' || source_path[i] == 92) // '\' == 92
            index_context = i;
    return source_path + index_context + 1;
}

//output is in temp
void help_build(FILE* p_bar, FILE* p_components, char path_of_file[], char identation[])
{
    const std::filesystem::path file_path(path_of_file); std::error_code ec;
    if (std::filesystem::is_directory(file_path, ec)) //directory
    {
        if(identation[0])
            strcat(path_of_file, "/\0");

        fprintf(p_bar, "%s%s\n", identation, get_file_name(path_of_file));
        strcat(identation, "\t\0");

        for (auto& p : std::filesystem::directory_iterator(file_path)) //alphabetical order
            if (p.path().empty() == false)
                help_build(p_bar, p_components, (char*)p.path().string().c_str(), identation);

        identation[strlen(identation) - 1] = '\0';
        fprintf(p_bar, "%s%s%s\n", identation, typed_end_of_directory, get_file_name(path_of_file));
    }
    else //normal file
    {
        p_components = fopen(path_of_file, "rb");
        if (p_components == nullptr)
        {
            std::cout << "error - composition: can not open:" << path_of_file <<" .\n";
            return;
        }

        fprintf(p_bar, "%s%s", identation, get_file_name(path_of_file));

        char temp = fgetc(p_components); if(temp!=EOF) fprintf(p_bar, "\n\n%c", temp);
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
    p_bar = fopen("constant files/test files/temp.tar", "wb");
    if (p_bar == nullptr)
    {
        std::cout << "error - composition: can not create temp file.\n";
        return;
    }

    for(int i=0; i < nr_paths; i++)
        help_build(p_bar, p_components, paths_input[i], identation);

    fclose(p_bar);
}

void read_antet(FILE* pointer_to_file, char my_string[]) // was not used in the end
{
    char* character = new char{ 0 };
    for(size_t i = 0; i < strlen(my_string); i++)
        my_string[i] = '\0';

    size_t index = 0;

    fread(character, 1, 1, pointer_to_file);
    while(*character != '\n')
    {
        my_string[index++] = *character;
        fread(character, 1, 1, pointer_to_file);
    }
}

void help_decompose_content(FILE* p_bar, FILE* p_components, char* path_output)
{
    p_components = fopen(path_output, "wb");
    if(p_components == nullptr)
        std::cout << "error - decomposition: can not write the files.\n";

    fseek(p_bar, -1, SEEK_CUR);
    char check_empty[MAX] = { 0 };
    fread(check_empty, sizeof(char), strlen(typed_end_of_file), p_bar);
    if(strcmp(check_empty, typed_end_of_file) == 0)
        return;
    fseek(p_bar, -strlen(typed_end_of_file), SEEK_CUR); // rewind pointer
    fseek(p_bar, 2, SEEK_CUR); // remove file_name_antent's "\n"

    char* character = new char{ 0 };
    while(true)
    {
        fread(character, 1, 1, p_bar);
        if(*character == typed_end_of_file[0])
        {
            bool condition_to_continue = false;
            char temp[MAX] = { *character }, temp_index = 1;
            for(size_t i = 1; i < strlen(typed_end_of_file) && condition_to_continue == false; i++)
            {
                fread(character, 1, 1, p_bar);
                temp[temp_index++] = *character;
                if(*character != typed_end_of_file[i])
                    condition_to_continue = true;
            }

            if(condition_to_continue == false)
                break;
            fwrite(temp, sizeof(char), (size_t)temp_index, p_components);
        }

        else fwrite(character, 1, 1, p_components);
    }

    delete character;
    fclose(p_components);
}

void help_decompose_antet(FILE* p_bar, FILE* p_components, char* path_output, char line[])
{
    line[strlen(line) - 1] = '\0'; //delete '\n'
    while (line[0] == '\t')
            strcpy(line, line + 1);

    char new_destination[MAX];
    strcpy(new_destination, path_output);
    strcat(new_destination, line);

    if (line[strlen(line) - 1] == '/') // directory name
    {
        mkdir(new_destination);

        char previous_line[MAX];
        strcpy(previous_line, line);
        fgets(line, MAX, p_bar);

        while(strstr(line, typed_end_of_directory) == nullptr && strstr(line, previous_line) == nullptr)
        {
            help_decompose_antet(p_bar, p_components, new_destination, line);
            fgets(line, MAX, p_bar);
        }
    }
    else help_decompose_content(p_bar, p_components, new_destination);
}

void decompose_tar(char* path_output, char* output_name)
{
    char final_path_output[MAX] = {0};
    strcpy(final_path_output, path_output);
    strcat(final_path_output, output_name);
    mkdir(final_path_output);

    FILE* p_bar = nullptr, * p_components = nullptr;
    p_bar = fopen(temp_location, "rb");
    if (p_bar == nullptr)
    {
        std::cout << "error - decomposition: missing temp file.\n";
        return;
    }

    char line[MAX] = {0};
    while(fgets(line, MAX, p_bar))
        help_decompose_antet(p_bar, p_components, final_path_output, line);

    fclose(p_bar);
}
