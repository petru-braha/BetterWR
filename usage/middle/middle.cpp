#include <iostream>
#include <filesystem>

#include "middle.h"
#include "../../admin/packing_functions.h"
#include "../../algorithms/huffman.h"
#include "../../algorithms/lzw.h"

#define K 1000 //one etern buffer

void savedSize(size_t originalSize, size_t encodedSize){
    size_t bytesSaved = originalSize - encodedSize;
    std::cout << "Original size: " << originalSize << " bits" << " (" << originalSize / 8 << " bytes).\n";
    std::cout << "Encoded size: " << encodedSize << " bits" << " (" << encodedSize / 8 << " bytes).\n";
    std::cout << "Bits saved: " << bytesSaved << " bits" << " (" << bytesSaved / 8 << " bytes).\n";
    std::cout << endl;
}
bool compressHuf_paste(char* path_output, char* output_name) //the temp file is built, ik its location => encoding, final output
{
    FILE* input = fopen("../../files/temp.txt", "rb");
    FILE* output = fopen(strcat(path_output, output_name), "wb");
    char buffer[K * K];
    for (int i = 0; i < BUFFER_SIZE; ++i)
        buffer[i] = 0;
    size_t bytesRead = fread(buffer, sizeof(char), K * K, input);
    if (input == nullptr || output == nullptr)
    {
        printf("error: missing file.\n");
        fclose(input);
        return false;
    }

    //from binary to ASCII
    string binaryData(buffer, bytesRead);
    node* root = buildHuffmanTree(binaryData);
    string encodedString = "";
    HuffmanEncode(root, binaryData, encodedString);
    string textToOutput = writeEncodedDataToFile(encodedString);

    char treeInfo[MAX];
    int treeFreq[MAX], int treeSize = 0;
    createTreeString(root, 1, treeInfo, treeFreq, treeSize);

    fwrite(&treeSize, sizeof(int), 1, output);
    for (int i = 1; i <= treeSize; ++i)
        fwrite(&treeFreq[i], sizeof(int), 1, output);
    for (int i = 1; i <= treeSize; ++i)
        fwrite(&treeInfo[i], sizeof(char), 1, output);

    int bitlength = encodedString.size();
    fwrite(&bitlength, sizeof(int), 1, output);
    fwrite(textToOutput.c_str(), sizeof(char), textToOutput.size(), output);

    size_t originalSize = bytesRead * 8;
    size_t encodedSize = textToOutput.size() * 8;
    savedSize(originalSize, encodedSize);

    fclose(input);
    fclose(output);
    return true;
}

bool compressLzw_paste(char* path_output, char* output_name)
{
    FILE* input = fopen("../../files/temp.txt", "rb");
    FILE* output = fopen(strcat(path_output, output_name), "wb");
    char buffer[K * K];
    for (int i = 0; i < BUFFER_SIZE; ++i)
        buffer[i] = 0;
    size_t bytesRead = fread(buffer, sizeof(char), K * K, input);
    if (input == nullptr || output == nullptr)
    {
        printf("error: missing file.\n");
        fclose(input);
        return false;
    }

    // Realizarea encodarii LZW
    lzw_encode(buffer, sizeof(buffer), encoded_text);
    int n = Len(encoded_text, MAX);

    // Convertire int to string pentru a scrie mai usor textul encodat in fisier
    string encoded_text_char = {};
    for (int x = 0; x < n; x++)
        encoded_text_char += to_string(encoded_text[x]) + ' ';

    size_t originalSize = bytesRead * 8;
    size_t encodedSize = encoded_text_char.size() * 8;
    for (size_t i = 0; i < n; ++i)
        fprintf(output, "%d ", static_cast<int>(encoded_text[i]));
    savedSize(originalSize, encodedSize);

    delete[] encoded_text;
    fclose(input);
    fclose(output);
    return true;
}

