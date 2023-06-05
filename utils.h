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
