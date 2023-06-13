#ifndef _BINFILE_H_
#define _BINFILE_H_

int tamano_bin(FILE * pArchivo);
void listar_tabla_creditos(struct credito creditosbin[], int d, int opcion, char tipo[]);
void crear_creditosdat();
int existe_bin();
void listar_bin(char *arg1, char *arg2);
void alta(char * arg1);
void modificar(char *arg1, char *arg2, char *arg3);
void buscar(char *arg1, char *arg2, char *arg3);
void baja_logica(char * arg1);
void baja_fisica(char *arg1);


#endif // _BINFILE_H_
