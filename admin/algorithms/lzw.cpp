#include <iostream>
#include <cstring>
#include "lzw.h"

const char temp_location[] = "constant files/test files/temp.tar";
const char separator[] = "*:indexed_AT:*";
int array_len(int a[], int sz)
{
    int i = 0;
    while (i < sz && a[i])
        i++;
    return i;
}

void print_number(ull* number, FILE* output)
{
	if (*number <= UCHAR_MAX)
	{
		fwrite(number, sizeof(char), 1, output);
		return;
	}

	if (*number <= USHRT_MAX)
	{
		fwrite(number, sizeof(short), 1, output);
		return;
	}

	if (*number <= ULONG_MAX)
	{
		fwrite(number, sizeof(long), 1, output);
		return;
	}

	fwrite(number, sizeof(ull), 1, output);
}

dictionary::dictionary()
{
    this->temporary_codes = fopen(path_file_codes, "wb");
    if(temporary_codes == nullptr) std::cout << "error - lzw: failed to initialise codes.\n";
    this->index = 256;

    for(ull i=0; i < this->index; i++)
    {
        char* ascii_character = new char{i};
        fprintf(this->temporary_codes, "%c%s", ascii_character, separator);
        print_number(reinterpret_cast<ull*>(ascii_character), this->temporary_codes);
        fputc('\n', this->temporary_codes);
        delete ascii_character;
    }
}

ull convert_char(std::string nr)
{
	ull p = 1, index = 0, result = 0;
	while (nr[index + 1])
		index++;

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

void dictionary::add(std::string sequence)
{
    fprintf(this->temporary_codes, "%s%s", sequence, separator);
    ull* temp = new ull {this->index};
    print_number(temp, this->temporary_codes);
    this->index++;
    fputc('\n', this->temporary_codes);
}

/*
int dictionary::exist_string(std::string sequence)
{
    char element = 0;
    ull encoded_value = 0;

    for(ull i = 0; i < this->index && encoded_value == 0; i++)
    {
        //read uncoded_string
        char str[MAX] = ""; size_t index_str = 0;
        while(strstr(str, separator) == nullptr || index_str < MAX)
        {
            fscanf(this->temporary_codes, "%c", element);
            str[index_str++] = element;
        }

        if(strstr(str, separator) == nullptr)
        {
            size_t index_separator = 0;
            while(element == separator[index_separator] && index_separator < strlen(separator))
            {
                fscanf(this->temporary_codes, "%c", element);
                index_separator++;
            }

            fseek(this->temporary_codes, -index_separator, SEEK_CUR);
            if(index_separator + 1 != strlen(separator))
                return -1; //really bad
        }

        ///uint position
        size_t n = strlen(str);
        if(strstr(str, separator))
            n = strlen(str) - strlen(separator);

        str[n] = '\0';

        ///found
        if(strcmp(str, sequence) == 0)
        {
            uint* number = new uint{0};
            fread(number, sizeof(uint), 1, this->temporary_codes);
            encoded_value= *number; delete number;
        }
    }

    return encoded_value;
}

dictionary::~dictionary()
{
    fclose(this->temporary_codes);
    if(remove(path_file_codes))
        std::cout << "error - lzw: failed to delete codes.\n";
}

void compress_lzw(char* path_output, char* output_name) ///write type of compression, statistics
{

    FILE* file_input = fopen(temp_location, "rb");
    FILE* file_outpt = fopen(strcat(path_output, output_name), "wb");
    //if(file_input == nullptr || file_outpt == nullptr) return;

    dictionary* D = new dictionary;
    char next = 0, current[MAX] = "", to_test[MAX] = ""; to_test[0] = fgetc(file_input);

    while (next != EOF)
    {
        next = fgetc(file_input);
        if (next != EOF)
            current[strlen(current)] = next;

        char temp[MAX]; strcpy(temp, strcat(to_test, current));
        if(D->exist_string(temp) == 0)
            strcat(to_test, current);
        else
        {
            D->add(temp);
            int * last_added = new int{D->index-1};
            fwrite(last_added, sizeof(int), 1, file_outpt);
            strcpy(to_test, current); delete last_added;
        }
        memset(current, 0, sizeof(current));
    }

    int* last_added = new int{D->index-1};
    fwrite(last_added, sizeof(int), 1, file_outpt);
    delete last_added; delete D; fclose(file_input); fclose(file_outpt);
}

*void decompress_lzw(char* path_input, char* path_output, char* output_name);
{
    FILE* file_input = fopen(path_input, "rb");
    FILE* file_outpt = fopen(strcat(path_output, output_name), "wb");
    dictionary* D = new dictionary();

    char next = fgetc(file_input);
    while(next != EOF)
    {
        next = fgetc(file_input);
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
}
*/
