//Struct donde se puede almacenar una fecha.
struct fecha{
    int dia;
    int mes;
    int anio;
};
//Igual pero con el mes como un string de 3 caracteres
struct fecha_mes{
    int dia;
    char mes[3];
    int anio;
};

//Struct con los datos de un credito, el cual se guarda en creditos.dat
struct credito{
    int orden;
    char nombre[32];
    char apellido[32];
    float importe;
    char tipo[32];
    struct fecha_mes date;
    int cuotas;
    double importe_cuota;
    double iva;
    double total_cuota;
    int activo;
};

void inicializar_credito(struct credito c[], int d){
    for (int i = 0; i < d; i++){
        c[i].orden = 0;
        strcpy(c[i].nombre, "");
        strcpy(c[i].apellido, "");
        c[i].importe = 0.0;
        strcpy(c[i].tipo, "");
        c[i].date.dia = 0;
        strcpy(c[i].date.mes, "---");
        c[i].date.anio = 0;
        c[i].cuotas = 0;
        c[i].importe_cuota = 0;
        c[i].iva = 0;
        c[i].total_cuota = 0;
        c[i].activo = 0;
    }
}

//Struct con los datos de un credito, leido directamente del CSV, el cual se convierte a un struct credito
struct credito_csv{
    int orden;
    char cliente[32];
    int importe;
    char tipo[32];
    struct fecha date;
    int cuotas;
    double importe_cuota;
    double iva;
    double total_cuota;
};

 void inicializar_creditocsv(struct credito_csv c[], int d){
    for (int i = 0; i < d; i++){
        c[i].orden = 0;
        strcpy(c[i].cliente, "");
        c[i].importe = 0.0;
        strcpy(c[i].tipo, "");
        c[i].date.dia = 0;
        c[i].date.mes = 0;
        c[i].date.anio = 0;
        c[i].cuotas = 0;
        c[i].importe_cuota = 0;
        c[i].iva = 0;
        c[i].total_cuota = 0;
    }
}
