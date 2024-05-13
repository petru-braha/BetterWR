#pragma once

#define max_integer_possible    18446744073709551615
#define max_integer_accepted    2147483647

typedef unsigned long long  ull;
const char path_file_codes[] = "temp_codes.bin";
int array_len(int a[], int sz);
bool ull_nat(ull number);

#include <stdio.h>
#include <string>
class dictionary
{
    FILE* temporary_codes;
public:
    ull index;
    dictionary();
    void add(std::string sequence);
    ull  exist_string(std::string sequence); // return its code
    bool exist_nr(ull value);

    ~dictionary();
};

void compress_lzw(char* path_output, char* output_name);
void decompress_lzw(char* path_input, char* path_output, char* output_name);

/// assumption = even though bigger size ready to be read, strlen(uncoded_string) < MAX
/// how get rid of assumption: dynamic allocation big data
/// assumption = index limited to ull_max ( maximum number of codes )
