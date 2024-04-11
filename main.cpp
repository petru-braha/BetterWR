#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <direct.h>
#include "algorithms/huffman.h"
#include "algorithms/lzw.h"
using namespace std;
#define MAX 300
#define nr_buttons 13
short int width=1536, height=960;

///TAR SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
char file_name[MAX];
void get_FILEname(char source_path[]);

void help_build(char path_of_file[], FILE * p_bar, FILE * p_components);
void build_tar();
void help_decompose(char line[], char destioantion[], FILE * p_bar, FILE * p_components, bool condition);
void decompose_tar();

///GRAPHIC SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void highlight(int x1, int y1, int x2, int y2);
void graphic_button(int x1, int y1, int x2, int y2);
void graphic_x(int x1, int y1, int x2, int y2);
bool first_exe;
void start_graphics();

short int coordo[nr_buttons][4];
void graphics_MENUbuttons();
void graphics_GLOBALbuttons(int value);
void graphics_EXPLbuttons();
void graphics_ALGbuttons();

short int unit=0;
void graphics_selected();

bool click_on_button(int x, int y, int which_button);
bool click_on_file(int x, int y, int which_button);

///EXPLORER SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool last_step;
char alg;
short int file_nr_visible;
short int file_coordo[MAX][4];
char file_accessedPATH[MAX]="\0";
char file_lastOPENED[MAX];
char file_visible[MAX][MAX];

void explorer(char mode[]);
void file_explorer();

///COMMANDS SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//void define_announcement(bool mode);
void change_extension(char type[]) //are ca input un fisier tar corect
{
    if(filesystem::path(path_of_tar).extension()==".txt")
        strcpy(strstr(path_of_tar, ".txt"), type);
    else
        strcpy(strchr(path_of_tar, '.'), ".txt");
}

