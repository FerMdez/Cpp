#ifndef H_LISTALONJA_H
#define H_LISTALONJA_H

#include "lotes.h"

//Constantes:

//Tipos:
typedef struct tListaLotes {
	tLotes* lote[MAX_LOTES];
	int cont;
};
//Funciones:
void inicializar(tListaLotes& lista);
int numLotes(tListaLotes& lista);
bool insertar(tListaLotes& lista, tLotes& nuevo);
bool cargar(tListaLotes& lista);
bool buscar(tListaLotes& lista, tLotes& nuevo, int& pos); //Implementación recursiva y binaria.
void obeternerLote(tListaLotes& lista, tLotes* lote, int& pos);
void mostrar(tListaLotes& lista, tListaComprador& comprador);
void liberar(tListaLotes& lista);

#endif // !H_LISTALONJA_H
