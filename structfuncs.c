#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

#include "structfuncs.h"

void inicializar_credito(struct credito c[], int d){
    for (int i = 0; i < d; i++){
        c[i].orden = 0;
        strcpy(c[i].nombre, "");
        strcpy(c[i].apellido, "");
        c[i].importe = 0.0;
        strcpy(c[i].tipo, "");
        c[i].date.dia = 0;
        strcpy(c[i].date.mes, "---");
        c[i].date.anio = 0;
        c[i].cuotas = 0;
        c[i].importe_cuota = 0;
        c[i].iva = 0;
        c[i].total_cuota = 0;
        c[i].activo = 0;
    }
}
void inicializar_creditocsv(struct credito_csv c[], int d){
    for (int i = 0; i < d; i++){
        c[i].orden = 0;
        strcpy(c[i].cliente, "");
        c[i].importe = 0.0;
        strcpy(c[i].tipo, "");
        c[i].date.dia = 0;
        c[i].date.mes = 0;
        c[i].date.anio = 0;
        c[i].cuotas = 0;
        c[i].importe_cuota = 0;
        c[i].iva = 0;
        c[i].total_cuota = 0;
    }
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

void fechames_to_fecha(struct fecha_mes datemes, struct fecha * date){
    date->dia = datemes.dia;
    date->anio = datemes.anio;

    //Convierte el string a numero (NO SWITCH CON STRINGS???!!!?)
    if (strcmp(datemes.mes, "ene") == 0) date->mes = 1;
    if (strcmp(datemes.mes, "feb") == 0) date->mes = 2;
    if (strcmp(datemes.mes, "mar") == 0) date->mes = 3;
    if (strcmp(datemes.mes, "abr") == 0) date->mes = 4;
    if (strcmp(datemes.mes, "may") == 0) date->mes = 5;
    if (strcmp(datemes.mes, "jun") == 0) date->mes = 6;
    if (strcmp(datemes.mes, "jul") == 0) date->mes = 7;
    if (strcmp(datemes.mes, "ago") == 0) date->mes = 8;
    if (strcmp(datemes.mes, "sep") == 0) date->mes = 9;
    if (strcmp(datemes.mes, "oct") == 0) date->mes = 10;
    if (strcmp(datemes.mes, "nov") == 0) date->mes = 11;
    if (strcmp(datemes.mes, "dic") == 0) date->mes = 12;
}

//Funcion que compara 2 fechas y ve cual es antes y despues
//la funcion toma como si todos los años tuviesen 29 dias en febrero, pero no deberia haber ningun problema
int fechacmp(struct fecha date1, struct fecha date2){
    int dias_meses[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //Dias
    int dias1 = date1.dia;
    int dias2 = date2.dia;

    //Meses
    for (int i = 0; i < date1.mes; i++){
        dias1 += dias_meses[i];
    }
    for (int i = 0; i < date2.mes; i++){
        dias2 += dias_meses[i];
    }

    //Años
    dias1 += date1.anio * 366;
    dias2 += date2.anio * 366;

    //Compara
    if (dias1 < dias2) return -1;
    else if (dias1 > dias2) return 1;
    else return 0;
}
