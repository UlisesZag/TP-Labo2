#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Toma un string y cambia todos los caracteres "reemplazado" por los "reemplazante"
void string_changechar(char str[], int largo, char reemplazado, char reemplazante){
    for (int i = 0; i < largo; i++){
        if (str[i] == reemplazado){
            str[i] = reemplazante;
        }
    }
}

//Toma un string y lo pone en mayusculas
void string_toupper(char str[], int largo){
    for (int i = 0; i < largo; i++){
        if (str[i] == '\0') break;
        str[i] = toupper(str[i]);
    }
}

//Toma un string y lo pone en minusculas
void string_tolower(char str[], int largo){
    for (int i = 0; i < largo; i++){
        if (str[i] == '\0') break;
        str[i] = tolower(str[i]);
    }
}
