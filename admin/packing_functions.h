#pragma once
void change_extension(char type[], char path_output[]);
char* get_FILEname(char source_path[]);

void help_build(char path_of_file[], FILE* p_bar, FILE* p_components, char identation[]);
void build_tar(short nr_paths, char** paths_input);

void help_decompose(char line[], char destination[], FILE* p_bar, FILE* p_components, bool condition);
void decompose_tar(char* path_output, char* output_name);
