#ifndef H_LISTAPELICULAS_H
#define H_LISTAPELICULAS_H

#include "Pelicula.h"

//Constantes:
const int MAX_PELIS = 50;

//Tipos:
typedef struct tListaPeliculas {
	tPelicula *pelicula[MAX_PELIS];
	int cont;
};

//Funciones:
bool cargar(tListaPeliculas& listaPelis); //Carga la lista de películas.
void filtrarPorActor(tListaPeliculas& listaPelis, std::string& nombre); //Genera nueva lista que contiene enlaces a las películas donde ha participado ese actor.
void mostrar(tListaPeliculas& listaPelis); //Muestra la lista de películas
void ordenarPorGenero(tListaPeliculas& listaPelis); //Ordenadas por género de menor a mayor.
void ordenarPorValoracion(tPelicula& pelIZQ, tPelicula& pelDER); //Ordenación por inserción. Ordenadas por valoración de mayor a menor.
void destruir(tListaPeliculas& listaPelis);

#endif // !H_LISTAPELICULAS_H

