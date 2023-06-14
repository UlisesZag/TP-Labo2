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

void str_to_fechames(struct fecha_mes * date, char * str_date){
    char meses[12][4] = {"ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};
    int dias_meses[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //No uso sscanf porque puede ser que el usuario lo ingrese mal
    //Asi que tengo que usar strtok
    char * saveptr;
    char * dia = strtok_r(str_date, "/", &saveptr);
    char * mes = strtok_r(NULL, "/", &saveptr);
    char * anio = strtok_r(NULL, "/", &saveptr);

    int mes_num;
    int dia_num;
    int anio_num;
    char mes_str[4];

    if (mes != NULL)
        sscanf(mes, "%d", &mes_num);

    //Convierte strings a numeros
    if (dia != NULL) sscanf(dia, "%d", &dia_num); else dia_num = 0;
    if (anio != NULL) sscanf(anio, "%d", &anio_num); else anio_num = 0;
    if (mes != NULL && mes_num >= 1 && mes_num <= 12) strcpy(mes_str, meses[mes_num-1]); else strcpy(mes_str, "---");

    //Validaciones
    if (dia_num <= 0 || dia_num > dias_meses[mes_num-1]) dia_num = 0;
    if (anio_num <= 0) anio_num = 0;

    //Finalmente los pone en el struct
    date->dia = dia_num;
    strcpy(date->mes, mes_str);
    date->anio = anio_num;
}

//Funcion que cambia el texto de color
void set_text_color(int color){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
