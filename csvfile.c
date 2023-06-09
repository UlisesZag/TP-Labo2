#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

#include "structs.h"
#include "structfuncs.h"
#include "utils.h"

#include "csvfile.h"

#define TABLE_MAX 32

//Lista un csv que ingrese el usuario
void listar_csv(char * arg1){
    char ruta[32];
    struct credito_csv creditos[TABLE_MAX];
    FILE * pArchivo;

    //Si ARG1 es ingresado, lo usa como ruta de csv.
    if (arg1 == NULL){
        printf("Ingrese la ruta del archivo CSV a listar: \nRUTA>");
        scanf("%32[^\n]", ruta);
        fflush(stdin);
    }
    else{
        strcpy(ruta, arg1);
    }

    //Abre el archivo en solo lectura
    pArchivo = fopen(ruta, "r");

    if (pArchivo == NULL){
        printf("ERROR: El archivo no existe. Verificar ruta ingresada.\n");
    }
    else{
        //Lee el csv por lineas
        char linea[2048];
        int pos = 0;

        printf("Ord  Nombre y apellido  Importe    Tipo        Fecha        Cuotas  Imp. Cuota  IVA     Total Cuota\n");

        fgets(linea, 2048, pArchivo);
        fgets(linea, 2048, pArchivo);//Lee la primera linea para pasar directamente a la segunda.
        while (!feof(pArchivo)){
            string_changechar(linea, 2048, ',', '.'); //Cambia las comas por puntos para que sscanf parsee bien.
            sscanf(linea, "%d;%32[^;];%d;%32[^;];%d;%d;%d;%d;%lf;%lf;%lf\n",
                    &creditos[pos].orden,
                    creditos[pos].cliente,
                    &creditos[pos].importe,
                    creditos[pos].tipo,
                    &creditos[pos].date.dia,
                    &creditos[pos].date.mes,
                    &creditos[pos].date.anio,
                    &creditos[pos].cuotas,
                    &creditos[pos].importe_cuota,
                    &creditos[pos].iva,
                    &creditos[pos].total_cuota);
            printf("%-4d %-19s %9d %8s   %02d/%02d/%4d %6d %10.2lf %8.2lf %8.2lf\n",
                    creditos[pos].orden,
                    creditos[pos].cliente,
                    creditos[pos].importe,
                    creditos[pos].tipo,
                    creditos[pos].date.dia,
                    creditos[pos].date.mes,
                    creditos[pos].date.anio,
                    creditos[pos].cuotas,
                    creditos[pos].importe_cuota,
                    creditos[pos].iva,
                    creditos[pos].total_cuota);
            pos++;
            fgets(linea, 1024, pArchivo);
        }
    }

    fclose(pArchivo);
}

