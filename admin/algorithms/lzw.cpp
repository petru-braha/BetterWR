/*#include <iostream>
#include <cstring>
#include "lzw.h"
#define MAX 300

///build
///future patch: a way longer input paramenter!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const char separator[MAX] = "*:is_indexed_at_the_number:*";

dictionary::dictionary()
{
    this->temporary_codes = fopen(path_file_codes, "wb");
    if(temporary_codes == nullptr)
        std::cout << "error - lzw: failed to initialise codes.\n";
    this->index = 256;

    for(unsigned long long i=0; i < this->index; i++)
    {
        char* ascii_character = new char{i};
        fprintf(this->temporary_codes, "%s%s%llu\n" , ascii_character, separator, i);
        delete ascii_character;
    }
}

void dictionary::add(char sequence[])
{
    fprintf(this->temporary_codes, "%s%s%llu\n", sequence, separator, this->index);
}

bool dictionary::exist_string(char sequence[]) //normal sized string
{
    char element[MAX]={0};
    fscanf(this->temporary_codes, "%s", element);
    for(size_t i=0; i < strlen(sequence); i++) //we treat the case where string's size is maximum
        if(sequence[i] != element[i])
            return false;
    return true;
}

ull convert_char(char* nr)
{
	ull p = 1, index = 0, result = 0;
	while (nr[index])
		index++;
	index--;
	while (index)
	{
		result = result + (nr[index] - '0') * p;
		p *= 10;
		index--;
	}

	if (nr[index] == '-')
		return -1 * result;
	return result + (nr[index] - '0') * p;
}

bool dictionary::exist_nr(ull value)
{
    char element[MAX]={0};
    while(strstr(element, separator) == nullptr)
        fscanf(this->temporary_codes, "%s", element);

    strcpy(element, strstr(element, separator));
    strcpy(element, element + strlen(separator));
    if(strstr(element, "\n"))
    {
        size_t index_nl = strstr(element, "\n");
        element[index_nl] = '\0';
        rewind(this->temporary_codes);
        if(value == convert_char(element))
            return true;
    }
    else
    {
        char continue_element[MAX] = {0};
        fscanf(this->temporary_codes, "%s", continue_element);
        strcat(element, continue_element);
        if(strstr(element, "\n") == 0)
        {
            std::cout << "error - lzw: failed to check if the code exists.\n";
            return false;
        }

        element[strstr(element, "\n")] = '\0';
        rewind(this->temporary_codes);
        if(value == convert_char(element))
            return true;
    }

    return false;
}

dictionary::~dictionary()
{
    fclose(this->temporary_codes);
    if(remove(path_file_codes))
        std::cout << "error - lzw: failed to delete codes.\n";
}

int array_len(int a[], int size) {
    int i = 0;
    while (i < size && a[i])
        i++;
    return i;
}

///compress
void build_encoded(dictionary D, char s[] ,int *encoded_text) // append code of to the pointer
{
    if (strlen(s) == 1)
        encoded_text[array_len(encoded_text, MAX)] = s[0];
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

// present patch: make the alg work with big data
unsigned int* lzw_encode_string(char input[])
{
//    - temp_before_LASTbuild mereu trebuie sa intre in output la codare
//    - current <- ultima litera a cuvantului adaugat in dic
//    - i -> current

    dictionary D;
    unsigned int* encoded_text = new unsigned int[MAX]{ 0 };
    char temp[MAX] = {0}, temp_before_LASTbuild[MAX], current;
    int ASCII_value = 256, i = 0;

    //build_variables
    current = input[i];
    temp[strlen(temp)] = current;

    //next?
    i++;
    while (i < strlen(input))
    {
        while (is_in_dictionary(temp) && strlen(temp) > 1)
        {
            strcpy(temp_before_LASTbuild, temp);
            if (i + 1 != strlen(inputs))
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

    delete D;
    return encoded_text;
}

///decompress
void build_decoded(char s[], char text[])
{
    strcat(text, s);
}

char* lzw_decode_string(int* input)///argumentul va fi un FILE*
{
    dictionary D;
    char* decoded_text = new char[MAX]{0};
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
    delete D;
    return decoded_text;
}
*/
