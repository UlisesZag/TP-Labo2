/*
UNIVERSIDAD NACIONAL DE SAN MARTIN | LABORATORIO DE COMPUTACION II | TRABAJO PRACTICO FINAL, Primer cuatrimestre, 2023
Autor: ULISES ZAGARE; Fecha de entrega del TP: 20/6/2023;
Archivos:
CODIGO FUENTE:
    main.c
    binfile.c
    binfile.h
    csvfile.c
    csvfile.h
    structs.h
    structfuncs.c
    structfuncs.h
    utils.c
    utils.h
    defines.h
CSVs:
    prestamos.csv
ARCHIVOS DE PROYECTO:
    TP_Final.cbp
    TP_Final.depend
    TP_Final.layout
DOCUMENTACION
    docs/Trabajo pr�ctico final  LABO II 1er C - 2023.pdf (trabajo practico)
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

#include "structs.h"
#include "utils.h"
#include "binfile.h"
#include "csvfile.h"
#include "defines.h"


int main(){
    //Menu principal
    char input[65];
    int salir = 0;

    set_text_color(11);
    printf("================================== [ GESTION DE CREDITOS v0.1 ] ==================================\n");
    set_text_color(7);
    existe_bin();
    printf("Ingrese \"ayuda\" para obtener una lista de comandos.\n");

    while (!salir){
        printf("\n> ");
        strcpy(input, "");


        //Lee la opcion
        scanf("%64[^\n]", input);
        fflush(stdin);
        string_tolower(input, strlen(input));
        //Lo divide en comando y argumentos
        char *saveptr = NULL;
        char *comando = NULL;
        char *arg1 = NULL;
        char *arg2 = NULL;
        char *arg3 = NULL;
        comando = strtok_r(input, " ", &saveptr);
        arg1 = strtok_r(NULL, " ", &saveptr);
        arg2 = strtok_r(NULL, " ", &saveptr);
        arg3 = strtok_r(NULL, " ", &saveptr);

        if (comando != NULL){
            if (strcmp(comando, "nuevodat") == 0){
                crear_creditosdat();
            }
            else if (strcmp(comando, "salir") == 0){
                salir = 1;
            }
            else if (strcmp(comando, "listar") == 0){
                listar_bin(arg1, arg2, arg3);
            }
            else if (strcmp(comando, "listarcsv") == 0){
                listar_csv(arg1);
            }
            else if (strcmp(comando, "importarcsv") == 0){
                importar_csv(arg1);
            }
            else if (strcmp(comando, "bajalogica") == 0){
                baja_logica(arg1);
            }
            else if (strcmp(comando, "bajafisica") == 0){
                baja_fisica(arg1);
            }
            else if (strcmp(comando, "listarxyz") == 0){
                listar_xyz(arg1);
            }
            else if (strcmp(comando, "alta") == 0){
                alta(arg1);
            }
            else if (strcmp(comando, "modificar") == 0){
                modificar(arg1, arg2, arg3);
            }
            else if (strcmp(comando, "buscar") == 0){
                buscar(arg1, arg2, arg3);
            }
            else if (strcmp(comando, "dfjk") == 0){
                printf("osu!mania lol.\n");
            }
            else if (strcmp(comando, "ayuda") == 0){
                set_text_color(11);
                printf("\n===== [ COMANDOS ] =====\n");
                set_text_color(7);

                printf(
                       "- Tabla de creditos: -------------------------------------------------------------------------------------\n"
                       "\t - nuevodat: Crear nuevo archivo \"creditos.bin\"\n"
                       "\t - listar [opcion][tipo/fechas]: Listar todos los creditos.\n"
                       "\t    [opcion]: El filtro de listado. \n"
                       "\t        - Si esta vacio muestra todos los creditos\n"
                       "\t        - Si es \"activos\" muestra solo los activos\n"
                       "\t        - Si es \"tipo\" muestra solo los de un tipo de credito especificado por tipo.\n"
                       "\t        - Si es \"fecha\" muestra solo los creditos entre un rango de fechas.\n"
                       "\t    [tipo/fechas]:   El tipo de credito para el filtro por tipo, o las fechas para el filtro por fechas.\n"
                       "\t        << SOLO PARA TIPO >>\n"
                       "\t        - Si es \"garantia\" muestra solo los del tipo \"CON G    ARANTIA\"\n"
                       "\t        - Si es \"firma\" muestra solo los del tipo \"A SOLA FIRMA\"\n"
                       "\t        << SOLO PARA FECHA >>\n"
                       "\t        - Las fechas deben ser en formato dia/mes/a%co EN NUMEROS.\n"
                       "\t - modificar [orden][opcion][tipo/importe]: Modifica un campo de un credito por numero de orden.\n"
                       "\t    [orden]:  El numero de orden del credito a modificar.\n"
                       "\t    [opcion]: El campo a modificar:\n"
                       "\t        - Si es \"tipo\" modifica el tipo de credito.\n"
                       "\t        - Si es \"importe\" modifica el importe del credito\n"
                       "\t    [tipo/importe]: El tipo de credito o el importe a asignar al credito.\n"
                       "\t        << SOLO PARA TIPO >>\n"
                       "\t        - Si es \"garantia\" modifica el tipo a \"CON GARANTIA\".\n"
                       "\t        - Si es \"firma\" modifica el tipo a \"A SOLA FIRMA\".\n"
                       "\t - buscar [tipo][orden/apellido]: Busca un credito por numero de orden o apellido, e imprime sus datos.\n"
                       "\t    [tipo]: El tipo de dato a buscar:\n"
                       "\t        - Si es \"orden\" busca por el numero de orden\n"
                       "\t        - Si es \"apellido\" busca por apellido\n"
                       "\t    [orden/apellido]: El numero de orden o el apellido del credito a buscar.\n"
                       "\t - bajalogica [orden]: Dar de baja a un credito (usuario pasivo).\n"
                       "\t    [orden]:  El numero de orden del credito a dar de baja\n"
                       "\t - bajafisica [orden]: Borra a un credito de la tabla, y lo escribe en un archivo .xyz por fecha.\n"
                       "\t    [orden]:  El numero de orden del credito a dar de baja\n"
                       "\n"
                       "- CSV: ---------------------------------------------------------------------------------------------------\n"
                       "\t - listarcsv [ruta]: Listar todos los creditos de un csv.\n"
                       "\t    [ruta]: La ruta del archivo .csv a mostrar.\n"
                       "\t - importarcsv [ruta]: Importar los datos de un CSV a la base creditos.dat.\n"
                       "\t    [ruta]: La ruta del archivo .csv a importar como \"creditos.dat\".\n"
                       "\t - listarxyz [ruta]: Listar un archivo .xyz hecho por bajafisica.\n"
                       "\t    [ruta]: La ruta del archivo .xyz a mostrar.\n"
                       "\n"
                       "- Otros: -------------------------------------------------------------------------------------------------\n"
                       "\t - ayuda: Mostrar lista de comandos.\n"
                       "\t - salir: Salir\n",
                       164);
            }
            else{
                printf("No se reconoce el comando. Ingrese \"ayuda\" para obtener una lista de comandos.\n");
            }
        }
    }

    return 0;
}
