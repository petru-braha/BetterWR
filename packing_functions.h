struct stack{
    int nr_elem;
    char folder_names[MAX][MAX];
} S;
char file_separator[MAX]="*5EPArAToR*";
char identation[MAX];

int nr_files_for_tar;

char input_for_paths[MAX][MAX];
char path_of_tar[MAX]="C:/Users/PETRU/Desktop/myfiles.txt";
char path_decompose[MAX]="C:/Users/PETRU/Desktop/";
char decompose_name[]="unpack/";

bool is_folder(char path[]);
char* reverseArray(char arr[], int length);
char* get_FILEname(char source_path[]);

void help_build(char path_of_file[], FILE * p_bar, FILE * p_components);
void build_tar();
void help_decompose(char line[], char destioantion[], FILE * p_bar, FILE * p_components, bool condition);
void decompose_tar();
