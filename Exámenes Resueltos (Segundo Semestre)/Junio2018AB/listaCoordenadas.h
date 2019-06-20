#ifndef _LISTACOORDENADAS
#define _LISTACOORDENADAS

#include "jardin.h"

//Constantes:
const int MAX_COORDENADAS = DIM * DIM;

//Tipos:
typedef struct tListaCoordenadas {
	tCoordenada coordenada[MAX_COORDENADAS];
	int cont;
};

//Funciones:
void crearVacia(tListaCoordenadas& listaCoor);
bool buscar(tListaCoordenadas& listaCoor, tCoordenada& coordenada);
bool insertar(tListaCoordenadas& listaCoor, tCoordenada& coor);
bool sacar(tListaCoordenadas& listaCoor, tCoordenada& coor);

#endif // !_LISTACOORDENADAS
