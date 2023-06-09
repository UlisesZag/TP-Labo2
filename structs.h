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
