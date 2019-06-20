//Sudoku - Fernando Méndez Torrubiano
#ifndef H_TABLEROSODOKU_H
#define H_TABLEROSODOKU_H
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "CasillaSudoku.h"

//Constantes:
const int MAXDIM = 9;

//Tipos:
typedef struct tCoor {
	int fila, col;
}; 

typedef	struct tTableroSudoku {
	tCasillaSudoku casilla[MAXDIM][MAXDIM];
	int numVacias;
};

//Funciones:
bool cargar(tTableroSudoku& tablero, std::string nombreFichero); //carga la información almacenada en el archivo de nombre nombreFichero que  contiene el tablero del sudoku a jugar, contando las casillas, y devuelve un  booleano que indica si la carga se ha podido realizar.Los valores posibles de  las casillas deberán quedar convenientemente actualizados.
void mostrar(const tTableroSudoku& tablero); //Muestra por pantalla el tablero dado.
bool actualizar(tTableroSudoku& tablero, tCoor cor, int num); //Coloca el nº num en la casilla de coordenadas cor = (fila, col) (ambas en el  intervalo [0, 8]) del tablero tablero; el booleano que devuelve indica si la  acción ha sido posible (para ello la casilla debe ser vacía y num debe ser uno de  los valores posibles de la misma).Si es posible colocar el número dado en la  casilla indicada deberán actualizarse convenientemente los valores candidatos  de las casillas que puedan verse afectadas (las de la misma fila, columna y  submatriz  que  la  casilla  dada).También  se  debe  actualizar  el  número  de  casillas vacías.
bool borrar(tTableroSudoku& tablero, tCoor cor); //Borra el número  de la casilla de coordenadas cor = (fila, col)  (ambas en el intervalo [0, 8]) del  tablero tablero y la casilla volverá a estar en estado vacío; el booleano que  devuelve indica si la acción ha sido posible (debe ser una casilla que haya sido  previamente rellenada).Si es posible borrar el número de la casilla indicada  deberán actualizarse convenientemente los valores candidatos de las casillas  que puedan verse afectadas (las de la misma fila, columna y submatriz que la  casilla dada).También se debe actualizar el número de casillas vacías.
void mostrarCandidatos(const tTableroSudoku& tablero, tCoor cor); //Muestra los valores posibles de la casilla, del tablero dado, que tiene   coordenadas cor = (fila, col) (ambas en el intervalo [0, 8]).
void completarSimples(tTableroSudoku& tablero); //En cada casilla que  tiene  un  único  valor  posible  se  pone  dicho  valor  y  se  actualizan  convenientemente  los  valores  posibles  de  las  casillas  que  puedan  verse  afectadas.También se debe actualizar el número de casillas vacías.
int numVacias(const tTableroSudoku& tablero); //Devuelve el número  de casillas vacías del tablero dado.
void cargarCandidatos(tTableroSudoku& tablero, tCoor cor); //Recibe el tablero y unas coordenadas, lee para dichas coordenadas los posibles valores candidatos.

#endif