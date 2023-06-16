#ifndef _STRUCTFUNCS_H_
#define _STRUCTFUNCS_H_

void inicializar_credito(struct credito c[], int d);
void inicializar_creditocsv(struct credito_csv c[], int d);
void str_to_fechames(struct fecha_mes * date, char * str_date);
void fechames_to_fecha(struct fecha_mes datemes, struct fecha * date);
int fechacmp(struct fecha date1, struct fecha date2);

#endif // _STRUCTFUNCS_H_
