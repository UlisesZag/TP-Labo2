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
    char nombre[32];
    char apellido[32];
    float importe;
    int tipo;
    struct fecha_mes date;
    int cuotas;
    float importe_cuota;
    float iva;
    float total_cuota;
    int activo;
};

//Struct con los datos de un credito, leido directamente del CSV, el cual se convierte a un struct credito
struct credito_csv{
    char cliente[32];
    int importe;
    int tipo;
    struct fecha date;
    int cuotas;
    float importe_cuota;
    float iva;
    float total_cuota;
};
