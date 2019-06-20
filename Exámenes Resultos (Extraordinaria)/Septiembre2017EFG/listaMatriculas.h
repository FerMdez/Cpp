#ifndef _LISTAMATRICULAS
#define _LISTAMATRICULAS

#include "listaAsignaturas.h"

//Constantes:
const int MAX_MATRICULAS = 50;

//Tipos:
typedef struct tMatricula {
	std::string apellido, nombre, nif, tipo;
	tListaAsignaturas asignaturas;
	double coste;
};

typedef struct tListaMatriculas {
	tMatricula *matriculas[MAX_MATRICULAS]; //Ordenada por apellidos de menor a mayor.
	int cont;
};

//Funciones:
bool cargarMatriculas(tListaMatriculas& lista); //matriculas.txt
bool insertarMatricula(tListaMatriculas& lista, tMatricula& aux); //Inserción ordenada.
void mostrarMatriculas(tListaMatriculas& lista);
void seleccionarMatricula(tListaMatriculas& lista, int& linea);
void liberar(tListaMatriculas& lista);

#endif // !_LISTAMATRICULAS
