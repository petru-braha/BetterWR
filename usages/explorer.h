bool last_step;
char alg;
short int file_nr_visible;
char file_accessedPATH[MAX]="\0";
char file_lastOPENED[MAX];
char file_visible[MAX][MAX];

void explorer(char mode[]);
void file_explorer();
