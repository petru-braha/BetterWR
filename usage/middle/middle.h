#pragma once
#define MAX 500
#define nr_input_paths 10
const char temp_location[] = "files/temp.txt";

//everything is accessible from both gui and cmd
void display_instructions_bash();
bool verification(int argc, char** argv);

bool compress_huf(char* path_output, char* output_name);
bool compress_lzw(char* path_output, char* output_name);

bool decompress_huf(char* path_input, char* path_output, char* output_name);
bool decompress_lzw(char* path_input, char* path_output, char* output_name);

void very_last_step(char* operation, char* algorithm, short nr_paths, char** paths_input, char* path_output, char* output_name);
