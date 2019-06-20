//Sudoku - Fernando Méndez Torrubiano
#ifndef H_JUEGOSODOKU_H
#define H_JUEGOSODOKU_H
#pragma once

#include <iostream>
#include <string>
#include "ListaSudokus.h"
#include "TableroSudoku.h"

//Constantes:

//Tipos:
typedef struct tJuegoSudoku {
	tRegSudoku registro;
	tTableroSudoku tablero;
};

//Funciones:
void mostrar(const tJuegoSudoku& juego); //Muestra por pantalla la  información del sudoku que se va a jugar así como el tablero del mismo. bool cargar(tJuegoSuduko & juego, const tRegSudoku & sudoku) : actualiza el tablero del parámetro juego con el contenido del archivo cuyo  nombre figura en el parámetro sudoku.
int jugar(const tRegSudoku& sudoku); //Dada la información del sudoku elegido lleva a cabo todas las acciones correspondientes a haber elegido la opción 1 de esta versión y devuelve la puntuación obtenida por el jugador (0 si  aborta  la  resolución  antes  de  rellenar  el  tablero  o  los  puntos  asociados  al  sudoku elegido en caso de resolverlo).
char subMenu();
void ejecutarSubMenu(tJuegoSudoku& juego, int& puntos);
void pedirCoordenadas(tCoor& coordenadas);
void actulizarCandidatos(tJuegoSudoku& juego, tCoor& coordenadas);

#endif