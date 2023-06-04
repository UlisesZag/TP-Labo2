#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "binfile.h"
#include "structs.h"
#include "csvfile.h"


int main(){
    struct credito creditos[64]; //Toda la tabla de creditos.

    //Menu principal
    char input[32];
    int salir = 0;

    printf("================ GESTION DE CREDITOS v0.1 ================\n");
    existe_bin();
    printf("Ingrese \"ayuda\" para obtener una lista de comandos.\n\n");

    while (!salir){
        printf(">");

        //Lee la opcion
        scanf("%s", input);
        fflush(stdin);
        //input = toupper(opcion);

        char * comando;
        comando = strtok(input, " ");

        if (strcmp(comando, "nuevodat") == 0){
            crear_creditosdat();
        }
        else if (strcmp(comando, "salir") == 0){
            salir = 1;
        }
        else if (strcmp(comando, "ayuda") == 0){
            printf("\nCOMANDOS:\n");
            printf("\t nuevodat: Crear nuevo archivo \"creditos.bin\"\n");
            printf("\t ayuda: Mostrar lista de comandos.\n");
            printf("\t salir: Salir\n");
        }
        else{
            printf("\nNo se reconoce el comando. Ingrese \"ayuda\" para obtener una lista de comandos.\n");
        }
    }

    return 0;
}
