#ifndef H_PELICULA_H
#define H_PELICULA_H

#include "Reparto.h"

//Constantes:


//Tipos:
typedef struct tPelicula {
	std::string titulo, director, genero, valoracion;
	tReparto listaReparto[MAX_ACTORES];
	int contReparto;
};

//Funciones:
bool cargar(tPelicula& pelicula, std::ifstream&); //Carga una pel�cula.
bool interviene(tPelicula& pelicula, std::string& nombre); //True si el actor se encuentra en la pel�cula, false en caso contrario.
void mostrar(tPelicula& pelicula); //Muestra por pantalla el t�tulo, director, g�nero y valoraci�n de una pel�cula.

#endif // !H_PELICULA_H
