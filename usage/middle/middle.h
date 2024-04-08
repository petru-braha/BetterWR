#pragma once
char* temp_location = "files/temp.txt";

//everything is accessible from both gui and cmd
char* operation, * algorithm;
short nr_paths = 1;
char** paths_input = { "../../files/to_econde/" }, * path_output = "../../files/encoded/";
char* output_name = "unpack______________";

void display_instructions_bash();
bool verification(int argc, char** argv);

//encode and move functions
bool compressHuf_paste(char* path_output, char* output_name);
bool compressLzw_paste(char* path_output, char* output_name);

bool decompressHuf(char* path_output, char* output_name);
bool decompressLzw(char* path_output, char* output_name);

void very_last_step(char* operation, char* algorithm, short nr_paths, char** paths_input, char* path_output, char* output_name);
