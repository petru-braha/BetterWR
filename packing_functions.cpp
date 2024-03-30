#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <direct.h>
#define MAX 300

bool is_folder(char path[])
{
    if (std::filesystem::exists(std::filesystem::path(path)) && std::filesystem::path(path).extension() == "")
        return true;
    return false;
}

char* reverseArray(char arr[], int length)
{
    int index_start = 0;
    int index_end = length - 1;

    while (index_start < index_end)
    {
        // Swap characters at start and end indices
        char temp = arr[index_start];
        arr[index_start] = arr[index_end];
        arr[index_end] = temp;

        // Move indices towards the center
        index_start++;
        index_end--;
    }
    return arr;
}

char* get_FILEname(char source_path[])
{
    int length=strlen(source_path);
    int index_context=0;
    for(int i=0;i<length-1;i++)
        if(source_path[i]=='/')
            index_context=i;
    return source_path+index_context+1;
}
