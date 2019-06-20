#ifndef _LISTAGRUPOS
#define _LISTAGRUPOS

#include "ListaEstudiantes.h"

//Constantes:
const int MAX_GRUPOS = 10;

//Tipos:
typedef struct tGrupo {
	tListaEstudiantes estudiantes;
	std::string id;
};

typedef struct tListaGrupos {
	tGrupo *grupo[MAX_GRUPOS];
	int cont;
};


//Funciones:
bool cargar(tListaGrupos& grupos);
void mostrar(tListaGrupos& grupos);
bool buscar(tListaGrupos& grupos, std::string NIF, int& pos); //Recursiva;
void destruir(tListaGrupos grupos);

#endif // !_LISTAGRUPOS