void commands()
{
    bool first=1;
    int which_button=0;

    struct point
    {
        int x, y;
    } mouse;

    while(1)
    {
        ///MENU BUTON
        while(which_button==0)
        {
            getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y);
            if(mouse.x!=-1 && mouse.y!=-1)
            {
                //1. ESC
                if(click_on_button(mouse.x, mouse.y, 3))
                {
                    highlight(coordo[3][0], coordo[3][1], coordo[3][2], coordo[3][3]);
                    delay(100);
                    closegraph();
                    exit(0);
                }
                //2. MENUbuton
                for(int i=0; i<3; i++)
                    if(click_on_button(mouse.x, mouse.y, i))
                    {
                        highlight(coordo[i][0], coordo[i][1], coordo[i][2], coordo[i][3]);
                        delay(100);
                        which_button=i+1;
                        break;
                    }
            }
        }
        ///CE OPERATIE
        if(file_accessedPATH[0]==0)
        {
            if(which_button)
            {
                if(which_button==3)
                {
                    start_graphics();
                    setcolor(15);
                    settextstyle(DEFAULT_FONT, 0, 2);
                    outtextxy(coordo[0][0], coordo[0][1], "Cititi fisierul: readME.txt");
                    delay(1500);
                    system("readME.txt");
                }
                else
                {
                    if(first)
                    {
                        file_explorer();
                        first=0;
                    }
                    if(which_button==1)///arhivare
                    {
                        graphics_ALGbuttons();
                        if(alg=='H')
                            highlight(coordo[10][0], coordo[10][1], coordo[10][2], coordo[10][3]);
                        if(alg=='L')
                            highlight(coordo[11][0], coordo[11][1], coordo[11][2], coordo[11][3]);
                        setcolor(15);
                        settextstyle(SMALL_FONT, 0, 8);
                        outtextxy(340, 50, "ALEGE FISIERE PENTRU COMPRIMARE");
                    }
                    else///dezarhivare
                    {
                        setcolor(15);
                        settextstyle(SMALL_FONT, 0, 8);
                        outtextxy(300, 50, "ALEGE ARHIVA (UNA SINGURA)");

                    }
                    graphics_GLOBALbuttons(5);
                }
                graphics_GLOBALbuttons(4);
            }
        }
        ///JOACA IN FILESYSTEM
        while(last_step==0)
        {
            getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y);
            if(mouse.x!=-1 && mouse.y!=-1)
            {
                //1. ESC
                if(click_on_button(mouse.x, mouse.y, 3))
                {
                    highlight(coordo[3][0], coordo[3][1], coordo[3][2], coordo[3][3]);
                    delay(100);
                    closegraph();
                    exit(0);
                }
                //2. go_back
                if(file_accessedPATH[0])
                {
                    if(strlen(file_accessedPATH)<4)
                    {
                        if(click_on_button(mouse.x, mouse.y, 4))
                        {
                            highlight(coordo[4][0], coordo[4][1], coordo[4][2], coordo[4][3]);
                            delay(100);
                            graphics_GLOBALbuttons(4);
                            strcpy(file_accessedPATH, "\0");
                            strcpy(file_lastOPENED, "\0");
                            file_explorer();

                            unit=0;
                            for(int i=0; i<nr_files_for_tar; i++)
                            {
                                get_FILEname(input_for_paths[i]);
                                setcolor(15);
                                line(1040, 195+unit, 1440, 195+unit);

                                settextstyle(SMALL_FONT, 0, 10);
                                outtextxy(1040, 200+unit, file_name);

                                if(strchr(file_name, '.')==NULL)
                                    readimagefile("photos/folder2.jpg", 1010, 200+unit, 1035, 235+unit);
                                else
                                    readimagefile("photos/txt2.jpg", 1010, 200+unit, 1035, 235+unit);
                                unit+=45;
                                line(1040, 195+unit, 1440, 195+unit);
                            }
                            break;
                        }
                    }
                    else
                    {
                        if(click_on_button(mouse.x, mouse.y, 4))
                        {
                            highlight(coordo[4][0], coordo[4][1], coordo[4][2], coordo[4][3]);
                            delay(100);

                            graphics_GLOBALbuttons(4);
                            get_FILEname(file_accessedPATH);
                            strcpy(file_lastOPENED, file_name);
                            strcpy(strstr(file_accessedPATH, file_lastOPENED), "\0");
                            get_FILEname(file_accessedPATH);
                            strcpy(file_lastOPENED, file_name);
                            cout<<file_accessedPATH<<'\n';
                            explorer("directory_iterator");
                            break;
                        }
                    }
                }
                else
                {
                    if(click_on_button(mouse.x, mouse.y, 4))
                    {
                        highlight(coordo[4][0], coordo[4][1], coordo[4][2], coordo[4][3]);
                        delay(100);
                        which_button=0;
                        first=1;
                        alg=0;
                        //sterg datele
                        for(int i=0;i<nr_files_for_tar;i++)
                            memset(input_for_paths[i], 0, sizeof input_for_paths[i]);
                        nr_files_for_tar=0;
                        start_graphics();
                        graphics_MENUbuttons();
                        break;
                    }
                }
                //3. ALGORITM
                if(which_button==1)
                {
                    if(click_on_button(mouse.x, mouse.y, 10))
                    {
                        alg='H';
                        graphics_ALGbuttons();
                        highlight(coordo[10][0], coordo[10][1], coordo[10][2], coordo[10][3]);
                    }
                    else
                    {
                        if(click_on_button(mouse.x, mouse.y, 11))
                        {
                            alg='L';
                            graphics_ALGbuttons();
                            highlight(coordo[11][0], coordo[11][1], coordo[11][2], coordo[11][3]);
                        }
                    }
                }
                //3.9 deselectare
                for(int i=0; i<11; i++)
                    if(click_on_file(mouse.x, mouse.y, i))
                    {
                        graphic_x(file_coordo[i][0], file_coordo[i][1], file_coordo[i][2], file_coordo[i][3]);
                        delay(200);
                        strcpy(input_for_paths[i], "\0");
                        nr_files_for_tar--;
                        for(int j=i;j<nr_files_for_tar;j++)
                            strcpy(input_for_paths[j], input_for_paths[j+1]);
                        setcolor(0);
                        setfillstyle(SOLID_FILL, 0);
                        bar(1000, 195, 1450,890);
                        unit=0;
                        for(int i=0; i<nr_files_for_tar; i++)
                        {
                            get_FILEname(input_for_paths[i]);
                            setcolor(15);
                            line(1040, 195+unit, 1440, 195+unit);
                            file_coordo[i][0]=1000;
                            file_coordo[i][1]=195+unit;
                            file_coordo[i][2]=1440;

                            settextstyle(SMALL_FONT, 0, 10);
                            outtextxy(1040, 200+unit, file_name);

                            if(strchr(file_name, '.')==NULL)
                                readimagefile("photos/folder2.jpg", 1010, 200+unit, 1035, 235+unit);
                            else
                                readimagefile("photos/txt2.jpg", 1010, 200+unit, 1035, 235+unit);
                            unit+=45;
                            line(1040, 195+unit, 1440, 195+unit);
                            file_coordo[i][3]=195+unit;
                        }
                        graphics_GLOBALbuttons(5);
                        break;
                    }
                //4. gata
                if(click_on_button(mouse.x, mouse.y, 5))
                {
                    highlight(coordo[5][0], coordo[5][1], coordo[5][2], coordo[5][3]);
                    delay(100);
                    graphics_GLOBALbuttons(5);
                    if(nr_files_for_tar==0 && (alg!='H' && alg!='L'))
                    {
                        cout<<nr_files_for_tar;
                        cout<<"error: nu ai ales fisier sau algoritm de utilizare";
                    }
                    else
                    {
                        FILE *input=nullptr, *output=nullptr;
                        if(which_button==1)
                        {
                            build_tar();
                            if(alg=='H')
                            {
                                input = fopen(path_of_tar, "rb+");
                                if (input == NULL)
                                {
                                    printf("Error opening input file\n");
                                    exit(1);
                                }

                                // Citim datele din input si le punem intr-un buffer
                                const int BUFFER_SIZE = 30000;  // adjustare manuala
                                char buffer[BUFFER_SIZE];
                                size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
                                if (bytesRead <= 0)
                                {
                                    printf("Error reading input file\n");
                                    fclose(input);
                                    exit(1);
                                }

                                // Crearea unui string din bufferul citit din fisier
                                string binaryData(buffer, bytesRead);
                                cout << binaryData << endl << endl;

                                // Realizarea codarii Huffman
                                node* root = buildHuffmanTree(binaryData);
                                string encodedString = "";
                                HuffmanEncode(root, binaryData, encodedString);

                                // Convertim string-ul binar in simboluri ASCII
                                string textToOutput = writeEncodedDataToFile(encodedString);

                                //Salvam informatiile despre arborele Huffman, care vor fi stocate la inceputul fisierului encodat
                                char treeInfo[MAX];
                                int treeFreq[MAX];
                                int treeSize = 0;
                                createTreeString(root, 1, treeInfo, treeFreq, treeSize);


                                //Dupa ce am obtinut informatiile din fisierul nostru text si am encodat-o folosind Huffman, redeschidem acelasi fisier pentru a scrie informatia encodata
                                change_extension(".huf");
                                output = fopen(path_of_tar, "wb+");
                                if (output == NULL)
                                {
                                    printf("Error opening output file\n");
                                    exit(1);
                                }

                                // Scriem in fisier toate informatiile care trebuie salvate, pentru a putea fi utilizate ulterior la reconstruirea folderelor
                                fwrite(&treeSize, sizeof(int), 1, output);

                                for (int i = 1; i <= treeSize; ++i)
                                    fwrite(&treeFreq[i], sizeof(int), 1, output);

                                for (int i = 1; i <= treeSize; ++i)
                                    fwrite(&treeInfo[i], sizeof(char), 1, output);

                                int bitlength = encodedString.size();
                                fwrite(&bitlength, sizeof(int), 1, output);

                                fwrite(textToOutput.c_str(), sizeof(char), textToOutput.size(), output);    // scriem in fisier textul encodat

                                change_extension(".txt");

                                fclose(input);
                                fclose(output);
                                remove(path_of_tar);
                                //UNDE VREI SA O PUI
                                //CUM SA SE NUMEASCA ARHIVA

                            }
                            if(alg=='L')
                            {
                                int* encoded_text;
                                encoded_text = new int[MAX];
                                memset(encoded_text, 0, MAX * sizeof(int));

                                input = fopen(path_of_tar, "rb");
                                if (input == NULL)
                                {
                                    printf("Error opening input file\n");
                                    exit(1);
                                }

                                change_extension(".lzw");
                                output = fopen(path_of_tar, "wb");
                                if (output == NULL)
                                {
                                    printf("Error opening output file\n");
                                    fclose(input);
                                    exit(1);
                                }

                                // Citim datele din input si le punem intr-un buffer
                                const int BUFFER_SIZE = 30000;  // adjustare manuala
                                char buffer[BUFFER_SIZE];
                                for (int i = 0; i < BUFFER_SIZE; ++i)
                                buffer[i] = 0;
                                size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
                                if (bytesRead <= 0)
                                {
                                    printf("Error reading input file\n");
                                    fclose(input);
                                    exit(1);
                                }

                                // Realizarea encodarii LZW
                                lzw_encode(buffer,sizeof(buffer), encoded_text);
                                int n = Len(encoded_text, MAX);

                                // Convertire int to string pentru a scrie mai usor textul encodat in fisier
                                string encoded_text_char = {};
                                for (int x = 0; x < n; x++)
                                    encoded_text_char += to_string(encoded_text[x]) + ' ';

                                // Calculam dimensiunea datelor
                                size_t originalSize = bytesRead * 8;
                                size_t encodedSize = encoded_text_char.size() * 8;

                                for (size_t i = 0; i < n; ++i)
                                    fprintf(output, "%d ", static_cast<int>(encoded_text[i]));      // scriem in fisier textul encodat

                                delete[]encoded_text;
                                change_extension(".txt");
                                fclose(input);
                                fclose(output);
                                remove(path_of_tar);
                                //UNDE VREI SA O PUI
                                //CUM SA SE NUMEASCA ARHIVA
                            }
                        }
                        else
                        {
                            if(strcmp(filesystem::path(input_for_paths[0]).extension().string().c_str(), ".huf")==0)
                            {
                                // Deschidem fisierul de input pentru citire
                                input = fopen(input_for_paths[0], "rb+");
                                if (input == NULL)
                                {
                                    printf("Error opening input file\n");
                                    exit(1);
                                }

                                // Citim datele din input si le punem intr-un buffer
                                const int BUFFER_SIZE = 30000;  // adjustare manuala
                                char buffer[BUFFER_SIZE];

                                // recuperam informatiile despre arborele Huffman
                                char treeInfo[MAX];
                                int treeFreq[MAX];
                                int treeSize = 1;

                                fread(&treeSize, sizeof(int), 1, input);

                                for (int i = 1; i <= treeSize; ++i)
                                    fread(&treeFreq[i], sizeof(int), 1, input);

                                for (int i = 1; i <= treeSize; ++i)
                                    fread(&treeInfo[i], sizeof(char), 1, input);

                                int bitlength;
                                fread(&bitlength, sizeof(int), 1, input);

                                size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
                                if (bytesRead <= 0)
                                {
                                    printf("Error reading input file\n");
                                    fclose(input);
                                    exit(1);
                                }

                                // Crearea unui string din bufferul citit din fisier
                                string binaryData(buffer, bytesRead);

                                // Reconstruim arborele Huffman
                                node* rootNode = reconstructTree(treeSize, 1, treeInfo, treeFreq);

                                // Convertim simbolurile ASCII citite din fisier intr un sir de biti, care urmeaza a fi folosit in functia de decodare
                                string codes = ASCIIToBinary(binaryData, bitlength);

                                // Realizarea decodarii Huffman si scrierea textului decodat in fisier
                                string decodedOutput = "";
                                HuffmanDecode(rootNode, codes, decodedOutput);

                                // Pentru ca restabilirea folderelor sa functioneze corect, intai am decodat textul din fisierul text ce contine informatia necesara
                                // Rescriem in acelasi fisier informatia decodata, pentru ca restabilirea se face pe baza textului initial, nu cel encodat
                                output = fopen(path_of_tar, "wb+");
                                if (output == NULL)
                                {
                                    printf("Error opening input file\n");
                                    exit(1);
                                }

                                fwrite(decodedOutput.c_str(), sizeof(char), decodedOutput.size(), output);

                                fclose(input);
                                fclose(output);
                            }
                            else
                            {
                                if(strcmp(filesystem::path(input_for_paths[0]).extension().string().c_str(), ".lzw")==0)
                                {
                                    int* decoded_text;
                                    decoded_text = new int[MAX];
                                    memset(decoded_text, 0, MAX * sizeof(int));

                                    char* output_text;
                                    output_text = new char[MAX];
                                    memset(output_text, 0, MAX * sizeof(char));

                                    // Deschidem fisierul de input pentru citire
                                    input = fopen(input_for_paths[0], "rb");
                                    if (input == NULL)
                                    {
                                        printf("Error opening input file\n");
                                        exit(1);
                                    }

                                    // Deschidem fisierul de output pentru a scrie datele codate
                                    output = fopen(path_of_tar, "wb");
                                    if (output == NULL)
                                    {
                                        printf("Error opening output file\n");
                                        fclose(input);
                                        exit(1);
                                    }

                                    // Citim datele din input si le punem intr-un buffer
                                    const int BUFFER_SIZE = 30000;
                                    char buffer[BUFFER_SIZE];
                                    for (int i = 0; i < BUFFER_SIZE; ++i)
                                        buffer[i] = 0;
                                    size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
                                    if (bytesRead <= 0)
                                    {
                                        printf("Error reading input file\n");
                                        fclose(input);
                                        exit(1);
                                    }

                                    int n = Len(decoded_text, MAX);

                                    // Convertim sirul de caractere citit din fisier intr un vector de intregi, pentru a putea fi folosit la decodare
                                    bufferToIntArray(buffer, strlen(buffer), decoded_text, n);

                                    // Realizarea decodarii LZW si scrierea textului decodat in fisier
                                    lzw_decode(decoded_text, output_text);
                                    fwrite(output_text, sizeof(char), strlen(output_text), output);

                                    delete[]decoded_text;
                                    delete[]output_text;

                                    fclose(input);
                                    fclose(output);

                                }
                            }
                            decompose_tar();
                        }
                    }
                        last_step=1;
                }
                //5. butoane file_explorer
                for(int i=6; i<10; i++)
                {
                    if(click_on_button(mouse.x, mouse.y, i))
                    {
                        highlight(coordo[i][0], coordo[i][1], coordo[i][2], coordo[i][3]);
                        delay(100);
                        graphics_EXPLbuttons();

                        ///annocement_button(mode de scris/mode de inchis)
                        char new_name[MAX], temp[MAX];
                        cin>>new_name;
                        strcpy(temp, file_accessedPATH);
                        strcat(temp, new_name);

                        switch(i)
                        {
                        case 7:
                            mkdir(temp);
                            explorer("directory_iterator");
                            break;
                        case 8:
                            fopen(temp, "r");
                            explorer("directory_iterator");
                            break;
                        }
                        break;
                    }
                }
                //6. folder
                for(int i=11; i<11+file_nr_visible; i++)
                    if(click_on_file(mouse.x, mouse.y, i))
                    {
                        highlight(file_coordo[i][0], file_coordo[i][1], file_coordo[i][2], file_coordo[i][3]);
change_MYMIND:
                        while(1)
                        {
                            bool ok=0, change_of_mind=0;
                            getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y);
                            if(mouse.x!=-1 && mouse.y!=-1)
                            {
                                //se schimba input
                                for(int j=11; j<11+file_nr_visible; j++)
                                    if(click_on_file(mouse.x, mouse.y, j) && i!=j)
                                    {
                                        if(file_accessedPATH[0]==0)
                                            explorer("partitive");
                                        else
                                            explorer("directory_iterator");
                                        highlight(file_coordo[j][0], file_coordo[j][1], file_coordo[j][2], file_coordo[j][3]);
                                        change_of_mind=1;
                                        i=j;
                                        break;
                                    }
                                if(change_of_mind)
                                    goto change_MYMIND;
                                if(click_on_button(mouse.x, mouse.y, 3))//stop
                                {
                                    highlight(coordo[3][0], coordo[3][1], coordo[3][2], coordo[3][3]);
                                    delay(100);
                                    closegraph();
                                    exit(0);
                                }
                                if(click_on_button(mouse.x, mouse.y, 4))//inapoi
                                {
                                    highlight(coordo[4][0], coordo[4][1], coordo[4][2], coordo[4][3]);
                                    delay(100);
                                    graphics_GLOBALbuttons(4);
                                    ok=1;
                                    if(file_accessedPATH[0]==0)
                                        explorer("partitive");
                                    else
                                        explorer("directory_iterator");
                                }
                                if(click_on_button(mouse.x, mouse.y, 6) && file_accessedPATH[0] && nr_files_for_tar<11)//selecteaza
                                {///de tradus, aranjat, gata_button
                                    bool dir=0;
                                    highlight(coordo[6][0], coordo[6][1], coordo[6][2], coordo[6][3]);
                                    delay(100);
                                    graphics_EXPLbuttons();

                                    strcpy(file_lastOPENED, file_visible[i]);
                                    char temp[MAX];
                                    strcpy(temp, file_accessedPATH);
                                    strcat(temp, file_lastOPENED);
                                    if(is_folder(temp))
                                    {
                                        strcat(temp, "/");
                                        dir=1;
                                    }

                                    strcpy(input_for_paths[nr_files_for_tar++], temp);
                                    get_FILEname(temp);
                                    graphics_selected();
                                    explorer("directory_iterator");
                                    ok=1;
                                }
                                if(click_on_button(mouse.x, mouse.y, 9) && file_accessedPATH[0]) //delete
                                {
                                    highlight(coordo[9][0], coordo[9][1], coordo[9][2], coordo[9][3]);
                                    delay(100);
                                    graphics_EXPLbuttons();

                                    strcpy(file_lastOPENED, file_visible[i]);
                                    char temp[MAX];
                                    strcpy(temp, file_accessedPATH);
                                    strcat(temp, file_lastOPENED);

                                    if(is_folder(temp))
                                        rmdir(temp);
                                    else
                                        remove(temp);
                                    explorer("directory_iterator");
                                    ok=1;
                                }

                                if(click_on_file(mouse.x, mouse.y, i))//accesez calea
                                {
                                    ok=1;
                                    strcpy(file_lastOPENED, file_visible[i]);
                                    strcat(file_accessedPATH, file_lastOPENED);
                                    if(is_folder(file_accessedPATH))
                                    {
                                        if(strlen(file_accessedPATH)>=4)
                                            strcat(file_accessedPATH, "/");
                                        cout<<file_accessedPATH<<'\n';
                                        explorer("directory_iterator");
                                    }
                                    else
                                    {
                                        char exe[MAX];
                                        strcpy(exe, file_accessedPATH);
                                        strcpy(strstr(file_accessedPATH, file_lastOPENED), "\0");
                                        get_FILEname(file_accessedPATH);
                                        strcpy(file_lastOPENED, file_name);
                                        cout<<file_accessedPATH<<'\n';
                                        explorer("directory_iterator");
                                        system(exe);
                                    }
                                }
                            }
                            if(ok)
                                break;
                        }
                        break;//pt for
                    }


            }
        }
    if(last_step)
        break;//schimb
    }
}






