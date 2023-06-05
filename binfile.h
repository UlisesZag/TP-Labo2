#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Funcion que saca el tamaño del archivo
//SIEMPRE se deberia ejecutar al principio de la funcion, y no mientras se esta moviendo pArchivo
int tamano_bin(FILE * pArchivo){
    int pos;
    fseek(pArchivo, 0, SEEK_END);
    pos = ftell(pArchivo);
    return pos;
}

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
            printf("Archivo \"creditos.dat\" vacio creado.\n\n");
        }
    }
    else{
        //Crea el archivo vacio
        pArchivo = fopen("creditos.dat", "wb");
        fclose(pArchivo);
        printf("Archivo \"creditos.dat\" vacio creado.\n\n");
    }
}

//Funcion que verifica la existencia de creditos.bin
int existe_bin(){
    FILE *pArchivo;
    pArchivo = fopen("creditos.dat", "rb");

    if (pArchivo != NULL){
        fclose(pArchivo);
        return 1;
    }
    else{
        printf("[!] No existe un archivo \"creditos.bin\". Cree uno con \"nuevodat\" o importe un CSV con \"importar\".\n\n");
        return 0;
    }
}

//Funcion que muestra los archivos de creditos.dat
void listar_bin(){
    if (!existe_bin()) return;

    FILE *pArchivo;
    pArchivo = fopen("creditos.dat", "rb");

    if (pArchivo != NULL){
        //Calcula el tamaño del archivo. Sale si el archivo esta vacio.
        int fsize = tamano_bin(pArchivo);
        if (fsize == 0){
            printf("El archivo \"creditos.dat\" esta vacio.\n");
            fclose(pArchivo);
            return;
        }

        //TODO mostrar un archivo con datos.

        printf("ORDEN | APELLIDO | NOMBRE    | IMPORTE | TIPO DE CREDITO | FECHA     | CUOTAS | IMPORTE CUOTA | IVA | TOTAL CUOTA\n");
    }
}
