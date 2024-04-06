#pragma once
#define K 1000 //one etern buffer
char* temp_location = "files/temp.txt";
//i want these values to be accessible from both gui and cmd

char* operation, * algorithm;
short nr_paths;
char** paths_input, * path_output;
char* output_name; ////create the file on the output!

//encode and move functions
bool compressHuf_paste(char* path_output, char* output_name);
bool compressLzw_paste(char* path_output, char* output_name);

bool decompressHuf(char* path_output, char* output_name);
bool decompressLzw(char* path_output, char* output_name);
