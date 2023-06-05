#include <stdio.h>
#include <stdlib.h>

#define TABLE_MAX 64

//Lista un csv que ingrese el usuario
void listar_csv(){
    char ruta[32];
    struct credito_csv creditos[TABLE_MAX];
    FILE * pArchivo;

    printf("Ingrese la ruta del archivo CSV a listar: \nRUTA>");
    scanf("%s", ruta);
    fflush(stdin);

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
            printf("%4d %19s %9d %8s %4d/%02d/%4d %6d %10.2lf %8.2lf %8.2lf\n",
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
void importar_csv(){
    char ruta[32];
    struct credito_csv creditoscsv[TABLE_MAX];
    struct credito creditosbin[TABLE_MAX];
    FILE * pArchivoCsv;
    FILE * pArchivoBin;


    printf("Ingrese la ruta del archivo CSV a importar como creditos.dat: \nRUTA>");
    scanf("%s", ruta);
    fflush(stdin);

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
        for (int i = 0; i < TABLE_MAX; i++){
            creditosbin[i].orden = creditoscsv[i].orden;
            creditosbin[i].importe = creditoscsv[i].importe;
            //strcpy(&creditosbin[i].tipo, creditoscsv[i].tipo);
        }
    }

    //Guarda todo en un archivo
    fwrite(creditoscsv, sizeof(struct credito_csv[64]), 1, pArchivoBin);

    fclose(pArchivoCsv);
}
