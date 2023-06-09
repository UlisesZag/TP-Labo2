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
