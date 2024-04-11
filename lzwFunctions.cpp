#pragma warning(disable:4996)

#include <iostream>
#include <cstring>
#include "lzw.h"

using namespace std;

struct dictionary {
    int index;  //if == 0 then empty
    line element[MAX];
} D;

// functie de convertire a sirului citit din fisier intr un vector de valori intregi
void bufferToIntArray(const char* buffer, int bufferSize, int* intArray, int& arraySize) {
    int currentNumber = 0;
    bool inNumber = false;
    int arrayIndex = 0;

    for (int i = 0; i < bufferSize; ++i) {
        char currentChar = buffer[i];

        if (isdigit(currentChar)) {
            currentNumber = currentNumber * 10 + (currentChar - '0');
            inNumber = true;
        }
        else {
            if (inNumber) {
                // adadugam numarul in vector
                intArray[arrayIndex++] = currentNumber;

                // reset pentru urmatorul numar
                currentNumber = 0;
                inNumber = false;
            }
        }
    }

    // daca ultimul caracter face parte dintr un numar, il adaugam in vector
    if (inNumber) {
        intArray[arrayIndex++] = currentNumber;
    }

    // actualizam dimensiunea vectorului
    arraySize = arrayIndex;
}

int Len(int a[], int size) {
    int i = 0;
    while (i < size && a[i])
        i++;
    return i;
}

void initialize_dictionary()
{
    while (D.index < 256)
    {
        D.element[D.index].new_value = D.index;
        D.element[D.index].stored_value[0] = (char)D.index;
        D.index++;
    }
}
bool is_in_dictionary(char s[])
{
    for (int i = 0; i < D.index; i++)
        if (strcmp(D.element[i].stored_value, s) == 0)
            return 1;
    return 0;
}
void add_TOdictionary(char s[], int& ASCII_value)
{
    D.element[D.index].new_value = ASCII_value++;
    strcpy(D.element[D.index++].stored_value, s);
}

void build_encoded(char s[],int *&encoded_text)
{
    if (strlen(s) == 1)
        encoded_text[Len(encoded_text,MAX)] = s[0];
    else
    {
        for (int i = 0; i < D.index; i++)
            if (strcmp(D.element[i].stored_value, s) == 0)
            {
                encoded_text[Len(encoded_text,MAX)] = D.element[i].new_value;
                break;
            }
    }
}
///FUNCTII PENTRU DECODIFICARE, RESTUL SUNT PENTRU CODIFICARE SI DICTIONAR
bool is_in_dictionaryENCODED(int next)
{
    if (next > D.index - 1)
        return 0;
    return 1;
}

void build_decoded(char s[],char text[])
{
    strcat(text, s);
    text[strlen(text)] = '\0';
}

void lzw_encode(char input[], int size, int*& encoded_text)
{
    /*
    - temp_before_LASTbuild mereu trebuie sa intre in output la codare
    - current <- ultima litera a cuvantului adaugat in dic
    - i -> current
    */
    char temp[MAX], temp_before_LASTbuild[MAX], current;
    int ASCII_value = 256, i = 0;

    //initialise_temp
    memset(temp, 0, sizeof temp);
    //build_variables
    current = input[i];
    temp[strlen(temp)] = current;
    temp[strlen(temp)] = '\0';
    //next?
    i++;
    while (i < strlen(input))
    {
        while (is_in_dictionary(temp) && strlen(temp) > 1)
        {
            strcpy(temp_before_LASTbuild, temp);
            if (i + 1 != strlen(input))
            {
                i++;
                //build_variables
                current = input[i];
                temp[strlen(temp)] = current;
                temp[strlen(temp)] = '\0';
            }
            else
            {
                build_encoded(temp_before_LASTbuild,encoded_text);
                return;
            }
        }

        if (!(is_in_dictionary(temp)) && strlen(temp) > 1)
        {
            build_encoded(temp_before_LASTbuild,encoded_text);
            add_TOdictionary(temp, ASCII_value);
            //initialise_temp
            memset(temp, 0, sizeof temp);
            //build_variables
            current = input[i];
            temp[strlen(temp)] = current;
            temp[strlen(temp)] = '\0';
            //next?
            i++;
        }

        strcpy(temp_before_LASTbuild, temp);
        //build_variables
        current = input[i];
        temp[strlen(temp)] = current;
        temp[strlen(temp)] = '\0';

        ///ultimul caracter
        if (i == strlen(input))
            build_encoded(temp_before_LASTbuild,encoded_text);
    }
    //sterg datele
    memset(input, 0, size);
    for (i = 0; i < D.index; i++)
    {
        memset(D.element[i].stored_value, 0, MAX);
        D.element[i].new_value = 0;
    }
    D.index = 0;
}

void lzw_decode(int input[],char*& decoded_text)
{
    initialize_dictionary();
    int current = input[0], next, n = Len(input,MAX) - 1;
    char temp[MAX], previous_temp[MAX];
    strcpy(temp, D.element[current].stored_value);

    build_decoded(temp,decoded_text);
    memset(previous_temp, 0, sizeof previous_temp);
    previous_temp[strlen(previous_temp)] = temp[0];

    for (int i = 0; i < n; i++)
    {
        next = input[i + 1];
        if (!(is_in_dictionaryENCODED(next)))   // caz rar: urmatorul numar nu e in dictionar => inseamna ca e de fapt numarul de dinainte duplicat
        {
            strcpy(temp, D.element[current].stored_value);
            strcat(temp, previous_temp);
        }
        else
            strcpy(temp, D.element[next].stored_value);

        build_decoded(temp,decoded_text);
        memset(previous_temp, 0, sizeof previous_temp);
        previous_temp[strlen(previous_temp)] = temp[0];

        strcat(D.element[D.index].stored_value, D.element[current].stored_value);   //se construieste dictionarul cu fiecare nou numar
        strcat(D.element[D.index].stored_value, previous_temp);
        D.element[D.index].stored_value[strlen(D.element[D.index].stored_value)] = '\0';
        D.index++;
        current = next;
    }

    //sterg datele
    n++;
    for (int i = 0; i < n; i++)
        input[i] = 0;

    for (int i = 0; i < D.index; i++)
    {
        memset(D.element[i].stored_value, 0, MAX);
        D.element[i].new_value = 0;
    }
    D.index = 0;
}
