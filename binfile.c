#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "structs.h"
#include "structfuncs.h"
#include "utils.h"
#include "defines.h"

#include "binfile.h"

//Funcion que saca el tamaño del archivo
//SIEMPRE se deberia ejecutar al principio de la funcion, y no mientras se esta moviendo pArchivo
int tamano_bin(FILE * pArchivo){
    int pos;
    fseek(pArchivo, 0, SEEK_END);
    pos = ftell(pArchivo);
    return pos;
}

//Funcion que muestra la tabla de creditos, con filtros segun opcion y "tipo"
void listar_tabla_creditos(struct credito creditosbin[], int d, int opcion, char tipo[], struct fecha fecha1, struct fecha fecha2){
    set_text_color(15);
    printf("ORD | APELLIDO  | NOMBRE  | IMPORTE  | TIPO DE CREDITO | FECHA      | CUOTAS | IMPORTE CUOTA | IVA   | TOTAL CUOTA | ACT\n");
    set_text_color(7);

    //Ve desde donde la tabla esta vacia
    int con_datos = 0;
    for (int i = 0; i < d; i++){
        if (creditosbin[i].orden != 0) con_datos = i+1;
    }

    //Ahora imprime todos hasta con_datos
    for (int i = 0; i < con_datos; i++){
        if (opcion == 1 && creditosbin[i].activo == 0) continue; //Si la opcion es solo los activos, no imprimir los inactivos
        if (opcion == 2 && strcmp(creditosbin[i].tipo, tipo) != 0) continue; //Si la opcion es solo los activos, no imprimir los inactivos

        //Filtro por fecha
        if (opcion == 3){
            struct fecha fecha_credito;
            fechames_to_fecha(creditosbin[i].date, &fecha_credito);
            if (!(fechacmp(fecha_credito, fecha1) >= 0 && fechacmp(fecha_credito, fecha2) <= 0))
                continue;
        }

        printf("%-3d  %-11s %-10s %9.2f %17s  %02d/%3s/%04d %8d %14.2lf %8.2lf %13.2lf %3d\n",
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

    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);

    //Primero intenta abrirlo para ver si ya existe.
    pArchivo = fopen("creditos.dat", "rb");

    if (pArchivo != NULL) {
        //En este caso existe, le pregunta al usuario si quiere crear un archivo en blanco
        set_text_color(14);
        printf("Ya existe un archivo \"creditos.dat\". Desea sobreescribirlo con un archivo en blanco?\n");
        set_text_color(7);
        printf("[S/N]> ");

        char opcion;
        scanf("%c", &opcion);
        fflush(stdin);
        opcion = toupper(opcion);

        if (opcion == 'S'){
            //Crea el archivo vacio
            pArchivo = fopen("creditos.dat", "wb");
            fwrite(creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
            fclose(pArchivo);

            set_text_color(10);
            printf("Archivo \"creditos.dat\" vacio creado.\n\n");
            set_text_color(7);
        }
    }
    else{
        //Crea el archivo vacio
        pArchivo = fopen("creditos.dat", "wb");
        fwrite(creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);

        set_text_color(10);
        printf("Archivo \"creditos.dat\" vacio creado.\n");
        set_text_color(7);
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
        set_text_color(12);
        printf("[!] No existe un archivo \"creditos.dat\". Cree uno con \"nuevodat\" o importe un CSV con \"importarcsv\".\n\n");
        set_text_color(7);
        return 0;
    }
}

///LISTAR: Funcion que muestra los archivos de creditos.dat
void listar_bin(char *arg1, char *arg2, char *arg3){
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

        //Lee el archivo
        fseek(pArchivo, 0, SEEK_SET);
        fread(&creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);

        int opcion = 0; //Filtros de listado
        char tipo[32];
        struct fecha fecha1, fecha2;
        if (arg1 != NULL){
            if (strcmp(arg1, "activos") == 0) opcion = 1;
            if (strcmp(arg1, "tipo") == 0) opcion = 2;
            if (strcmp(arg1, "fecha") == 0) opcion = 3;
        }

        if (opcion == 2){
            if (arg2 != NULL && strcmp(arg2, "garantia") == 0){
                strcpy(tipo, "CON GARANTIA");
            }
            else if (arg2 != NULL && strcmp(arg2, "firma") == 0){
                strcpy(tipo, "A SOLA FIRMA");
            }
            else{
                char tipo_c;
                printf("Ingrese el tipo de credito:\nA: CON GARANTIA\nB: A SOLA FIRMA\nTIPO> ");
                scanf("%c", &tipo_c);
                fflush(stdin);
                tipo_c = toupper(tipo_c);

                if (tipo_c == 'A') strcpy(tipo, "CON GARANTIA");
                else if (tipo_c == 'B') strcpy(tipo, "A SOLA FIRMA");
                else{
                    set_text_color(12);
                    printf("[!] Tipo de credito invalido.");
                    set_text_color(7);
                    fclose(pArchivo);
                    return;
                }
            }
        }

        if (opcion == 3){
            //Fecha 1
            if (arg2 != NULL){
                str_to_fecha(&fecha1, arg2);
                if (!fecha_valida(fecha1)){
                    set_text_color(12);
                    printf("[!] Fecha inicial invalida (mas dias de los que tiene el mes? o mas meses de los que tiene el a%co?).\n", 164);
                    set_text_color(7);
                    fclose(pArchivo);
                    return;
                }
            }
            else{
                set_text_color(15);
                printf("FECHA INICIAL:\n");
                set_text_color(7);
                scan_fecha(&fecha1);
                if (!fecha_valida(fecha1)){
                    set_text_color(12);
                    printf("[!] Fecha inicial invalida (mas dias de los que tiene el mes? o mas meses de los que tiene el a%co?).\n", 164);
                    set_text_color(7);
                    fclose(pArchivo);
                    return;
                }
            }

            //Fecha 2
            if (arg3 != NULL){
                str_to_fecha(&fecha2, arg3);
                if (!fecha_valida(fecha2)){
                    set_text_color(12);
                    printf("[!] Fecha final invalida (mas dias de los que tiene el mes? o mas meses de los que tiene el a%co?).\n", 164);
                    set_text_color(7);
                    fclose(pArchivo);
                    return;
                }
            }
            else{
                set_text_color(15);
                printf("FECHA FINAL:\n");
                set_text_color(7);
                scan_fecha(&fecha2);
                if (!fecha_valida(fecha2)){
                    set_text_color(12);
                    printf("[!] Fecha final invalida (mas dias de los que tiene el mes? o mas meses de los que tiene el a%co?).\n", 164);
                    set_text_color(7);
                    fclose(pArchivo);
                    return;
                }
            }

            //Se fija si fecha 1 < fecha 2
            if (fechacmp(fecha1, fecha2) == 1){
                set_text_color(12);
                printf("[!] La fecha inicial es mayor a la fecha final.\n");
                set_text_color(7);
                fclose(pArchivo);
                return;
            }
        }
        listar_tabla_creditos(creditosbin, registros, opcion, tipo, fecha1, fecha2);

        fclose(pArchivo);
    }
}

///ALTAS: Funcion que da de alta a un credito.
void alta(char * arg1){
    if (!existe_bin()) return;

    FILE *pArchivo;
    pArchivo = fopen("creditos.dat", "rb");

    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);

    if (pArchivo != NULL){
        //Calcula el tamaño del archivo. Sale si el archivo esta vacio.
        int fsize = tamano_bin(pArchivo);

        //Lee el archivo
        fseek(pArchivo, 0, SEEK_SET);
        fread(&creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);

        //Lee el numero de orden, ya sea por linea de comandos o por entrada aparte
        set_text_color(11);
        printf("----- DAR NUEVA ALTA -----\n");
        set_text_color(7);
        //Orden
        int orden;
        if (arg1 == NULL){
            printf("Ingrese el numero de orden del credito a dar alta:\nORDEN> ");
            scanf("%d", &orden);
            fflush(stdin);
        }
        else{
            sscanf(arg1, "%d", &orden);
        }

        if (orden < 1 || orden > TABLE_MAX){//SI EL VALOR ESTA FUERA DE RANGO
            set_text_color(12);
            printf("[!] Orden ingresado fuera de rango. Ingrese un numero de orden valido.\n");
            set_text_color(7);
            return;
        }
        if (creditosbin[orden-1].orden != 0){//SI EL CREDITO NO EXISTE
            set_text_color(12);
            printf("[!] Ya existe un credito de orden %d. Elija otro.\n", orden);
            set_text_color(7);
            return;
        }

        creditosbin[orden-1].orden = orden;

        //Nombre
        printf("Nombre: ");
        scanf("%31s", creditosbin[orden-1].nombre);
        fflush(stdin);
        //Apellido
        printf("Apellido: ");
        scanf("%31s", creditosbin[orden-1].apellido);
        fflush(stdin);
        string_toupper(creditosbin[orden-1].apellido, strlen(creditosbin[orden-1].apellido));

        //Importe
        creditosbin[orden-1].importe = scan_num_range("Importe: ", 0, 9999999);

        //Tipo
        char tipo_c;
        do{
            printf("Ingrese un tipo de credito. (A: CON GARANTIA; B: A SOLA FIRMA)\nTipo: ");
            scanf("%c", &tipo_c);
            fflush(stdin);
            tipo_c = toupper(tipo_c);

            if (tipo_c != 'A' && tipo_c != 'B'){
                set_text_color(12);
                printf("[!] Tipo de credito invalido. Ingrese un tipo de credito valido.\n");
                set_text_color(7);
            }
        } while (tipo_c != 'A' && tipo_c != 'B');

        if (tipo_c == 'A') strcpy(creditosbin[orden-1].tipo, "CON GARANTIA");
        if (tipo_c == 'B') strcpy(creditosbin[orden-1].tipo, "A SOLA FIRMA");


        //Fecha
        char strfecha[11] = "00/00/0000";
        do{
            printf("Ingrese la fecha (formato: dia/mes/a%co en numeros)\nFecha: ", 164);
            scanf("%10s", strfecha);
            fflush(stdin);

            str_to_fechames(&creditosbin[orden-1].date, strfecha);

            if (creditosbin[orden-1].date.dia == 0 ||
                creditosbin[orden-1].date.anio == 0 ||
                strcmp(creditosbin[orden-1].date.mes, "---") == 0){
                    set_text_color(12);
                    printf("[!] Fecha invalida. Ingrese una fecha valida.\n");
                    set_text_color(7);
                }

        } while (creditosbin[orden-1].date.dia == 0 ||
                 creditosbin[orden-1].date.anio == 0 ||
                 strcmp(creditosbin[orden-1].date.mes, "---") == 0);


        //Varios valores numericos
        creditosbin[orden-1].cuotas = (int) scan_num_range("Cuotas: ", 0, 999999);
        creditosbin[orden-1].importe_cuota = (double) scan_num_range("Importe cuota: ", 0, 99999999);
        creditosbin[orden-1].iva = (double) scan_num_range("IVA: ", 0, 99999999);
        creditosbin[orden-1].total_cuota = (double) scan_num_range("Total cuota: ", 0, 99999999);
        creditosbin[orden-1].activo = 1;


        //Aca abre de nuevo el archivo y escribe todo el struct, luego lo cierra de nuevo
        pArchivo = fopen("creditos.dat", "wb");
        fwrite(creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);

        set_text_color(10);
        printf("Alta de credito en orden %d realizado con exito.\n", orden);
        set_text_color(7);
    }
}

