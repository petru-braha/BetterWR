#define nr_buttons 13
void gui_commands_STOP();
void gui_commands_go_back(int& which_button, bool& first_command);
void gui_commands_alg(int& which_button);
void gui_commands_deselect();
void gui_commands_ready(int& which_button);
void gui_commands_sidebar();
void gui_commands_folder_manipulation();

void gui_commands_firstStep_menu(int &which_button);
void gui_commands_secondStep_decideOperation(char file_accessedPATH[], int which_button, bool &first_command, char& alg);
void gui_command_thirdStep(int& which_button, bool& first_command);

void gui_commands();

void graphical_user_interface();
