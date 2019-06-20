#ifndef _LISTACITAS
#define _LISTACITAS

#include "ListaClientes.h"

//Constantes:


//Tipos:
typedef struct tCita {
	tCliente *puntero1;
	tCliente *puntero2;
	std::string lugar;
	int valoracion;
};

typedef struct tListaCitas {
	tCita *lista; //Ordena por valoracion, de mayor a menor.
	int cont;
	int capacidad;
};

//Funciones:
void nuevaLista(tListaCitas& listaCitas);
bool inserta(tListaCitas& listaCitas, const tCita& cita); //const tCliente&, const tCliente&, std::string&, int&
void muestra(const tListaCitas& listaCitas);
void libera(tListaCitas& listaCitas);

#endif // !_LISTACITAS
