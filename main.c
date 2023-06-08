#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

#include "utils.h"
#include "structs.h"
#include "binfile.h"
#include "csvfile.h"

#define TABLE_MAX 32


int main(){
    //Menu principal
    char input[32];
    int salir = 0;

    printf("================[ GESTION DE CREDITOS v0.1 ]================\n");
    existe_bin();
    printf("Ingrese \"ayuda\" para obtener una lista de comandos.\n");

    while (!salir){
        printf("\n> ");

        //Lee la opcion
        gets(input);
        fflush(stdin);
        string_tolower(input, strlen(input));
        //Lo divide en comando y argumentos
        char *saveptr = NULL;
        char *comando = NULL;
        char *arg1 = NULL;
        char *arg2 = NULL;
        comando = strtok_r(input, " ", &saveptr);
        arg1 = strtok_r(NULL, " ", &saveptr);
        arg2 = strtok_r(NULL, " ", &saveptr);

        if (strcmp(comando, "nuevodat") == 0){
            crear_creditosdat();
        }
        else if (strcmp(comando, "salir") == 0){
            salir = 1;
        }
        else if (strcmp(comando, "listar") == 0){
            listar_bin(arg1, arg2);
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
            listar_xyz();
        }
        else if (strcmp(comando, "ayuda") == 0){
            printf("\n=====[ COMANDOS ]=====\n");
            printf("Tabla de creditos:\n");
            printf("\t nuevodat: Crear nuevo archivo \"creditos.bin\"\n");
            printf("\t listar: Listar todos los creditos.\n");
            printf("\t bajalogica: Dar de baja a un credito (usuario pasivo).\n");
            printf("\t bajafisica: Borra a un credito de la tabla, y lo escribe en un archivo .xyz por fecha.\n");
            printf("\t listarxyz: Listar un archivo .xyz hecho por bajafisica.\n");
            printf("CSV:\n");
            printf("\t listarcsv: Listar todos los creditos de un csv.\n");
            printf("\t importarcsv: Importar los datos de un CSV a la base creditos.dat.\n");
            printf("Otros:\n");
            printf("\t ayuda: Mostrar lista de comandos.\n");
            printf("\t salir: Salir\n");
        }
        else{
            printf("\nNo se reconoce el comando. Ingrese \"ayuda\" para obtener una lista de comandos.\n");
        }
    }

    return 0;
}
