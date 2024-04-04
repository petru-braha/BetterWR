#include <iostream>
#include <graphics.h>
#include "../graphics_functions.h"

void commands();
void decide_boot(int argc, char** argv)
{
    FILE* input = nullptr, * output = nullptr;
    char* optionSelect, * algSelect;

    ///graphics?
    if(argc == 1)
    {
        short screen_x = 0, screen_y = 0;
        define_fullscreen(screen_x, screen_y);
        if(screen_x==0 || screen_y==0)
            exit(1);

        initwindow(screen_x, screen_y, "", -3, -3);
        start_graphics(1);
        graphics_MENUbuttons();
        commands();
        closegraph();
        exit(0);
    }

    ///cmd?
    /*
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
    */
}
