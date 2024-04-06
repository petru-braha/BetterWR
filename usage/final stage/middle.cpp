#include "middle.h"
#include <stdio.h>

#include "huffman.h"
#include "lzw.h
bool compressHuf_paste(char* path_output, char* output_name) //the temp file is built, ik its location => encoding, final output
{
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
