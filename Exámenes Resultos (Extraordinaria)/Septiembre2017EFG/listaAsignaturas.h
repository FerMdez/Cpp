#ifndef _LISTAASIGNATURAS
#define _LISTAASIGNATURAS

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

//Constantes:
const int MAX_ASIGNATURAS = 30;

//Tipos:
typedef struct tAsignatura {
	std::string codigo, nombre;
	int creditos;
};

typedef struct tListaAsignaturas{ //NO ORDENADA
	tAsignatura asignatura[MAX_ASIGNATURAS];
	int cont;
};

//Funciones:
bool cargarAsignaturas(tListaAsignaturas& lista, std::ifstream& archivo); //matriculas.txt
void insertarAsignatura(tListaAsignaturas& lista, std::ifstream& archivo);


#endif // !_LISTAASIGNATURAS
