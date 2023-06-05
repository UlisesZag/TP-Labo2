#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
    printf("Ingrese \"ayuda\" para obtener una lista de comandos.\n\n");

    while (!salir){
        printf(">");

        //Lee la opcion
        scanf("%s", input);
        fflush(stdin);

        char * comando;
        comando = strtok(input, " ");

        if (strcmp(comando, "nuevodat") == 0){
            crear_creditosdat();
        }
        else if (strcmp(comando, "salir") == 0){
            salir = 1;
        }
        else if (strcmp(comando, "listar") == 0){
            listar_bin();
        }
        else if (strcmp(comando, "listarcsv") == 0){
            listar_csv();
        }
        else if (strcmp(comando, "importarcsv") == 0){
            importar_csv();
        }
        else if (strcmp(comando, "ayuda") == 0){
            printf("\n=====[ COMANDOS ]=====\n");
            printf("Base de datos:\n");
            printf("\t nuevodat: Crear nuevo archivo \"creditos.bin\"\n");
            printf("\t listar: Listar todos los creditos.\n");
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
