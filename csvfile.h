#include <stdio.h>
#include <stdlib.h>

void listar_txt(){
    char ruta[32];

    printf("Ingrese la ruta del archivo CSV a listar: \n");
    scanf("%s", ruta);
    fflush(stdin);

    //Abre el archivo en solo lectura
    FILE * pArchivo;
    pArchivo = fopen(ruta, "r");

    if (pArchivo == NULL){
        printf("ERROR: El archivo no existe. Verificar ruta ingresada.\n");
    }
    else{

    }
}
