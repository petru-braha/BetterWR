#pragma once
void  change_extension(char* file_path, const char* extension);
char* get_file_name(char source_path[]);

void build_tar(short nr_paths, char** paths_input);
void decompose_tar(char* path_output, char* output_name);
