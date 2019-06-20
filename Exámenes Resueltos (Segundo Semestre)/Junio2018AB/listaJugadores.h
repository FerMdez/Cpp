#ifndef _LISTAJUGADORES
#define _LISTAJUGADORES

#include "listaCoordenadas.h"

//Constantes:


//Tipos:
typedef struct tJugador {
	std::string nombre;
	int puntos;
};

typedef struct tListaJugadores {
	tJugador **jugador; //Ordenada por nombre y sin nombres repetidos.
	int cont;
	int capacidad;
};

//Funciones:
void iniciar(tListaJugadores& lista);
bool cargarJugadores(tListaJugadores& lista, std::ifstream& archivo);
bool guardarJugadores(tListaJugadores& lista, std::ofstream& archivo);
void mostrarJugadores(const tListaJugadores& jugadores);
bool buscar(tListaJugadores& jugadores, std::string nombre, int& pos); //Binaria y recursiva.
void actualizarPuntuacion(tListaJugadores& jugadores, std::string nombre, int puntos);
void mostrarPorPuntos(const tListaJugadores& jugadores);
void liberar(tListaJugadores& jugadores);

#endif // !_LISTAJUGADORES
