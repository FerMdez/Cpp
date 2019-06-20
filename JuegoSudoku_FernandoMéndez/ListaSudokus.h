//Sudoku - Fernando M�ndez Torrubiano
#ifndef H_LISTASODOKUS_H
#define H_LISTASODOKUS_H
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "RegistroSudoku.h"

//Constantes:

//Tipos:
typedef struct tListaSudokus {
	tRegSudoku registro[MAX_SDK];
	int contador;
};

//Funciones:
void iniciar(tListaSudokus& lista); //Inicializa�lista�a�una�lista�vac�a.
int numElems(const tListaSudokus& lista); //Devuelve�el�n�mero de elementos�de�lista.
bool cargar(tListaSudokus& lista); //Guarda�en�lista�el�contenido�del archivo�registroSudokus.txt,�devuelve�un�booleano�que�indica�si�la�carga�se ha�podido�realizar.
void mostrar(const tListaSudokus& lista); //Visualiza�por�pantalla�la�informaci�n�de�los�sudokus�de�la�lista�dada.
bool guardar(const tListaSudokus& lista); //Almacena�en�el�archivo registroSudokus.txt�el�contenido�de�lista�y�devuelve�un�valor�booleano indicando�si�la�acci�n�fue�posible.Debe�respetar�el�formato�indicado�para�el� archivo.
bool buscar(const tListaSudokus& lista, std::string nombArch); //Busca en�lista�el�fichero�nombArch;�devuelve�true�si�est�en�la�lista;�y�false�en otro�caso.
bool insertar(tListaSudokus& lista, const tRegSudoku& sudoku); //Si�no�existe�un�sudoku�en�lista�con�igual�nombre�de�fichero�lo�inserta�en�la�posici�n�adecuada�respetando�el�orden�existente.Se�devuelve�un�booleano�que indica�si�se�pudo�a�adir, para�lo�cual�tambi�n�hay�que�tener�en�cuenta�si�la�lista� est�o�no�llena.Debe�implementarse�una�inserci�n�ordenada.

#endif