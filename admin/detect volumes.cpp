#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

std::vector<std::string> list_volumes()
{
    std::vector<std::string> the_list;
    char* size_volume = new char[MAX_PATH]();
    GetLogicalDriveStringsA(MAX_PATH, size_volume);
    for(int i = 0; i < 100; i += 4)
        if (size_volume[i] != (char)0)
            the_list.push_back(std::string{size_volume[i], size_volume[i+1], size_volume[i+2]});
    delete[] size_volume;
    return the_list;
}

// future patch: detect all volumes despite the operating system / letters
// i've created a file just for this topic because i found that there are a lot of methods of finding the volumes; i have to experiment more in the future
