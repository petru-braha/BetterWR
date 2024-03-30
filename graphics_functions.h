void highlight(int x1, int y1, int x2, int y2);
void graphic_button(int x1, int y1, int x2, int y2);
void graphic_x(int x1, int y1, int x2, int y2);
void start_graphics(bool first_exe);

void graphics_MENUbuttons();
void graphics_GLOBALbuttons(int value);
void graphics_EXPLbuttons();
void graphics_ALGbuttons();

//short int unit=0;
void graphics_selected(char file_name[], int nr_files_for_tar);

bool click_on_button(int x, int y, int which_button);
bool click_on_file(int x, int y, int which_button);
