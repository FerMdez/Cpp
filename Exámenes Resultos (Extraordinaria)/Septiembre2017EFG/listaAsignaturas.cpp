#include "listaAsignaturas.h"
using namespace std;

bool cargarAsignaturas(tListaAsignaturas& lista, std::ifstream& archivo) {
	bool carga = false;

	//archivo >> lista.cont;
	insertarAsignatura(lista, archivo);
	if (!archivo.fail()) {
		carga = true;
	}

	return carga;
}

void insertarAsignatura(tListaAsignaturas& lista, std::ifstream& archivo) {
	for (int i = 0; i < lista.cont; i++) {
		archivo >> lista.asignatura[i].codigo;
		archivo.ignore();
		getline(archivo, lista.asignatura[i].nombre);
		archivo >> lista.asignatura[i].creditos;
	}
}