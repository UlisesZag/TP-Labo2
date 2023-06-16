#ifndef _UTILS_H_
#define _UTILS_H_

void string_changechar(char str[], int largo, char reemplazado, char reemplazante);

void string_toupper(char str[], int largo);

void string_tolower(char str[], int largo);

void get_date_string(char str[], char separator);

float scan_num_range(char prompt[], float minimo, float maximo);

void set_text_color(int color);

#endif // _UTILS_H_
