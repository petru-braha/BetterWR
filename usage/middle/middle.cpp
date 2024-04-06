#include "middle.h"
#include <stdio.h>

#include "huffman.h"
#include "lzw.h

void savedSize(size_t originalSize, size_t encodedSize)
{
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