//Sudoku - Fernando Méndez Torrubiano
#ifndef H_REGISTROSODOKU_H
#define H_REGISTROSODOKU_H
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "checkML.h"

//Constantes:
const int MAX_SDK = 9;

//Tipos:
typedef struct tRegSudoku {
	int puntos;
	std::string nomTablero;
};

//Funciones:
bool cargar(tRegSudoku& sudoku, std::istream& infile); //Lee los datos del siguiente registro del flujo infile en sudoku y devuelve un booleano que indica si la carga se ha podido realizar.
void mostrar(const tRegSudoku& sudoku);  //Visualiza en la consola la información del registro dado.
void iniciar(tRegSudoku& registro, std::string file, int puntos); //Inicia el registro con los datos file y puntos.
bool guardar(const tRegSudoku& registro, std::ostream& outfile); //Almacena en outfile el contenido de registro y devuelve un valor booleano  indicando si la acción fue posible.Debe respetar el formato del archivo.
bool operator<(const tRegSudoku& regIzq, const tRegSudoku& regDer); //Sobrecarga del operador < para datos del tipo tRegSudoku de acuerdo con el orden descrito.

#endif