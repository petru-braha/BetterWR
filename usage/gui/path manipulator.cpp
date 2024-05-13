#include <cstring>
#include <string>
#include "../../admin/pack.h"

void delete_dir_accessed(std::string & str)
{
    if(str == "")
        return;

    size_t index_context = -1;
    for(size_t i = 0; i < str.size() - 1; i++)
        if(str[i] == '/' || str[i] == 92)
            index_context = i;

    str.erase(index_context + 1, str.size());
}
