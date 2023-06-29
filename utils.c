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
        if (str[i] == 164) str[i] = 165;
        str[i] = toupper(str[i]); //Caracteres ingles
    }
}

//Toma un string y lo pone en minusculas
void string_tolower(char str[], int largo){
    for (int i = 0; i < largo; i++){
        if (str[i] == '\0') break;
        if (str[i] == 'Ñ') str[i] = 'ñ';
        if (str[i] == 165) str[i] = 164;
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
    char input[32];
    while (1){
        printf("%s", prompt);
        scanf("%31s", input);
        fflush(stdin);

        //Cambia las comas por puntos
        string_changechar(input, strlen(input), ',', '.');

        int valid = 1;
        //Chequea si no ingreso letras o cosas asi
        for (int i = 0; i < strlen(input); i++){
            if ((!isdigit(input[i])) && (input[i] != '.')) valid = 0;
        }
        if (!valid){
            set_text_color(12);
            printf("[!] Valor invalido. Ingrese un numero entero / con coma. [E#2]\n");
            set_text_color(7);
            continue;
        }

        sscanf(input, "%f", &num);

        if (num >= minimo && num <= maximo) break;
        set_text_color(12);
        printf("[!] Valor fuera de rango. Ingrese un valor valido. [E#5]\n");
        set_text_color(7);
    }

    return num;
}

//Funcion que cambia el texto de color
void set_text_color(int color){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