//Convertir un CSV a creditos.dat
void importar_csv(char *arg1){
    char meses[12][4] = {"ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};
    char ruta[32];
    struct credito_csv creditoscsv[TABLE_MAX];
    inicializar_creditocsv(creditoscsv, TABLE_MAX);
    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);
    FILE * pArchivoCsv;
    FILE * pArchivoBin;

    //Si ARG1 es ingresado, lo usa como ruta de archivo csv
    if (arg1 == NULL){
        printf("Ingrese la ruta del archivo CSV a importar como creditos.dat: \nRUTA>");
        scanf("%32[^\n]", ruta);
        fflush(stdin);
    }
    else{
        strcpy(ruta, arg1);
    }

    //Abre el archivo en solo lectura
    pArchivoCsv = fopen(ruta, "r");

    if (pArchivoCsv == NULL){
        printf("ERROR: El archivo no existe. Verificar ruta ingresada.\n");
    }
    else{
        //Antes de nada verifica si creditos.dat existe, si es asi le preguna al usuario si quiere reescribir,
        pArchivoBin = fopen("creditos.dat", "rb");
        if (pArchivoBin != NULL) {
            //En este caso existe, le pregunta al usuario si quiere crear un archivo en blanco
            printf("Ya existe un archivo \"creditos.dat\". Desea sobreescribirlo con los datos del CSV?\n[S/N]>");

            char opcion;
            scanf("%c", &opcion);
            fflush(stdin);
            opcion = toupper(opcion);

            //Si no dice "S" cancela todo.
            if (opcion != 'S'){
                fclose(pArchivoBin);
                fclose(pArchivoCsv);
                return;
            }
        }


        //Lo vuelve a abrir para escritura
        fclose(pArchivoBin);
        pArchivoBin = fopen("creditos.dat", "wb");

        //Lee el csv por lineas
        char linea[1024];
        int pos = 0;

        fgets(linea, 1024, pArchivoCsv);
        fgets(linea, 1024, pArchivoCsv);//Lee la primera linea para pasar directamente a la segunda.
        while (!feof(pArchivoCsv)){
            string_changechar(linea, 2048, ',', '.'); //Cambia las comas por puntos para que sscanf parsee bien.
            sscanf(linea, "%d;%32[^;];%d;%32[^;];%d;%d;%d;%d;%lf;%lf;%lf;\n",
                    &creditoscsv[pos].orden,
                    creditoscsv[pos].cliente,
                    &creditoscsv[pos].importe,
                    creditoscsv[pos].tipo,
                    &creditoscsv[pos].date.dia,
                    &creditoscsv[pos].date.mes,
                    &creditoscsv[pos].date.anio,
                    &creditoscsv[pos].cuotas,
                    &creditoscsv[pos].importe_cuota,
                    &creditoscsv[pos].iva,
                    &creditoscsv[pos].total_cuota);
            pos++;
            fgets(linea, 1024, pArchivoCsv);
        }
        //Convierte la tabla de CSV a tabla de creditos.dat
        for (int i = 0; i < pos; i++){
            //Datos que se pueden pasar de una
            creditosbin[i].orden = creditoscsv[i].orden;
            creditosbin[i].importe = creditoscsv[i].importe;
            creditosbin[i].date.dia = creditoscsv[i].date.dia;
            strcpy(creditosbin[i].date.mes, meses[creditoscsv[i].date.mes-1]); //Cambia el numero por el mes en minusculas
            creditosbin[i].date.anio = creditoscsv[i].date.anio;
            creditosbin[i].cuotas = creditoscsv[i].cuotas;
            creditosbin[i].importe_cuota = creditoscsv[i].importe_cuota;
            creditosbin[i].iva = creditoscsv[i].iva;
            creditosbin[i].total_cuota = creditoscsv[i].total_cuota;
            creditosbin[i].activo = 1;

            //Nombre y apellido
            char cliente[32];
            char * token;
            strcpy(cliente, creditoscsv[i].cliente);//Separa en nombre y apellido con strtok
            token = strtok(cliente, " ");
            strcpy(creditosbin[i].nombre, token); //Lo primero que hay en TOKEN es el nombre

            //El apellido lo pongo en otro string porque hay que ponerlo en mayusculas
            char apellido[32];
            token = strtok(NULL, ""); //Luego concatena lo que queda de string como apellido
            strcpy(apellido, token);
            string_toupper(apellido, strlen(apellido));
            strcpy(creditosbin[i].apellido, apellido); //Lo que queda en TOKEN es el apellido

            //Lo mismo con el tipo de credito.
            char tipo_credito[32];
            strcpy(tipo_credito, creditoscsv[i].tipo);
            string_toupper(tipo_credito, strlen(tipo_credito));
            strcpy(creditosbin[i].tipo, tipo_credito);
        }

        fwrite(creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivoBin);
        fclose(pArchivoBin);
        printf("Conversion de \"%s\" a \"creditos.dat\" exitosa (%d creditos cargados).\n", ruta, pos);
    }

    fclose(pArchivoCsv);
}

//Lista el archivo XYZ
void listar_xyz(){
    char ruta[32];
    FILE * pArchivo;

    printf("Ingrese la ruta del archivo XYZ a listar: \nRUTA>");
    scanf("%s", ruta);
    fflush(stdin);

    //Abre el archivo en solo lectura
    pArchivo = fopen(ruta, "r");

    if (pArchivo == NULL){
        printf("ERROR: El archivo no existe. Verificar ruta ingresada.\n");
    }
    else{
        char linea[2048];
        fgets(linea, 2048, pArchivo);
        while (!feof(pArchivo)){
            printf("%s", linea);
            fgets(linea, 2048, pArchivo);
        }
    }
}