bool decompressHuf(char* path_input, char* path_output, char* output_name)
{
    std::filesystem::path p_path(path_input);
    std::error_code ec;
    if (std::filesystem::path(p_path, ec).extension().string().c_str() != "huf"){
        std::cout<<"error - decompression: wrong file extension / selected algorithm.\n";
        return false;
    }

    FILE* input  = fopen(path_input, "rb");
    FILE* output = fopen(strcat(), "wb");
    if (output == nullptr || input == nullptr) {
        printf("error - decompression: invalid file paths.\n");
        fclose(input); fclose(output);
        return false
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

    node* rootNode = reconstructTree(treeSize, 1, treeInfo, treeFreq); //reconstruct huffman tree
    string codes = ASCIIToBinary(binaryData, bitlength); // ASCII => string of bits => decode

    // Realizarea decodarii Huffman si scrierea textului decodat in fisier
    string decodedOutput = "";
    HuffmanDecode(rootNode, codes, decodedOutput);
    fwrite(decodedOutput.c_str(), sizeof(char), decodedOutput.size(), output);

    fclose(input);
    fclose(output);
}

bool decompressLzw(char* path_output, char* output_name)
{
    if (isFileExtension(inputFile, "lzw"));
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
}


void display_instructions_bash() {
    std::cout << "Usage: " << "<operation> <algorithm> <nr_input_files> <input_file_paths> <output_path>\n";
    std::cout << "Check for syntax errors:\n";
    std::cout << "operations: 'compress' / 'decompress'\n";
    std::cout << "algorithms: 'HUF' / 'LZW'\n";
    std::cout << "check if the number of paths given is < 10 and is equal with nr_input_files.\ncheck if the paths are valid.\n\n";
}
bool verification(int argc, char** argv){
    if (argc < 7)
    {
        std::cout << "Usage: " << "<operation> <algorithm> <nr_input_files> <input_file_paths> <output_path> <output_name>\n";
        return false;
    }

    if (strcmp(argv[1], "compress") && strcmp(argv[1], "decompress"))
    {
        std::cout << "error: invalid first argument.\n\n";
        display_instructions_bash();
        return false;
    }

    if (strcmp(argv[2], "HUF") && strcmp(argv[2], "LZW"))
    {
        std::cout << "error: invalid second argument.\n\n";
        display_instructions_bash();
        return false;
    }

    int nr = 0;
    for (int i = 0; argv[3][i]; i++)
        nr = nr * 10 + (argv[3][i] - '0');
    if (nr + 5 != argc || nr <= 0 || nr > 10)
    {
        std::cout << "error: invalid third argument.\n\n";
        display_instructions_bash();
        return false;
    }

    //validation of paths
    for (int i = 0; i < nr; i++)
        if (std::filesystem::exists(argv[i + 4]) == 0)
        {
            std::cout << "error: invalid input_path argument.\n\n";
            display_instructions_bash();
            return false;
        }

    if (std::filesystem::exists(argv[argc - 2]) == 0)
    {
        std::cout << "error: invalid output_path argument.\n\n";
        display_instructions_bash();
        return false;
    }

    for (int i = 0; i < strlen(argv[argc - 1]); i++)
        if (argv[argc - 1][i] < 'A' || argv[argc - 1][i] > 'Z' || (argv[argc - 1][i] > 'Z' && argv[argc - 1][i] < 'a'))
        {
            std::cout << "error: invaid name.\n\n";
            return false;
        }
    return true;
}


void very_last_step(char* operation, char* algorithm, short nr_paths, char** paths_input, char* path_output, char* output_name)
{
    if (strcmp(operation, "compress") == 0)
    {
        build_tar(nr_paths, paths_input); //path iterator
        if (strcmp(algorithm, "HUF") == 0)
            compressHuf_paste(path_output, output_name);
        if (strcmp(algorithm, "LZW") == 0)
            compressLzw_paste(path_output, output_name);
    }
    else
    {
        for(int i=0; i < nr_paths; i++)
        {
            if (strcmp(algorithm, "HUF") == 0)
                decompressHuf(paths_input[i], path_output, output_name);
            if (strcmp(algorithm, "LZW") == 0)
                decompressLzw(paths_input[i], path_output, output_name);
            //delete content of temp.txt
            decompose_tar(path_output); //input temp.txt
        }

    }
    if(remove("files/temp.txt"))
        std::cout<<"error: temporary file not deleted.\n";
}
