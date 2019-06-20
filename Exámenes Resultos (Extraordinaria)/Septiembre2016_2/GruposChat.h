#ifndef _GRUPOSCHAT
#define _GRUPOSCHAT

#include "ListaContactos.h"

//Constantes:


//Tipos:
typedef struct tElemento {
	tContacto *puntero;
	int numMensajes;
};

typedef struct tGrupoChat {
	tElemento *elemento; //Ordenada por id.
	std::string nombreGrupo;
	int capacidad;
	int cont;
};

//Funciones:
void nuevo(tGrupoChat& grupo);
void insertar(tGrupoChat& grupo, tElemento& element); //Insertar por id.
bool buscar(tGrupoChat& grupo, std::string& id, int&, int&, int&); //Recursiva y binaria.
void mostrar(tGrupoChat& grupo);
void combinar(tGrupoChat& grupoA, tGrupoChat& grupoB, tGrupoChat& grupoC);
void destruir(tGrupoChat& grupo);


#endif // !_GRUPOSCHAT
