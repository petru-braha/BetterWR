#pragma warning(disable:4996)

#include <iostream>
#include <unordered_map>
#include <queue>
#include "huffman.h"
#include "lzw.h"
#include <cstring>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <filesystem>   //verific foldere
#include <direct.h>     //creare foldere

#define MAX_PATH_LENGTH 300
#define MAX_FILES 100
using namespace std;

// variabile globale folosite in lucrul cu foldere
struct stack {
    int nr_elem;
    char folder_names[MAX_FILES][MAX_PATH_LENGTH];
} static S;

int nr_files_for_tar;
static char** input_for_paths;
static char file_separator[MAX_PATH_LENGTH] = "*SEPARATOR*";
static char identation[MAX_PATH_LENGTH];
static char path_of_tar[MAX_PATH_LENGTH] = "C:/Users/ROGER/Desktop/TestFolderArhivat.txt";      // A SE MODIFICA PATH-UL
static char path_decompose[] = "C:/Users/ROGER/Desktop/";                                       // A SE MODIFICA PATH-UL
static char decompose_name[] = "TestFolderDezarhivat/";  //NUME FOLDER FISIERE DECOMPRIMATE
static char file_name[MAX_PATH_LENGTH];

// declarari de functii folosite in lucrul cu foldere
char* reverseArray(char arr[], int length);
void get_FILEname(char source_path[]);
bool is_folder(char path[]);
void help_build(char path_of_file[], FILE* p_bar, FILE* p_components);
void build_tar();
void help_decompose(char line[], char destioantion[], FILE* p_bar, FILE* p_components, bool condition);
void decompose_tar();
void convertToUppercase(string& input);
void convertToLowercase(string& input);


// functie pentru a verifica extensia fisierului
bool isFileExtension(const char* filename, const char* extension)
{
    // cautam aparitia caracterului '.' in numele fisierului
    const char* dotPosition = strrchr(filename, '.');

    // verificam daca '.' exista si daca extensia corespune
    if (dotPosition != nullptr) {
        return strcmp(dotPosition + 1, extension) == 0;
    }

    return false;
}

// functie care afiseaza dimensiunea economisita dupa folosirea algoritmilor
void savedSize(size_t originalSize, size_t encodedSize)
{
    // Compararea dimensiunii originale cu cea a datelor codate 
    size_t bytesSaved = originalSize - encodedSize;
    cout << endl;
    cout << "Original size: " << originalSize << " bits" << " (" << originalSize / 8 << " bytes)" << endl;
    cout << "Encoded size: " << encodedSize << " bits" << " (" << encodedSize / 8 << " bytes)" << endl;
    cout << "Bits saved: " << bytesSaved << " bits" << " (" << bytesSaved / 8 << " bytes)" << endl;
    cout << endl;
}

