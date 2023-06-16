#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#include "structs.h"
#include "defines.h"

#include "utils.h"

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
        if (str[i] == 'ñ') str[i] = 'Ñ';
        str[i] = toupper(str[i]); //Caracteres ingles
    }
}

//Toma un string y lo pone en minusculas
void string_tolower(char str[], int largo){
    for (int i = 0; i < largo; i++){
        if (str[i] == '\0') break;
        if (str[i] == 'Ñ') str[i] = 'ñ';
        str[i] = tolower(str[i]);
    }
}

//agarra un string y devuelve la fecha
void get_date_string(char str[], char separator){
    time_t t = time(NULL);
    struct tm tiempo = *localtime(&t);

    sprintf(str, "%02d%c%02d%c%04d", tiempo.tm_mday, separator, tiempo.tm_mon, separator, 1900+tiempo.tm_year); //String a devolver
}

//Funcion que solo deja ingresar un numero dentro de un rango.
float scan_num_range(char prompt[], float minimo, float maximo){
    float num;
    while (1){
        printf("%s", prompt);
        scanf("%f", &num);
        fflush(stdin);
        if (num >= minimo && num <= maximo) break;
        printf("[!] Valor fuera de rango. Ingrese un valor valido.\n");
    }

    return num;
}

//Funcion que cambia el texto de color
void set_text_color(int color){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
