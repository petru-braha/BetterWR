short int file_nr_visible;
char file_accessedPATH[MAX];
char file_lastOPENED[MAX];
char file_visible[MAX][MAX];

void explorer(const char mode[]);
void file_explorer();

#include "button/button.h"
//declaration of buttons
button_00 *compress_button = button_00::GetInstance();
button_01 *decompress_button = button_01::GetInstance();
button_02 *more_info_button = button_02::GetInstance();
button_03 *test_button = button_03::GetInstance();
button_04 *stop_button = button_04::GetInstance();
button_05 *back_button = button_05::GetInstance();
button_06 *done_button = button_06::GetInstance();
button_07 *select_button = button_07::GetInstance();
button_08 *mkdir_button = button_08::GetInstance();
button_09 *fopen_button = button_09::GetInstance();
button_10 *delete_button = button_10::GetInstance();
button_11 *huf_button = button_11::GetInstance();
button_12 *lzw_button = button_12::GetInstance();

//MENU, GLOBAL, EXPLORER, ALGORITHM
button menu_button[10] = {*compress_button, *decompress_button, *more_info_button, *test_button}; //will add more buttons
button global_button[3] = {*stop_button, *back_button, *done_button};
button explorer_button[4] = {*select_button ,*mkdir_button ,*fopen_button, *delete_button};
button algorithm_button[10] = {*huf_button, *lzw_button}; //will add more algorithms
