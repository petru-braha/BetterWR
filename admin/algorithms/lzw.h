#pragma once
#include <stdio.h>
#define max_integer_ever 18446744073709551615
typedef unsigned long long ull;
const char path_file_codes[] = "temp_codes.bin";

struct dictionary
{
    ull index;
    FILE* temporary_codes;

    dictionary();
    void add(char sequence[]);
    bool exist_string(char sequence[]);
    bool exist_nr(ull value);
    ~dictionary();
};

int array_len(int a[], int size);
void build_encoded(char s[], int*& encoded_text);
void build_decoded(char s[],char text[]);

unsigned int* lzw_encode_string(char* input);
char*         lzw_decode_string(int*  input);

///future patch: how long should the strings be?
// present patch: make the alg work with big data
