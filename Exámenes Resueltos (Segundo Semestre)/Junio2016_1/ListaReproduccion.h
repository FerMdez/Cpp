#ifndef _LISTAREPRODUCCIONES
#define _LISTAREPRODUCCIONES

#include "ListaTemas.h"

//Constantes:


//Tipos:
typedef struct tElemento {
	tTema *puntero;
	int valoracion;
};

typedef struct tListaReproduccion{
	tElemento *elemento;
	std::string nombreLista;
	int capacidad;
	int cont;
};

//Funciones:
void nueva(tListaReproduccion& lista);
bool insertar(tListaReproduccion& lista, tElemento& elemento);
bool buscar(tListaReproduccion& lista, std::string titulo, int& ini, int& fin, int& pos); //Binaria y recursiva.
void mostrar(tListaReproduccion& lista);
void modificarOrden(tListaReproduccion& lista, int& origen, int& fin);
void destruir(tListaReproduccion& lista);


#endif // !_LISTAREPRODUCCIONES
