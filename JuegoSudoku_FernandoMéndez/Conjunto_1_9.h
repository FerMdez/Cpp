//Sudoku - Fernando Méndez Torrubiano
#ifndef H_CONJUNTO_1_9_H
#define H_CONJUNTO_1_9_H
#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "checkML.h"

//Constantes:
const int MAX_INTERVALOS = 9; 

//Tipos:
typedef struct tConjunto_1_9 {
	bool boleano[MAX_INTERVALOS];
	int cardinal;
};

//Funciones:
void iniVacio(tConjunto_1_9& c); //Inicializa c al conjunto vacío.
void iniLLeno(tConjunto_1_9& c); //Inicializa c al conjunto formado por todos los enteros del intervalo [1, 9].
bool pertenece(const tConjunto_1_9& c, int e); //Devuelve un booleano que indica si el elemento e (nº entero € [1, 9]) se encuentra en el conjunto c.
void incluir(tConjunto_1_9& c, int e); //Mete el elemento e (€ [1, 9]) en  el conjunto c.
void quitar(tConjunto_1_9& c, int e); //Saca el elemento e (€ [1, 9]) del  conjunto c.
int numElems(const tConjunto_1_9& c); //Devuelve el nº de elementos que  hay en el conjunto c.
void mostrar(const tConjunto_1_9& c); //Visualiza  en  la  consola  los  elementos del conjunto c.


#endif