int main()
{
    initwindow(width, height, "", -3, -3);
    start_graphics();
    graphics_MENUbuttons();
    commands();
    closegraph();
    return 0;
}





///GRAPHIC SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void highlight(int x1, int y1, int x2, int y2)
{
    setcolor(15);
    for(int i=0; i<10; i++)
    {
        x1++;
        y1++;
        x2--;
        y2--;
        line(x1, y1, x2, y1);
        line(x1, y1, x1, y2);
        line(x1, y2, x2, y2);
        line(x2, y1, x2, y2);
    }
}
void graphic_button(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, 9); //the edge of rectangles
    bar(x1, y1, x2, y2);
    setfillstyle(SLASH_FILL, 1);
    bar(x1+5, y1+5, x2-5, y2-5);
}
void graphic_x(int x1, int y1, int x2, int y2)
{
    setcolor(4);
    line(x1, y2, x2, y1);
    line(x1, y1, x2, y2);
}
void start_graphics()
{
    //background
    if(first_exe)
        readimagefile("photos/2.jpg", 0, 0, width, height);
    else
        readimagefile("photos/1.jpg", 0, 0, width, height);
    first_exe=1;
    setcolor(9);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(1000, 200, "Algoritmi:");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(1050, 250, "-Huffman");
    outtextxy(1050, 270, "-Lempel-Ziv-Welch");

    graphics_GLOBALbuttons(3);
}
void graphics_MENUbuttons()
{
    setcolor(9);
    int x1=60, y1=height/4, temp=60, y2=y1+temp, x2=x1+380;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    for(int i=0; i<3; i++)
    {
        switch (i)
        {
        case 0:
            graphic_button(x1, y1, x2, y2);
            outtextxy(x1+15, y1+15, "arhivare");
            break;

        case 1:
            graphic_button(x1, y1, x2, y2);
            outtextxy(x1+15, y1+15, "dezarhivare");
            break;

        case 2:
            graphic_button(x1, y1, x2, y2);
            outtextxy(x1+15, y1+15, "info++?");
            break;

        case 3:
            graphic_button(x1, y1, x2, y2);
            outtextxy(x1+15, y1+15, "test");
            break;

        default:
            break;
        }
        coordo[i][0]=x1;
        coordo[i][1]=y1;
        coordo[i][2]=x2;
        coordo[i][3]=y2;

        y1=y2+10;
        y2=y1+temp;
    }
}
void graphics_GLOBALbuttons(int value)
{
    switch(value)
    {
    case 3:
        setcolor(4);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        graphic_button(1350, 40, 1500, 100);
        outtextxy(1375, 60, "STOP");
        coordo[3][0]=1350;
        coordo[3][1]=40;
        coordo[3][2]=1500;
        coordo[3][3]=100;
        break;
    case 4:
        setcolor(9);
        settextstyle(DEFAULT_FONT, 0, 2);
        graphic_button(30, 880, 130, 930);
        outtextxy(36, 895, "inapoi");
        coordo[4][0]=30;
        coordo[4][1]=880;
        coordo[4][2]=130;
        coordo[4][3]=930;
        break;
    case 5:
        setcolor(4);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        graphic_button(1270, 840, 1470, 900);
        outtextxy(1312, 860, "GATA!");
        coordo[5][0]=1270;
        coordo[5][1]=840;
        coordo[5][2]=1470;
        coordo[5][3]=900;
        break;
    }
}
void graphics_EXPLbuttons()
{
    setcolor(9);
    settextstyle(SMALL_FONT, 0, 9);
    int y=height/6;
    //selectare
    graphic_button(60, y-5, 180, y+35);
    outtextxy(70, y, "Select");
    coordo[6][0]=60;
    coordo[6][1]=y-5;
    coordo[6][2]=180;
    coordo[6][3]=y+35;
    y+=35;
    ///accesarea se va face din doublu clic (folder/fisier)
    //adauga folder
    graphic_button(60, y-5, 180, y+35);
    outtextxy(70, y, "Mkdir");
    coordo[7][0]=60;
    coordo[7][1]=y-5;
    coordo[7][2]=180;
    coordo[7][3]=y+35;
    y+=35;
    ///adauga fisier
    graphic_button(60, y-5, 180, y+35);
    outtextxy(70, y, "Fopen");
    coordo[8][0]=60;
    coordo[8][1]=y-5;
    coordo[8][2]=180;
    coordo[8][3]=y+35;
    y+=35;
    ///sterge
    graphic_button(60, y-5, 180, y+35);
    outtextxy(70, y, "Delete");
    coordo[9][0]=60;
    coordo[9][1]=y-5;
    coordo[9][2]=180;
    coordo[9][3]=y+35;
}
void graphics_ALGbuttons()
{
    setcolor(15);
    settextstyle(SMALL_FONT, 0, 8);
    graphic_button(50, 30, 125, 75);
    outtextxy(58, 40, "HUF");
    coordo[10][0]=50;
    coordo[10][1]=30;
    coordo[10][2]=125;
    coordo[10][3]=75;
    graphic_button(125, 30, 200, 75);
    outtextxy(133, 40, "LZW");
    coordo[11][0]=125;
    coordo[11][1]=30;
    coordo[11][2]=200;
    coordo[11][3]=75;
}
void graphics_selected()
{
    setcolor(15);
    line(1040, 195+unit, 1440, 195+unit);
    file_coordo[nr_files_for_tar-1][0]=1000;
    file_coordo[nr_files_for_tar-1][1]=195+unit;
    file_coordo[nr_files_for_tar-1][2]=1440;

    settextstyle(SMALL_FONT, 0, 10);
    outtextxy(1040, 200+unit, file_name);

    if(strchr(file_name, '.')==NULL)
        readimagefile("photos/folder2.jpg", 1010, 200+unit, 1035, 235+unit);
    else
        readimagefile("photos/txt2.jpg", 1010, 200+unit, 1035, 235+unit);
    unit+=45;
    line(1040, 195+unit, 1440, 195+unit);
    file_coordo[nr_files_for_tar-1][3]=195+unit;
    graphics_GLOBALbuttons(5);
}
bool click_on_file(int x, int y, int which_button)
{
    if(x>=file_coordo[which_button][0] && x<=file_coordo[which_button][2])
        if(y>=file_coordo[which_button][1] && y<=file_coordo[which_button][3])
            return 1;
    return 0;
}
bool click_on_button(int x, int y, int which_button)
{
    if(x>=coordo[which_button][0] && x<=coordo[which_button][2])
        if(y>=coordo[which_button][1] && y<=coordo[which_button][3])
            return 1;
    return 0;
}