void modificar(char *arg1, char *arg2, char *arg3){
    if (!existe_bin()) return;

    FILE *pArchivo;
    pArchivo = fopen("creditos.dat", "rb");

    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);

    if (pArchivo != NULL){
        //Calcula el tamaño del archivo. Sale si el archivo esta vacio.
        int fsize = tamano_bin(pArchivo);

        //Lee el archivo
        fseek(pArchivo, 0, SEEK_SET);
        fread(&creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);

        //Lee el numero de orden, ya sea por linea de comandos o por entrada aparte
        //Orden
        int orden;
        if (arg1 == NULL){
            printf("Ingrese el numero de orden del credito a modificar:\nORDEN> ");
            scanf("%d", &orden);
            fflush(stdin);
        }
        else{
            sscanf(arg1, "%d", &orden);
        }

        if (orden < 1 || orden > TABLE_MAX){//SI EL VALOR ESTA FUERA DE RANGO
            set_text_color(12);
            printf("[!] Orden ingresado fuera de rango. Ingrese un numero de orden valido.\n");
            set_text_color(7);
            return;
        }
        if (creditosbin[orden-1].orden == 0){//SI EL CREDITO NO EXISTE
            set_text_color(12);
            printf("[!] No existe un credito de orden %d. \n", orden);
            set_text_color(7);
            return;
        }

        char opcion = '-';
        if (arg2 == NULL){
            printf("Que campo desea modificar?\n"
                   "A: TIPO DE CREDITO\n"
                   "B: IMPORTE\n"
                   "OPCION> ");
            scanf("%c", &opcion);
            fflush(stdin);
            opcion = toupper(opcion);
        }
        else{
            if (strcmp(arg2, "tipo") == 0) opcion = 'A';
            if (strcmp(arg2, "importe") == 0) opcion = 'B';
        }
        //Opcion invalida?
        if (opcion != 'A' && opcion != 'B'){
            set_text_color(12);
            printf("[!] Opcion invalida. Ingrese una opcion valida. \n");
            set_text_color(7);
            return;
        }
        //MODIFICAR TIPO?
        if (opcion == 'A'){
            char tipo;
            if (arg3 == NULL){
                printf("Que tipo?\n"
                       "A: CON GARANTIA\n"
                       "B: A SOLA FIRMA\n"
                       "OPCION> ");
                scanf("%c", &opcion);
                fflush(stdin);
                tipo = toupper(opcion);
            }
            else{
                if (strcmp(arg3, "garantia") == 0) tipo = 'A';
                if (strcmp(arg3, "firma") == 0) tipo = 'B';
            }

            if (tipo != 'A' && tipo != 'B'){
                set_text_color(12);
                printf("[!] Opcion invalida. Ingrese una opcion valida. \n");
                set_text_color(7);
                return;
            }

            char confirmacion;
            printf("Esta seguro que quiere modificar el credito?\n[S/N]> ");
            scanf("%c", &confirmacion);
            fflush(stdin);
            confirmacion = toupper(confirmacion);

            if (confirmacion == 'S'){
                if (tipo == 'A') strcpy(creditosbin[orden-1].tipo, "CON GARANTIA");
                if (tipo == 'B') strcpy(creditosbin[orden-1].tipo, "A SOLA FIRMA");
                set_text_color(10);
                printf("Tipo de credito en orden %d modificado con exito.\n", orden);
                set_text_color(7);
            }
        }
        //MODIFICAR IMPORTE?
        if (opcion == 'B'){
            float importe;
            if (arg3 == NULL){
                printf("Ingrese el importe: ");
                scanf("%f", &importe);
                fflush(stdin);
            }
            else{
                string_changechar(arg3, strlen(arg3), ',', '.');
                sscanf(arg3, "%f", &importe);
            }

            if (importe <= 0.000001f){
                set_text_color(12);
                printf("[!] Importe invalido. \n");
                set_text_color(7);
                return;
            }

            char confirmacion;
            printf("Esta seguro que quiere modificar el credito?\n[S/N]> ");
            scanf("%c", &confirmacion);
            fflush(stdin);
            confirmacion = toupper(confirmacion);

            if (confirmacion == 'S'){
                creditosbin[orden-1].importe = importe;
                set_text_color(10);
                printf("Importe de credito en orden %d modificado con exito.\n", orden);
                set_text_color(7);
            }
        }


        //Aca abre de nuevo el archivo y escribe todo el struct, luego lo cierra de nuevo
        pArchivo = fopen("creditos.dat", "wb");
        fwrite(creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);
    }
}

