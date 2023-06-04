#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Funcion que crea un archivo creditos.dat vacio.
void crear_creditosdat(){
    FILE * pArchivo;

    //Primero intenta abrirlo para ver si ya existe.
    pArchivo = fopen("creditos.dat", "rb");

    if (pArchivo != NULL) {
        //En este caso existe, le pregunta al usuario si quiere crear un archivo en blanco
        printf("Ya existe un archivo \"creditos.dat\". Desea sobreescribirlo con un archivo en blanco?\n[S/N]>");

        char opcion;
        scanf("%c", &opcion);
        fflush(stdin);
        opcion = toupper(opcion);

        if (opcion == 'S'){
            //Crea el archivo vacio
            pArchivo = fopen("creditos.dat", "wb");
            fclose(pArchivo);
            printf("Archivo \"creditos.dat\" vacio creado.\n");
        }
    }
    else{
        //Crea el archivo vacio
        pArchivo = fopen("creditos.dat", "wb");
        fclose(pArchivo);
        printf("Archivo \"creditos.dat\" vacio creado.\n");
    }
}

//Funcion que verifica la existencia de creditos.bin
int existe_bin(){
    FILE *pArchivo;
    pArchivo = fopen("creditos.dat", "rb");

    if (pArchivo != NULL) return 1;
    else{
        fclose(pArchivo);
        printf("[!] No existe un archivo \"creditos.bin\". Cree uno con \"nuevodat\" o importe un CSV con \"importar\".\n\n");
        return 0;
    }
}