int main(int argc, char** argv)
{
    //Alternativ (ATENTIE !! a se modifica si continutul instructiunilor de decizie IF intr-un mod corespunzator):
    /*int optionSelect, algSelect;    
    cout << "Selectati operatia dorita : 1 - compresie , 2 - decompresie, 3 - compresie folder, 4 - decompresie folder" << endl;
    
    cin >> optionSelect;*/

    // IMPORTANT! A se rula folosind comanda  g++ -std=c++17 main.cpp huffmanFunctions.cpp lzwFunctions.cpp -o "numele executabilului"

    FILE* input = nullptr, * output = nullptr;
    char* optionSelect, * algSelect;
   
    // Verificam daca exista destule argumente pentru linia de comanda
    if (argc < 3 && strcmp(argv[1],"compresie_folder") != 0 && strcmp(argv[1], "decompresie_folder") != 0) {
        cout << "Usage: " << argv[0] << " <operation> <algorithm> <input_file> <output_file>" << endl;
        return 1;
    }

    optionSelect = argv[1];

    if (strcmp(optionSelect, "compresie") == 0) 
    {
        if (argc < 5) {
            cout << "Usage: " << argv[0] << " 1 <algorithm> <input_file> <output_file>" << endl;
            return 1;
        }
        algSelect = argv[2];
        const char* inputFile = argv[3];
        const char* outputFile = argv[4];

        // Alternativ: 
        //cout << "Introduceti algoritmul utilizat pentru comprimare: 1 - HUF , 2 - LZW" << endl;
        //cin >> algSelect;

        if (strcmp(algSelect, "HUF") == 0)
        {
            // Deschidem fisierul de input pentru citire
            input = fopen(inputFile, "rb");
            if (input == NULL) {
                printf("Error opening input file\n");
                exit(1);
            }

            // Deschidem fisierul de output pentru a scrie datele codate
            output = fopen(outputFile, "wb");
            if (output == NULL) {
                printf("Error opening output file\n");
                fclose(input);
                exit(1);
            }

            // Citim datele din input si le punem intr-un buffer
            const int BUFFER_SIZE = 30000;  // adjustare manuala
            char buffer[BUFFER_SIZE];
            size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
            if (bytesRead <= 0) {
                printf("Error reading input file\n");
                fclose(input);
                exit(1);
            }

            // Crearea unui string din bufferul citit din fisier
            string binaryData(buffer, bytesRead);

            // Realizarea codarii Huffman
            node* root = buildHuffmanTree(binaryData);
            string encodedString = "";
            HuffmanEncode(root, binaryData, encodedString);

            // Convertim string-ul binar in simboluri ASCII
            string textToOutput = writeEncodedDataToFile(encodedString);
            
            // Salvam informatiile despre arborele Huffman, care vor fi stocate la inceputul fisierului encodat
            char treeInfo[MAX];
            int treeFreq[MAX];
            int treeSize = 0;
            createTreeString(root, 1, treeInfo, treeFreq, treeSize);

            fwrite(&treeSize, sizeof(int), 1, output);

            for(int i = 1; i <= treeSize; ++i)
                fwrite(&treeFreq[i], sizeof(int), 1, output);

            for (int i = 1; i <= treeSize; ++i)
                fwrite(&treeInfo[i], sizeof(char), 1, output);

            int bitlength = encodedString.size();
            fwrite(&bitlength, sizeof(int), 1, output);

            fwrite(textToOutput.c_str(), sizeof(char), textToOutput.size(), output);    // scriem in fisier textul encodat

            // Calculam dimensiunea datelor 
            size_t originalSize = bytesRead * 8;
            size_t encodedSize = textToOutput.size() * 8;

            // Afisam diferentele de marime a fisierelor
            savedSize(originalSize, encodedSize);

            fclose(input);
            fclose(output);
        }
        else
        {
            if (strcmp(algSelect, "LZW") == 0)
            {
                int* encoded_text;
                encoded_text = new int[MAX];
                memset(encoded_text, 0, MAX * sizeof(int));

                // Deschidem fisierul de input pentru citire
                input = fopen(inputFile, "rb");
                if (input == NULL) {
                    printf("Error opening input file\n");
                    exit(1);
                }

                // Deschidem fisierul de output pentru a scrie datele codate
                output = fopen(outputFile, "wb");
                if (output == NULL) {
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
                if (bytesRead <= 0) {
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
                {
                    encoded_text_char += to_string(encoded_text[x]) + ' ';
                }

                // Calculam dimensiunea datelor 
                size_t originalSize = bytesRead * 8;
                size_t encodedSize = encoded_text_char.size() * 8;

                for (size_t i = 0; i < n; ++i) {
                    fprintf(output, "%d ", static_cast<int>(encoded_text[i]));      // scriem in fisier textul encodat        
                }

                // Afisam diferentele de marime a fisierelor
                savedSize(originalSize, encodedSize);

                delete[]encoded_text;

                fclose(input);
                fclose(output);
                return 0;
            }
            else
            {
                cout << "EROARE!" << endl;
                return 0;
            }
        }
    }
    else
    {
        if (strcmp(optionSelect, "decompresie") == 0)
        {

           if (argc < 4) {
                cout << "Usage: " << argv[0] << " 2 <input_file> <output_file>" << endl;
                return 1;
            }
            const char* inputFile = argv[2];
            const char* outputFile = argv[3];
            
            // Alternativ: 
            /*cout << "Enter the filename: ";
            char filename[256];
            cin.ignore();
            cin.getline(filename, 256);*/

            if (isFileExtension(inputFile, "huf"))
            {
                // Deschidem fisierul de input pentru citire
                input = fopen(inputFile, "rb");
                if (input == NULL) {
                    printf("Error opening input file\n");
                    exit(1);
                }

                // Deschidem fisierul de output pentru a scrie datele codate
                output = fopen(outputFile, "wb");
                if (output == NULL) {
                    printf("Error opening output file\n");
                    fclose(input);
                    exit(1);
                }

                // Citim datele din input si le punem intr-un buffer
                const int BUFFER_SIZE = 30000;  // adjustare manuala
                char buffer[BUFFER_SIZE];

                // Intai recuperam informatiile despre arborele Huffman
                char treeInfo[MAX];
                int treeFreq[MAX];
                int treeSize = 1;
                int bitlength;

                fread(&treeSize, sizeof(int), 1, input);

                for (int i = 1; i <= treeSize; ++i) 
                {
                    fread(&treeFreq[i], sizeof(int), 1, input);
                }

                for (int i = 1; i <= treeSize; ++i) {
                    fread(&treeInfo[i], sizeof(char), 1, input);
                }
    
                fread(&bitlength, sizeof(int), 1, input);
                
                // Citim restul continutului, care reprezinta de fapt textul encodat
                size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
                if (bytesRead <= 0) {
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
                fwrite(decodedOutput.c_str(), sizeof(char), decodedOutput.size(), output);

                fclose(input);
                fclose(output);

                return 0;
            }
            else
            {
                if (isFileExtension(inputFile, "lzw"))
                {
                    int* decoded_text;
                    decoded_text = new int[MAX];
                    memset(decoded_text, 0, MAX * sizeof(int));

                    char* output_text;
                    output_text = new char[MAX];
                    memset(output_text, 0, MAX * sizeof(char));

                    // Deschidem fisierul de input pentru citire
                    input = fopen(inputFile, "rb");
                    if (input == NULL) {
                        printf("Error opening input file\n");
                        exit(1);
                    }

                    // Deschidem fisierul de output pentru a scrie datele codate
                    output = fopen(outputFile, "wb");
                    if (output == NULL) {
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
                    if (bytesRead <= 0) {
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

                    return 0;
                }
            }
        }
        else
        {
            if (strcmp(optionSelect,"compresie_folder") == 0)
            {
                // Citim numarul de fisiere care vor fi date ca input
                cout << "Enter the number of files: ";
                cin >> nr_files_for_tar;

                // Alocam memorie pentru vectorul de inputs
                input_for_paths = new char* [nr_files_for_tar];
                for (int i = 0; i < nr_files_for_tar; ++i)
                {
                    input_for_paths[i] = new char[MAX_PATH_LENGTH];
                }

                // Citim de la tastatura path-urile pentru fisiere
                cin.ignore();
                for (int i = 0; i < nr_files_for_tar; ++i)
                {
                    cout << "Enter file path " << i + 1 << ": ";
                    cin.getline(input_for_paths[i], MAX_PATH_LENGTH);
                }

                cout << endl;
                // Construim fisierul text care contine structura de foldere encodata folosind algoritmul Huffman
                // Structura va fi afisata pe ecran pentru verificare
                build_tar();

                // Deschidem fisierul de input pentru citire
                input = fopen(path_of_tar, "rb+");
                if (input == NULL) {
                    printf("Error opening input file\n");
                    exit(1);
                }

                // Citim datele din input si le punem intr-un buffer
                const int BUFFER_SIZE = 30000;  // adjustare manuala
                char buffer[BUFFER_SIZE];
                size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
                if (bytesRead <= 0) {
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

                // Salvam informatiile despre arborele Huffman, care vor fi stocate la inceputul fisierului encodat
                char treeInfo[MAX];
                int treeFreq[MAX];
                int treeSize = 0;
                createTreeString(root, 1, treeInfo, treeFreq, treeSize);

                // Dupa ce am obtinut informatiile din fisierul nostru text si am encodat-o folosind Huffman, redeschidem acelasi fisier pentru a scrie informatia encodata
                output = fopen(path_of_tar, "wb+");
                if (output == NULL) {
                    printf("Error opening input file\n");
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

                fclose(input);
                fclose(output);
                return 0;
            }
            else
            {
                if (strcmp(optionSelect, "decompresie_folder") == 0)
                {
                    // Deschidem fisierul de input pentru citire
                    input = fopen(path_of_tar, "rb+");
                    if (input == NULL) {
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
                    {
                        fread(&treeFreq[i], sizeof(int), 1, input);
                    }

                    for (int i = 1; i <= treeSize; ++i) {
                        fread(&treeInfo[i], sizeof(char), 1, input);
                    }

                    int bitlength;
                    fread(&bitlength, sizeof(int), 1, input);

                    size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
                    if (bytesRead <= 0) {
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
                    if (output == NULL) {
                        printf("Error opening input file\n");
                        exit(1);
                    }

                    fwrite(decodedOutput.c_str(), sizeof(char), decodedOutput.size(), output);

                    fclose(input);
                    fclose(output);

                    // Restabilim folderele
                    decompose_tar();
                    cout << endl;

                    return 0;
                }
                else
                {
                    cout << "EROARE! OPTIUNE INEXISTENTA!" << endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}

// functii ce tin de lucrul cu foldere

char* reverseArray(char arr[], int length)
{
    int start = 0;
    int end = length - 1;

    while (start < end) {
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

void convertToUppercase(string& input) {

    for (char& c : input) {
        if (std::islower(c)) {
            c = std::toupper(c);
        }
    }
}

void convertToLowercase(string& input) {

    for (char& c : input) {
        if (std::isupper(c)) {
            c = std::tolower(c);
        }
    }
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

bool is_folder(char path[])
{
    if (filesystem::exists(filesystem::path(path)) && filesystem::path(path).extension() == "")
        return 1;
    return 0;
}

//pentru numele fisierelor se va face identare, nu si pt continutul lor! vezi comentariul de final pentru a vedea cum se va face treaba
void help_build(char path_of_file[], FILE* p_bar, FILE* p_components)
{
    if (is_folder(path_of_file))//folder
    {
        //pun in stack
        get_FILEname(path_of_file);
        strcpy(S.folder_names[++S.nr_elem], file_name);

        //pun in fisier numele folderului
        fputs(identation, p_bar);
        fputs(file_name, p_bar);
        fputs("/\n", p_bar);
        strcat(identation, "\t\0");

        for (auto& p : filesystem::directory_iterator(path_of_file))//ia fisierele alfabetic
        {
            if (p.path().empty() == false)
            {
                //transformare din string in char(BUGS!)
                char IN_folder[MAX_PATH_LENGTH];
                strcpy(IN_folder, p.path().string().c_str());
                for (int i = 0; i < strlen(IN_folder); i++)
                    if (IN_folder[i] == 92)
                        IN_folder[i] = '/';
                IN_folder[strlen(IN_folder)] = '\0';

                help_build(IN_folder, p_bar, p_components);
                memset(IN_folder, 0, sizeof IN_folder);
            }
        }

        //a ajuns la final
        strcpy(S.folder_names[S.nr_elem--], "\0");
        identation[strlen(identation) - 1] = '\0';
        fputs(identation, p_bar);
        fputs("end_of_", p_bar);
        get_FILEname(path_of_file);
        fputs(file_name, p_bar);
        fputs("/\n", p_bar);
    }
    else//fisier normal
    {
        p_components = fopen(path_of_file, "r");
        if (p_components == NULL)
        {
            cout << "error\n";
            return;
        }

        get_FILEname(path_of_file);
        fputs(identation, p_bar);
        fputs(file_name, p_bar);
        fputs("\n\n", p_bar);

        //copierea informatiei
        char temp;
        while ((temp = fgetc(p_components)) != EOF)
            fputc(temp, p_bar);
        fputs("\n\n", p_bar);
        fputs(file_separator, p_bar);
        fputs("\n\n", p_bar);

        fclose(p_components);
    }
}
void build_tar()
{
    char path_of_file[MAX_PATH_LENGTH];
    FILE* p_bar, * p_components = nullptr;
    p_bar = fopen(path_of_tar, "w");
    if (p_bar == NULL)
    {
        cout << "error";
        return;
    }

    int index = 0, k = nr_files_for_tar;
    while (index < k)
    {
        strcpy(path_of_file, input_for_paths[index]);
        help_build(path_of_file, p_bar, p_components);
        index++;
    }

    fclose(p_bar);
}

void help_decompose(char line[], char destination[], FILE* p_bar, FILE* p_components, bool condition)
{
    if (condition == 0)
    {
        line[strlen(line) - 1] = '\0';
        while (line[0] == '\t')
            strcpy(line, line + 1);
        if (line[strlen(line) - 1] == '/')//NUME FOLDER
        {
            char previous_line[MAX_PATH_LENGTH];
            strcpy(previous_line, line);

            char new_destination[MAX_PATH_LENGTH];
            strcpy(new_destination, destination);
            //creare folder
            strcat(new_destination, line);
            mkdir(new_destination);
            strcpy(S.folder_names[++S.nr_elem], new_destination);

            fgets(line, MAX_PATH_LENGTH, p_bar);
            while (strstr(line, "end_oF_") == NULL && strstr(line, previous_line) == NULL)
            {
                help_decompose(line, new_destination, p_bar, p_components, 0);
                fgets(line, MAX_PATH_LENGTH, p_bar);
            }

            strcpy(S.folder_names[S.nr_elem--], "\0");
            return;
        }
        else//NUME FISIER
        {
            char new_destination[MAX_PATH_LENGTH];
            strcpy(new_destination, destination);
            strcat(new_destination, line);
            condition = 1;
            fgets(line, MAX_PATH_LENGTH, p_bar);
            help_decompose(line, new_destination, p_bar, p_bar, 1);
        }
    }
    else//vorbim de continut aici
    {
        p_components = fopen(destination, "w");
        if (p_components)
        {
            int ok = 0;
            bool first = 1;
            while (1)
            {
                fgets(line, MAX_PATH_LENGTH, p_bar);
                if (strstr(line, file_separator))
                {
                    fgets(line, MAX_PATH_LENGTH, p_bar);
                    break;
                }
                else
                {
                    if ((strcmp(line, "\n") == 0))
                        ok++;
                    else
                    {
                        if (first == 0)
                            fputs("\n", p_components);
                        first = 0;
                        while (ok)
                        {
                            fputs("\n", p_components);
                            ok--;
                        }
                        line[strlen(line) - 1] = '\0';
                        fputs(line, p_components);
                    }
                }
            }
        }
        else
        {
            cout << "error";
            return;
        }
        condition = 0;
        fclose(p_components);
    }
}
void decompose_tar()
{
    FILE* p_bar, * p_components = nullptr;
    p_bar = fopen(path_of_tar, "r");
    if (p_bar == NULL)
    {
        cout << "error";
        return;
    }

    char path[MAX_PATH_LENGTH];
    strcpy(path, path_decompose);
    strcat(path, decompose_name);
    mkdir(path);
    //prima oara citesteste calea, afisarea pana la intalnirea file_separator
    char line[MAX_PATH_LENGTH];
    while (fgets(line, MAX_PATH_LENGTH, p_bar))
        help_decompose(line, path, p_bar, p_components, 0);
    /*
    0-NU STIU, prima linie
    1-DACA FIX INAINTE A FOST ANUNTAT NUME DE CEVA
    */
    fclose(p_bar);
}