///BUSCAR: Funcion que busca un dato por orden o apellido, e imprime todos los datos.
void buscar(char *arg1, char *arg2, char *arg3){
    if (!existe_bin()) return;

    FILE *pArchivo;
    pArchivo = fopen("creditos.dat", "rb");

    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);

    if (pArchivo != NULL){
        //Calcula el tamaño del archivo. Sale si el archivo esta vacio.
        int fsize = tamano_bin(pArchivo);
        if (fsize == 0){
            set_text_color(14);
            printf("El archivo \"creditos.dat\" esta vacio.\n");
            set_text_color(7);
            fclose(pArchivo);
            return;
        }

        int registros = fsize/sizeof(struct credito);

        //Lee el archivo
        fseek(pArchivo, 0, SEEK_SET);
        fread(&creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);

        int opcion = 0;
        //Tipo de dato a usar para buscar
        if (arg1 != NULL){
            if (strcmp(arg1, "orden") == 0) opcion = 1;
            if (strcmp(arg1, "apellido") == 0) opcion = 2;
        }
        else{
            printf("Ingrese el tipo de dato para buscar el credito:\n"
                   "1: Numero de orden; 2: Apellido.\n"
                   "TIPO> ");
            scanf("%d", &opcion);
            fflush(stdin);
        }
        if (opcion != 1 && opcion != 2){
            set_text_color(12);
            printf("[!] Opcion invalida. Ingrese una opcion valida.\n");
            set_text_color(7);
            return;
        }

        //Si es por numero de orden:
        if (opcion == 1){
            int orden = -1;
            if (arg2 != NULL){
                sscanf(arg2, "%d", &orden);
            }
            else{
                printf("Ingrese el numero de orden:\n"
                       "ORDEN> ");
                scanf("%d", &orden);
                fflush(stdin);
            }
            //Validacion
            if (orden < 1 || orden > TABLE_MAX){//SI EL VALOR ESTA FUERA DE RANGO
                set_text_color(12);
                printf("[!] Orden ingresado fuera de rango. Ingrese un numero de orden valido.\n");
                set_text_color(7);
                return;
            }
            if (creditosbin[orden-1].orden == 0){//SI EL CREDITO NO EXISTE
                set_text_color(12);
                printf("[!] No existe un credito de orden %d. \n", orden);
                set_text_color(7);
                return;
            }

            //Ahora si busca el credito por numero de orden
            set_text_color(11);
            printf("----- DATOS DEL CREDITO -----\n");
            set_text_color(7);
            printf(
                   "Orden: %d\n"
                   "Apellido: %s\n"
                   "Nombre: %s\n"
                   "Importe: %.2f\n"
                   "Tipo de credito: %s\n"
                   "Fecha: %02d/%s/%04d\n"
                   "Cuotas: %d\n"
                   "Importe de la cuota: %.2f\n"
                   "IVA: %.2f\n"
                   "Total de la cuota: %.2f\n"
                   "Activo: %d\n",
                   creditosbin[orden-1].orden,
                   creditosbin[orden-1].apellido,
                   creditosbin[orden-1].nombre,
                   creditosbin[orden-1].importe,
                   creditosbin[orden-1].tipo,
                   creditosbin[orden-1].date.dia,
                   creditosbin[orden-1].date.mes,
                   creditosbin[orden-1].date.anio,
                   creditosbin[orden-1].cuotas,
                   creditosbin[orden-1].importe_cuota,
                   creditosbin[orden-1].iva,
                   creditosbin[orden-1].total_cuota,
                   creditosbin[orden-1].activo
                   );
        }
        //Si es por apellido
        if (opcion == 2){
            int orden = -1;
            char apellido[32];

            if (arg2 != NULL){
                strcpy(apellido, arg2);
                //Procrastinacion: Esto es horrible, lo voy a arreglar despues
                if (arg3 != NULL){
                    strcat(apellido, " ");
                    strcat(apellido, arg3);
                }
            }
            else{
                printf("Ingrese el apellido:\n"
                       "APELLIDO> ");
                scanf("%31[^\n]", apellido);
                fflush(stdin);
            }

            string_toupper(apellido, strlen(apellido));

            //Busca el orden por apellido
            for (int i = 0; i < TABLE_MAX; i++){
                if (strcmp(creditosbin[i].apellido, apellido) == 0){
                    orden = i;
                    break;
                }
            }
            if (orden < 0){
                set_text_color(12);
                printf("[!] No se pudo encontrar un credito con ese apellido.\n");
                set_text_color(7);
                return;
            }

            //Si encontro el credito lo imprime
            set_text_color(11);
            printf("----- DATOS DEL CREDITO -----\n");
            set_text_color(7);
            printf(
                   "Orden: %d\n"
                   "Apellido: %s\n"
                   "Nombre: %s\n"
                   "Importe: %.2f\n"
                   "Tipo de credito: %s\n"
                   "Fecha: %02d/%s/%04d\n"
                   "Cuotas: %d\n"
                   "Importe de la cuota: %.2f\n"
                   "IVA: %.2f\n"
                   "Total de la cuota: %.2f\n"
                   "Activo: %d\n",
                   creditosbin[orden].orden,
                   creditosbin[orden].apellido,
                   creditosbin[orden].nombre,
                   creditosbin[orden].importe,
                   creditosbin[orden].tipo,
                   creditosbin[orden].date.dia,
                   creditosbin[orden].date.mes,
                   creditosbin[orden].date.anio,
                   creditosbin[orden].cuotas,
                   creditosbin[orden].importe_cuota,
                   creditosbin[orden].iva,
                   creditosbin[orden].total_cuota,
                   creditosbin[orden].activo
                   );
        }


        fclose(pArchivo);
    }
}

