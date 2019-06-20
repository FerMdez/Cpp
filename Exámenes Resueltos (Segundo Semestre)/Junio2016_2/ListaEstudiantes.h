#ifndef _LISTAESTUDIANTES
#define _LISTAESTUDIANTES

#include "Estudiante.h"

//Constantes:


//Tipos:
typedef struct tListaEstudiantes {
	tEstudiante *estudiante;	//Ordenada por NIF.
	int cont;
};


//Funciones:
bool cargar(tListaEstudiantes& lista, std::ifstream& archivo, int&);
bool buscar(tListaEstudiantes& lista, std::string NIF, int& ini, int& fin, int& pos); //Binaria y recursiva.
bool insertar(tListaEstudiantes& estudiante, int&, std::ifstream&);
void mostrar(tListaEstudiantes& estudiante);
void destruir(tListaEstudiantes& estudiantes);


#endif // !_LISTAESTUDIANTES
