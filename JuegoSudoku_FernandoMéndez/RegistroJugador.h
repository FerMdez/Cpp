//Sudoku - Fernando Méndez Torrubiano
#ifndef H_REGISTROJUGADOR_H
#define H_REGISTROJUGADOR_H
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "checkML.h"

//Constantes:


//Tipos:
typedef struct tRegJugador {
	std::string id;
	int puntos;
};

//Funciones:
void iniciar(tRegJugador& jugador, std::string id, int puntos); //Inicia jugador con los datos id y puntos.
void mostrar(const tRegJugador& jugador); //Visualiza en la consola la información del registro dado.
void actualizar(tRegJugador& jugador, int puntos); //Añade puntos a los puntos que lleva conseguidos el jugador dado.
bool operator<(const tRegJugador& regIzq, const tRegJugador& regDer); //Sobrecarga  del  operador < para  datos  del  tipo  tRegJugador  comparando en base al identificador.
bool menorXRanking(const tRegJugador& jug1, const tRegJugador& jug2); //Devuelve true si el jugador jug1 tiene menos puntos que el jugador jug2, o si tienen los mismos puntos pero el identificador del jugador jug2 es menor que el del jugador jug1; false en caso contrario.

#endif