///BAJALOGICA: Funcion que da de baja a un credito (activo = 0;
void baja_logica(char * arg1){
    if (!existe_bin()) return;

    FILE *pArchivo;
    pArchivo = fopen("creditos.dat", "rb");

    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);

    if (pArchivo != NULL){
        //Calcula el tamaño del archivo. Sale si el archivo esta vacio.
        int fsize = tamano_bin(pArchivo);
        if (fsize == 0){
            set_text_color(14);
            printf("El archivo \"creditos.dat\" esta vacio.\n");
            set_text_color(7);
            fclose(pArchivo);
            return;
        }

        //Lee el archivo
        fseek(pArchivo, 0, SEEK_SET);
        fread(&creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);

        //Lee el numero de orden, ya sea por linea de comandos o por entrada aparte
        int orden;
        if (arg1 == NULL){
            printf("Ingrese el numero de orden a dar la baja logica:\nORDEN> ");
            scanf("%d", &orden);
            fflush(stdin);
        }
        else{
            sscanf(arg1, "%d", &orden);
        }

        //SI EL VALOR ESTA FUERA DE RANGO
        if (orden < 1 || orden > TABLE_MAX){
            set_text_color(12);
            printf("[!] Orden ingresado fuera de rango. Ingrese un numero de orden valido.\n");
            set_text_color(7);
            return;
        }

        //SI EL CREDITO NO EXISTE
        if (creditosbin[orden-1].orden == 0){
            set_text_color(12);
            printf("[!] No existe un credito en el orden %d.\n", orden);
            set_text_color(7);
            return;
        }

        //SI EL CREDITO YA ES PASIVO
        if (creditosbin[orden-1].activo == 0){
            set_text_color(12);
            printf("[!] El credito con orden %d no es activo.\n", orden);
            set_text_color(7);
            return;
        }

        creditosbin[orden-1].activo = 0;

        pArchivo = fopen("creditos.dat", "wb");
        fwrite(creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);

        set_text_color(10);
        printf("Baja logica en orden %d realizado con exito.\n", orden);
        set_text_color(7);
    }
}