///EXPLORER SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void explorer(char mode[])
{
    //sterge highlight
    setfillstyle(SOLID_FILL, 0);
    bar(230, 143, 976, 920);

    int y=0;
    file_nr_visible=0;
    settextstyle(SMALL_FONT, 0, 8);
    if(strcmp(mode, "partitive")==0)
    {
        char last_partitive=0;
        for(int i='C'; i<='Z'; i++)
        {
            char s[5]="\0";
            s[0]=char(i);
            s[1]=':';
            s[2]='/';
            s[3]='\0';
            if(!is_folder(s))
                break;
            setcolor(15);
            line(230, 143+y, 974, 143+y);

            file_coordo[11+i-'C'][0]=230;
            file_coordo[11+i-'C'][1]=143+y;
            file_coordo[11+i-'C'][2]=974;

            setcolor(9);
            readimagefile("photos/folder2.jpg", 235, 150+y, 260, 150+y+25);
            outtextxy(270, 150+y, s);
            y+=40;

            file_coordo[11+i-'C'][3]=143+y;
            file_nr_visible++;

            strcpy(file_visible[11+i-'C'], s);
        }
        setcolor(15);
        line(230, 143+y, 974, 143+y);
    }
    else
    {
        if(strcmp(mode, "directory_iterator")==0)
        {
            //calea unde ai ajuns
            graphic_button(320, 90, 960, 130);
            setcolor(9);
            settextstyle(SMALL_FONT, 0, 8);
            outtextxy(330, 100, file_accessedPATH);
            int index=0;
            for(auto & p : filesystem::directory_iterator(file_accessedPATH))
                if(index<19)
                {
                    //gen las sa se vada doar 15 elemente maxim
                    char s[MAX]="\0";
                    strcpy(s, p.path().string().c_str());

                    get_FILEname(s);
                    strcpy(file_visible[11+index++], file_name);
                    setcolor(15);
                    line(230, 143+y, 974, 143+y);

                    file_coordo[10+index][0]=230;
                    file_coordo[10+index][1]=143+y;
                    file_coordo[10+index][2]=974;

                    setcolor(9);
                    if(is_folder(s))
                        readimagefile("photos/folder2.jpg", 235, 150+y, 260, 150+y+25);
                    else
                        readimagefile("photos/txt2.jpg", 235, 150+y, 260, 150+y+25);
                    outtextxy(270, 150+y, file_visible[11+index-1]);
                    y+=40;

                    file_coordo[10+index][3]=143+y;
                    file_nr_visible++;
                }
            setcolor(15);
            line(230, 143+y, 974, 143+y);
        }
    }
}
void file_explorer()
{
    cleardevice();
    readimagefile("photos/file explorer.jpg", 0, 0, width, height);
    graphics_EXPLbuttons();
    explorer("partitive");
    graphics_GLOBALbuttons(3);
}













