#ifndef _UTILS_H_
#define _UTILS_H_

void string_changechar(char str[], int largo, char reemplazado, char reemplazante);

void string_toupper(char str[], int largo);

void string_tolower(char str[], int largo);

void get_date_string(char str[], char separator);

float scan_num_range(char prompt[], float minimo, float maximo);

void str_to_fechames(struct fecha_mes * date, char * str_date);

#endif // _UTILS_H_
