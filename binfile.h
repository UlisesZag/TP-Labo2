#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TABLE_MAX 32

//Funcion que saca el tamaño del archivo
//SIEMPRE se deberia ejecutar al principio de la funcion, y no mientras se esta moviendo pArchivo
int tamano_bin(FILE * pArchivo){
    int pos;
    fseek(pArchivo, 0, SEEK_END);
    pos = ftell(pArchivo);
    return pos;
}

void listar_tabla_creditos(struct credito creditosbin[], int d){
    printf("ORD | APELLIDO  | NOMBRE  | IMPORTE  | TIPO DE CREDITO | FECHA      | CUOTAS | IMPORTE CUOTA | IVA   | TOTAL CUOTA | ACTIVO\n");
        for (int i = 0; i < d; i++){
            printf("%-3d %-12s %-10s %9.2f %17s %3d/%3s/%4d %4d %14.2lf %10.2lf %13.2lf %3d\n",
                    creditosbin[i].orden,
                    creditosbin[i].apellido,
                    creditosbin[i].nombre,
                    creditosbin[i].importe,
                    creditosbin[i].tipo,
                    creditosbin[i].date.dia,
                    creditosbin[i].date.mes,
                    creditosbin[i].date.anio,
                    creditosbin[i].cuotas,
                    creditosbin[i].importe_cuota,
                    creditosbin[i].iva,
                    creditosbin[i].total_cuota,
                    creditosbin[i].activo);
        }
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

    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);

    if (pArchivo != NULL){
        //Calcula el tamaño del archivo. Sale si el archivo esta vacio.
        int fsize = tamano_bin(pArchivo);
        if (fsize == 0){
            printf("El archivo \"creditos.dat\" esta vacio.\n");
            fclose(pArchivo);
            return;
        }

        int registros = fsize/sizeof(struct credito);
        printf("Cantidad de registros: %d\n", registros);

        //Lee el archivo
        fseek(pArchivo, 0, SEEK_SET);
        fread(&creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);

        listar_tabla_creditos(creditosbin, registros);

        fclose(pArchivo);
    }
}

///BAJAS
void baja_logica(){
    if (!existe_bin()) return;

    FILE *pArchivo;
    pArchivo = fopen("creditos.dat", "rb");

    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);

    if (pArchivo != NULL){
        //Calcula el tamaño del archivo. Sale si el archivo esta vacio.
        int fsize = tamano_bin(pArchivo);
        if (fsize == 0){
            printf("El archivo \"creditos.dat\" esta vacio.\n");
            fclose(pArchivo);
            return;
        }

        //Lee el archivo
        fseek(pArchivo, 0, SEEK_SET);
        fread(&creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);

        pArchivo = fopen("creditos.dat", "wb");

        int orden;
        printf("Ingrese el numero de orden a dar la baja logica:\nORDEN>");
        scanf("%d", &orden);

        creditosbin[orden-1].activo = 0;

        fwrite(creditosbin, sizeof(struct credito_csv)*TABLE_MAX, 1, pArchivo);

        printf("Baja logica en orden %d realizado con exito.\n", orden);

        fclose(pArchivo);
    }
}
