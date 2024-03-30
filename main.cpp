#include "libraries.h"

#include "algorithms/huffman.h"
#include "algorithms/lzw.h"

#include "global_variables.h"
#include "packing_functions.h"
#include "graphics_functions.h"

#include "explorer/explorer.h"

///COMMANDS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
extern struct point{
    int x, y;
} mouse;

//void define_announcement(bool mode);
void change_extension(char type[]) //are ca input un fisier tar corect
{
    if(std::filesystem::path(path_of_tar).extension()==".txt")
        strcpy(strstr(path_of_tar, ".txt"), type);
    else
        strcpy(strchr(path_of_tar, '.'), ".txt");
}

void commands_firstStep_menu(int &which_button);
void commands_secondStep_decideOperation(int which_button, bool &first_command)
{
    if(file_accessedPATH[0]==0)
    {
        if(which_button)
            {
                if(which_button==3)
                {
                    start_graphics(0);
                    setcolor(15);
                    settextstyle(DEFAULT_FONT, 0, 2);
                    outtextxy(coordo[0][0], coordo[0][1], "Cititi fisierul: readME.txt");
                    delay(1500);
                    system("readME.txt");
                }
                else
                {
                    if(first_command)
                    {
                        file_explorer();
                        first_command=0;
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
}

void commands()
{
    bool first_command=1;
    int which_button=0;

    while(1)
    {
        commands_firstStep_menu(which_button);
        commands_secondStep_decideOperation(which_button, first_command);

        ///FILESYSTEM
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
                                char file_name[MAX];
                                strcpy(file_name, get_FILEname(input_for_paths[i]));
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
                            strcpy(file_lastOPENED, get_FILEname(file_accessedPATH));
                            strcpy(strstr(file_accessedPATH, file_lastOPENED), "\0");
                            strcpy(file_lastOPENED, get_FILEname(file_accessedPATH));
                            std::cout<<file_accessedPATH<<'\n';
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
                        first_command=1;
                        alg=0;
                        //delete data
                        for(int i=0;i<nr_files_for_tar;i++)
                            memset(input_for_paths[i], 0, sizeof input_for_paths[i]);
                        nr_files_for_tar=0;
                        start_graphics(0);
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
                            char file_name[MAX];
                            strcpy(file_name, get_FILEname(input_for_paths[i]));
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
                        std::cout<<nr_files_for_tar;
                        std::cout<<"error: please choose an algorithm";
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
                                //UNDE VREI SA O PUI, CUM SA SE NUMEASCA ARHIVA?

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
                                //UNDE VREI SA O PUI, CUM SA SE NUMEASCA ARHIVA
                            }
                        }
                        else
                        {
                            if(strcmp(std::filesystem::path(input_for_paths[0]).extension().string().c_str(), ".huf")==0)
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
                        std::cin>>new_name;
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
                                    graphics_selected(get_FILEname(temp), nr_files_for_tar);
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
                                        std::cout<<file_accessedPATH<<'\n';
                                        explorer("directory_iterator");
                                    }
                                    else
                                    {
                                        char exe[MAX];
                                        strcpy(exe, file_accessedPATH);
                                        strcpy(strstr(file_accessedPATH, file_lastOPENED), "\0");
                                        strcpy(file_lastOPENED, get_FILEname(file_accessedPATH));
                                        std::cout<<file_accessedPATH<<'\n';
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
    start_graphics(1);
    graphics_MENUbuttons();
    commands();
    closegraph();
    return 0;
}

//expl
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
        for(int i='A'; i<='Z'; i++)
        {
            char s[5]="\0";
            s[0]=char(i);
            s[1]=':';
            s[2]='/';
            s[3]='\0';
            if(is_folder(s))
            {
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
            for(auto & p : std::filesystem::directory_iterator(file_accessedPATH))
                if(index<19)
                {
                    //gen las sa se vada doar 15 elemente maxim
                    char s[MAX]="\0";
                    strcpy(s, p.path().string().c_str());

                    strcpy(file_visible[11+index++], get_FILEname(s));
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



///pack
void help_build(char path_of_file[], FILE * p_bar, FILE * p_components)
{
    if(is_folder(path_of_file))//folder
    {
        //pun in stack
        strcpy(S.folder_names[++S.nr_elem], get_FILEname(path_of_file));
        //pun in fisier numele folderului
        fputs(identation, p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
        fputs("/\n", p_bar);
        strcat(identation, "\t\0");

        for(auto & p : std::filesystem::directory_iterator(path_of_file))//ia fisierele alfabetic
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

        //END
        strcpy(S.folder_names[S.nr_elem--], "\0");
        identation[strlen(identation)-1]='\0';
        fputs(identation, p_bar);
        fputs("end_oF_", p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
        fputs("/\n", p_bar);
    }
    else//normal file
    {
        p_components=fopen(path_of_file, "r");
        if(p_components == NULL) ///i love my girlfriend!!!
        {
            std::cout<<"error - composition: missing/corrupted file";
            return;
        }

        fputs(identation, p_bar);
        fputs(get_FILEname(path_of_file), p_bar);
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
        std::cout<<"error - composition: the requested file is missing\n";
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
    else///content
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
            std::cout<<"error - decomposition: can not write the files\n";
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
        std::cout<<"error - decomposition: the requested file is missing\n";
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

/**
to do:
-dezarhivare
-mkdir, fopen
-ce se intampla dupa gata(se inchide, afisare pe desktop)
*/
