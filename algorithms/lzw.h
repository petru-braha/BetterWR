#pragma once

void bufferToIntArray(const char* buffer, int bufferSize, int* intArray, int& arraySize);
int Len(int a[], int size);
void initialize_dictionary();
bool is_in_dictionary(char s[]);
void add_TOdictionary(char s[], int& ASCII_value);
void build_encoded(char s[], int*& encoded_text);
bool is_in_dictionaryENCODED(int next);
void build_decoded(char s[],char text[]);
void lzw_encode(char input[], int size, int*& encoded_text);
void lzw_decode(int input[], char*& decoded_text);
