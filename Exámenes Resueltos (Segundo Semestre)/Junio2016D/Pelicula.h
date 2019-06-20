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
bool cargar(tPelicula& pelicula, std::ifstream&); //Carga una película.
bool interviene(tPelicula& pelicula, std::string& nombre); //True si el actor se encuentra en la película, false en caso contrario.
void mostrar(tPelicula& pelicula); //Muestra por pantalla el título, director, género y valoración de una película.

#endif // !H_PELICULA_H