///TAR SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool is_folder(char path[])
{
    if (filesystem::exists(filesystem::path(path)) && filesystem::path(path).extension() == "")
        return 1;
    return 0;
}
char* reverseArray(char arr[], int length)
{
    int start = 0;
    int end = length - 1;

    while (start < end)
    {
        // Swap characters at start and end indices
        char temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move indices towards the center
        start++;
        end--;
    }
    return arr;
}
void get_FILEname(char source_path[])
{
    memset(file_name, 0, sizeof file_name);
    for (int i = strlen(source_path) - 1; i; i--)
    {
        if (source_path[i] == 47)
        {
            if (i != strlen(source_path) - 1)
                break;
        }
        else
            file_name[strlen(file_name)] = source_path[i];
    }
    file_name[strlen(file_name)] = '\0';
    char* reversedArray = reverseArray(file_name, strlen(file_name));
    strcpy(file_name, reversedArray);
    file_name[strlen(file_name)] = '\0';
}

void help_build(char path_of_file[], FILE * p_bar, FILE * p_components)
{
    if(is_folder(path_of_file))//folder
    {
        //pun in stack
        get_FILEname(path_of_file);
        strcpy(S.folder_names[++S.nr_elem], file_name);
        //pun in fisier numele folderului
        fputs(identation, p_bar);
        fputs(file_name, p_bar);
        fputs("/\n", p_bar);
        strcat(identation, "\t\0");

        for(auto & p : filesystem::directory_iterator(path_of_file))//ia fisierele alfabetic
        {
            if(p.path().empty()==false)
            {
                //transformare din string in char(BUGS!)
                char IN_folder[MAX];
                strcpy(IN_folder, p.path().string().c_str());
                for(int i=0;i<strlen(IN_folder);i++)
                    if(IN_folder[i]==92)
                        IN_folder[i]='/';
                IN_folder[strlen(IN_folder)]='\0';

                help_build(IN_folder, p_bar, p_components);
                memset(IN_folder, 0, sizeof IN_folder);
            }
        }

        //a ajuns la final
        strcpy(S.folder_names[S.nr_elem--], "\0");
        identation[strlen(identation)-1]='\0';
        fputs(identation, p_bar);
        fputs("end_oF_", p_bar);
        get_FILEname(path_of_file);
        fputs(file_name, p_bar);
        fputs("/\n", p_bar);
    }
    else//fisier normal
    {
        p_components=fopen(path_of_file, "r");
        if(p_components == NULL) ///i love my girlfriend!!!
        {
            cout<<"error\n";
            return;
        }

        get_FILEname(path_of_file);
        fputs(identation, p_bar);
        fputs(file_name, p_bar);
        fputs("\n\n", p_bar);

        //copierea informatiei
        char temp;
        while((temp=fgetc(p_components))!=EOF)
            fputc(temp, p_bar);

        fputs("\n\n", p_bar);
        fputs(file_separator, p_bar);
        fputs("\n\n", p_bar);

        fclose(p_components);
    }
}
void build_tar()
{
    char path_of_file[MAX];
    FILE *p_bar, *p_components;
    p_bar=fopen(path_of_tar, "w");
    if(p_bar == NULL)
    {
        cout<<"error";
        return;
    }

    int index=0, k=nr_files_for_tar;
    while(index<k)
    {
        strcpy(path_of_file, input_for_paths[index]);
        help_build(path_of_file, p_bar, p_components);
        index++;
    }

    fclose(p_bar);
}