///BAJAFISICA: Funcion que borra completamente a un credito
void baja_fisica(char *arg1){
    if (!existe_bin()) return;

    FILE *pArchivo;
    FILE *pArchivoXyz;
    pArchivo = fopen("creditos.dat", "rb");

    struct credito creditosbin[TABLE_MAX];
    inicializar_credito(creditosbin, TABLE_MAX);

    if (pArchivo != NULL){
        //Calcula el tamaño del archivo. Sale si el archivo esta vacio.
        int fsize = tamano_bin(pArchivo);
        if (fsize == 0){
            set_text_color(14);
            printf("El archivo \"creditos.dat\" esta vacio.\n");
            set_text_color(7);
            fclose(pArchivo);
            return;
        }

        //Lee el archivo
        fseek(pArchivo, 0, SEEK_SET);
        fread(&creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);
        fclose(pArchivo);

        //Lee el numero de orden, ya sea por linea de comandos o por entrada aparte
        int orden;
        if (arg1 == NULL){
            printf("Ingrese el numero de orden a dar la baja logica:\nORDEN> ");
            scanf("%d", &orden);
            fflush(stdin);
        }
        else{
            sscanf(arg1, "%d", &orden);
        }

        //SI EL VALOR ESTA FUERA DE RANGO
        if (orden < 1 || orden > TABLE_MAX){
            set_text_color(12);
            printf("[!] Orden ingresado fuera de rango. Ingrese un numero de orden valido.\n");
            set_text_color(7);
            return;
        }

        //SI EL CREDITO NO EXISTE
        if (creditosbin[orden-1].orden == 0){
            set_text_color(12);
            printf("[!] No existe un credito en el orden %d.\n", orden);
            set_text_color(7);
            return;
        }

        //Obtiene el string de fecha
        char str_tiempo[11];
        get_date_string(str_tiempo, '-');

        char ruta_xyz[30] = "clientes_bajas_";
        strcat(ruta_xyz, str_tiempo);
        strcat(ruta_xyz, ".xyz");

        pArchivo = fopen("creditos.dat", "wb");
        pArchivoXyz = fopen(ruta_xyz, "a");

        struct fecha fechanum;
        fechames_to_fecha(creditosbin[orden-1].date, &fechanum);

        fprintf(pArchivoXyz, "%d;%s %s;%d;%s;%d;%d;%d;%d;%f;%f;%f\n",
                creditosbin[orden-1].orden,
                creditosbin[orden-1].nombre,
                creditosbin[orden-1].apellido,
                (int) creditosbin[orden-1].importe,
                creditosbin[orden-1].tipo,
                fechanum.dia,
                fechanum.mes,
                fechanum.anio,
                creditosbin[orden-1].cuotas,
                creditosbin[orden-1].importe_cuota,
                creditosbin[orden-1].iva,
                creditosbin[orden-1].total_cuota
                );

        creditosbin[orden-1].activo = 0;
        creditosbin[orden-1].orden = 0;
        strcpy(creditosbin[orden-1].apellido, "");
        strcpy(creditosbin[orden-1].nombre, "");
        creditosbin[orden-1].importe = 0;
        strcpy(creditosbin[orden-1].tipo, "");
        creditosbin[orden-1].date.dia = 0;
        strcpy(creditosbin[orden-1].date.mes, "---");
        creditosbin[orden-1].date.anio = 0;
        creditosbin[orden-1].cuotas = 0;
        creditosbin[orden-1].importe_cuota = 0;
        creditosbin[orden-1].iva = 0;
        creditosbin[orden-1].total_cuota = 0;

        fwrite(creditosbin, sizeof(struct credito)*TABLE_MAX, 1, pArchivo);

        set_text_color(10);
        printf("Baja fisica en orden %d realizado con exito.\n", orden);
        set_text_color(7);

        fclose(pArchivo);
        fclose(pArchivoXyz);
    }
}
