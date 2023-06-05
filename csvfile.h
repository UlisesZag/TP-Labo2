#include <stdio.h>
#include <stdlib.h>

//Lista un csv que ingrese el usuario
void listar_txt(){
    char ruta[32];
    struct credito_csv creditos[64];

    printf("Ingrese la ruta del archivo CSV a listar: \nRUTA>");
    scanf("%s", ruta);
    fflush(stdin);

    //Abre el archivo en solo lectura
    FILE * pArchivo;
    pArchivo = fopen(ruta, "r");

    if (pArchivo == NULL){
        printf("ERROR: El archivo no existe. Verificar ruta ingresada.\n");
    }
    else{
        //Lee el csv por lineas
        char linea[1024];
        int pos = 0;

        printf("Ord  Nombre y apellido  Importe    Tipo        Fecha        Cuotas  Imp. Cuota  IVA     Total Cuota\n");

        fgets(linea, 1024, pArchivo);
        fgets(linea, 1024, pArchivo);//Lee la primera linea para pasar directamente a la segunda.
        while (!feof(pArchivo)){
            sscanf(linea, "%d;%32[^;];%d;%32[^;];%d;%d;%d;%d;%f;%f;%f;\n",
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
            printf("%4d %19s %9d %8s %4d/%02d/%4d %6d %10.2f %8.2f %8.2f\n",
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