void help_decompose(char line[], char destination[], FILE * p_bar, FILE * p_components, bool condition)
{
    if(condition==0)
    {
        line[strlen(line)-1]='\0';
        while(line[0]=='\t')
            strcpy(line, line+1);
        if(line[strlen(line)-1]=='/')//NUME FOLDER
        {
            char previous_line[MAX];
            strcpy(previous_line, line);

            char new_destination[MAX];
            strcpy(new_destination, destination);
            //creare folder
            strcat(new_destination, line);
            mkdir(new_destination);
            strcpy(S.folder_names[++S.nr_elem], new_destination);

            fgets(line, MAX, p_bar);
            while(strstr(line, "end_oF_")==NULL && strstr(line, previous_line)==NULL)
            {
                help_decompose(line, new_destination, p_bar, p_components, 0);
                fgets(line, MAX, p_bar);
            }

            strcpy(S.folder_names[S.nr_elem--], "\0");
            return;
        }
        else//NUME FISIER
        {
            char new_destination[MAX];
            strcpy(new_destination, destination);
            strcat(new_destination, line);
            condition=1;
            fgets(line, MAX, p_bar);
            help_decompose(line, new_destination, p_bar, p_bar, 1);
        }
    }
    else//vorbim de continut aici
    {
        p_components=fopen(destination, "w");
        if(p_components)
        {
            while(1)//adauga la final de fisier "\n\n"
            {
                fgets(line, MAX, p_bar);
                if(strstr(line, file_separator))
                {
                    fgets(line, MAX, p_bar);
                    break;
                }
                fputs(line, p_components);
            }
        }
        else
        {
            cout<<"error";
            return;
        }
        condition=0;
        fclose(p_components);
    }
}
void decompose_tar()
{
    FILE *p_bar, *p_components;
    p_bar=fopen(path_of_tar, "r");
    if(p_bar == NULL)
    {
        cout<<"error";
        return;
    }

    char path[MAX];
    strcpy(path, path_decompose);
    strcat(path, decompose_name);
    mkdir(path);
    //prima oara citesteste calea, afisarea pana la intalnirea file_separator
    char line[MAX];
    while(fgets(line, MAX, p_bar))
        help_decompose(line, path, p_bar, p_components, 0);
    /*
    0-NU STIU, prima linie
    1-DACA FIX INAINTE A FOST ANUNTAT NUME DE CEVA
    */
    fclose(p_bar);
}
