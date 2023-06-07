#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

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

//agarra un string y devuelve la fecha
void get_date_string(char str[], char separator){
    time_t t = time(NULL);
    struct tm tiempo = *localtime(&t);

    sprintf(str, "%02d%c%02d%c%04d", tiempo.tm_mday, separator, tiempo.tm_mon, separator, 1900+tiempo.tm_year); //String a devolver
}

/*
//Copiado de stackoverflow, solamente esta para hacer mas grande la consola.
struct SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
};
void adjust_window_size(short width, short height){
    struct SMALL_RECT test;

    HANDLE hStdout;
    COORD coord;
    BOOL ok;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = width;
    coord.Y = height;
    ok = SetConsoleScreenBufferSize(hStdout, coord);

    test.Left = 0;
    test.Top = 0;
    test.Right = coord.X-1;
    test.Bottom = coord.Y-1;

    //SetConsoleWindowInfo(hStdout, ok, &test);

} //end adjustWindowSize

*/
