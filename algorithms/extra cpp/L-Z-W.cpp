#include <iostream>
#include <cstring>
#define MAX 300
using namespace std;

///pentru un moment voi memora valorile in aceste variabile, dar de fapt continutul lor va fi memorat in fisiere, deci nu va exista o limita de memorie decat cea a calculatorului
char text[MAX]="WYS*WYGWYS*WYSWYSYSYSWYSYWSYWSYWSYYSWWYS";
int encoded_text[MAX];
    int Len(int a[])///functioneaza doar pentru vectori declarati global !!!!
    {
        int i=0;
        while(a[i])
            i++;
        return i;
    }

struct line{
    char stored_value[MAX];
    int new_value;//ASCII incepand de la 256 inclusiv
};
struct dictionary{
    int index;//if == 0 then empty
    line element[MAX];
} D;
void initialize_dictionary()
{
    while(D.index<256)
    {
        D.element[D.index].new_value=D.index;
        D.element[D.index].stored_value[0]=(char)D.index;
        D.index++;
    }
}
bool is_in_dictionary(char s[])
{
    for(int i=0;i<D.index;i++)
        if(strcmp(D.element[i].stored_value, s)==0)
            return 1;
    return 0;
}
void add_TOdictionary(char s[], int & ASCII_value)
{
    D.element[D.index].new_value=ASCII_value++;
    strcpy(D.element[D.index++].stored_value, s);
}

void build_encoded(char s[])
{
    if(strlen(s)==1)
        encoded_text[Len(encoded_text)] = s[0];
    else
    {
        for(int i=0;i<D.index;i++)
            if(strcmp(D.element[i].stored_value, s)==0)
            {
                encoded_text[Len(encoded_text)] = D.element[i].new_value;
                break;
            }
    }
}
///FUNCTII PENTRU DECODIFICARE, RESTUL SUNT PENTRU CODIFICARE SI DICTIONAR
    bool is_in_dictionaryENCODED(int next)
    {
        if(next>D.index-1)
            return 0;
        return 1;
    }

    void build_decoded(char s[])
    {
        strcat(text, s);
        text[strlen(text)]='\0';
    }



void lzw_encode(char input[]);
void lzw_decode(int input[]);




int main()///AICI AFISEZ DIFERENTELE INTRE TEXT CODAT SI ORIGINAL dupa cele 2 operatii
{
    for(int i=0;i<strlen(text);i++)
        cout<<(int)text[i]<<' ';
    cout<<'\n';
    lzw_encode(text);
    int n=Len(encoded_text);
    for(int i=0;i<n;i++)
        cout<<encoded_text[i]<<' ';
    cout<<'\n'<<"Codificarea a avut succes\n\n"<<text;//verific ca stergerea a avut succes prin a afisa din nou text

    cout<<"Textul codificat se va restabili in randul de mai jos\n";
    for(int i=0;i<n;i++)
        cout<<encoded_text[i]<<' ';
    cout<<'\n';
    lzw_decode(encoded_text);
    for(int i=0;i<strlen(text);i++)
        cout<<(int)text[i]<<' ';
    cout<<'\n';

    return 0;
}

void lzw_encode(char input[])
/**
- temp_before_LASTbuild mereu trebuie sa intre in output la codare
- current <- ultima litera a cuvantului adaugat in dic
- i -> current
*/
{
    char temp[MAX], temp_before_LASTbuild[MAX], current;
    int ASCII_value=256, i=0;

    //initialise_temp
    memset(temp, 0, sizeof temp);
    //build_variables
    current=input[i];
    temp[strlen(temp)]=current;
    temp[strlen(temp)]='\0';
    //next?
    i++;
    while(i<strlen(input))
    {
        while(is_in_dictionary(temp) && strlen(temp)>1)
        {
            strcpy(temp_before_LASTbuild, temp);
            if(i+1!=strlen(input))
            {
                i++;
                //build_variables
                current=input[i];
                temp[strlen(temp)]=current;
                temp[strlen(temp)]='\0';
            }
            else
            {
                build_encoded(temp_before_LASTbuild);
                return;
            }
        }

        if(!(is_in_dictionary(temp)) && strlen(temp)>1)
        {
            build_encoded(temp_before_LASTbuild);
            add_TOdictionary(temp, ASCII_value);
            //initialise_temp
            memset(temp, 0, sizeof temp);
            //build_variables
            current=input[i];
            temp[strlen(temp)]=current;
            temp[strlen(temp)]='\0';
            //next?
            i++;
        }

        strcpy(temp_before_LASTbuild, temp);
        //build_variables
        current=input[i];
        temp[strlen(temp)]=current;
        temp[strlen(temp)]='\0';

        ///ultimul caracter
        if(i==strlen(input))
            build_encoded(temp_before_LASTbuild);
    }
    //sterg datele
    memset(input, 0, sizeof input);
    for(i=0; i<D.index; i++)
    {
        memset(D.element[i].stored_value, 0, MAX);
        D.element[i].new_value=0;
    }
    D.index=0;
}

void lzw_decode(int input[])
{
    initialize_dictionary();
    int current=input[0], next, n=Len(input)-1;
    char temp[MAX], previous_temp[MAX];
    strcpy(temp, D.element[current].stored_value);

    build_decoded(temp);
    memset(previous_temp, 0, sizeof previous_temp);
    previous_temp[strlen(previous_temp)]=temp[0];

    for(int i=0; i<n; i++)
    {
        next=input[i+1];
        if (!(is_in_dictionaryENCODED(next)))   //caz rar:urmatorul numar nu e in dictionar => inseamna ca e de fapt numarul de dinainte duplicat
        {
            strcpy(temp, D.element[current].stored_value);
            strcat(temp, previous_temp);
        }
        else
            strcpy(temp, D.element[next].stored_value);

        build_decoded(temp);
        memset(previous_temp, 0, sizeof previous_temp);
        previous_temp[strlen(previous_temp)]=temp[0];

        strcat(D.element[D.index].stored_value, D.element[current].stored_value);//se construieste dictionarul cu fiecare nou numar
        strcat(D.element[D.index].stored_value, previous_temp);
        D.element[D.index].stored_value[strlen(D.element[D.index].stored_value)]='\0';
        D.index++;
        current=next;
    }

    //sterg datele
    n++;
    for(int i=0;i<n;i++)
        input[i]=0;

    for(int i=0; i<D.index; i++)
    {
        memset(D.element[i].stored_value, 0, MAX);
        D.element[i].new_value=0;
    }
    D.index=0;
}
/**
TO DO:
1. de facut extra teste pe algoritm
2. de implementat pe fisiere
*/