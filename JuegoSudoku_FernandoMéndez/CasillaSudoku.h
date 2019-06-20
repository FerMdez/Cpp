//Sudoku - Fernando Méndez Torrubiano
#ifndef H_CASILLASODOKU_H
#define H_CASILLASODOKU_H
#pragma once

#include <iostream>
#include <string>
#include "Conjunto_1_9.h"
#include "UtilidadesWin.h"

//Constantes:

//Tipos:
typedef enum tEstadoCasilla { vacia = 0, fija = 1, rellena = 4};
typedef struct tCasillaSudoku {
	tEstadoCasilla estado; //Estado de la casilla.
	int numero; //Número que contiene (en caso de NO estar vacía).
	tConjunto_1_9 posibles; //Conjunto de posibles números válidos para esa casilla.
};

//Funciones:
void iniciar(tCasillaSudoku& casilla, int numero, tEstadoCasilla estado); //Inicializa el estado de la casilla dada a estado, su número a numero  y su conjunto de candidatos al conjunto { 1,2,3,4,5,6,7,8,9 }.
bool actualizar(tCasillaSudoku& casilla, int  numero, tEstadoCasilla estado); //Modifica el estado y el nº de casilla si el estado actual de la casilla no es fija y numero es un candidato, en otro caso devuelve false.
bool actualizarSimple(tCasillaSudoku& casilla); //Si la casilla está vacía y tiene un único candidato, rellena la casilla con dicho valor, en otro  caso devuelve false.
void mostrar(const tCasillaSudoku& casilla); //Muestra en la consola  la casilla dada, utilizando distintos colores de fondo.Se mostrarán sobre fondo  azul las casillas fijas y sobre fondo rojo las casillas rellenas.El resto, sobre el fondo negro por defecto.

#endif