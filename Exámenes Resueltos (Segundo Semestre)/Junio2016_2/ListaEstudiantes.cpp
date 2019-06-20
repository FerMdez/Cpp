#include "ListaEstudiantes.h"
using namespace std;

bool cargar(tListaEstudiantes& lista, ifstream& archivo, int& numAlumnos) {
	bool carga = false;
	lista.estudiante = new tEstudiante[numAlumnos];
	lista.cont = 0;

	if (insertar(lista, numAlumnos, archivo)) {
		carga = true;
	}

	return carga;
}

bool buscar(tListaEstudiantes& lista, std::string NIF, int& ini, int& fin, int& pos) {
	bool encontrado = false;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (NIF < lista.estudiante[pos].NIF) {
			fin = pos - 1;
			encontrado = buscar(lista, NIF, ini, fin, pos);
		}
		else if (lista.estudiante[pos].NIF < NIF) {
			ini = pos + 1;
			encontrado = buscar(lista, NIF, ini, fin, pos);
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}

bool insertar(tListaEstudiantes& estudiante, int& numAlumnos, ifstream& archivo) {
	bool insertado = false;
	int ini = 0, fin = estudiante.cont - 1, pos = 0;

	for (int i = 0; i < numAlumnos; i++) {
		if (!buscar(estudiante, estudiante.estudiante[estudiante.cont].NIF, ini, fin, pos)) {
			for (int i = estudiante.cont; i > 0; i--){
				estudiante.estudiante[i] = estudiante.estudiante[i - 1];
			}
			if (cargar(estudiante.estudiante[pos], archivo)) {
				estudiante.cont++;
				insertado = true;
			}
		}
	}
	return insertado;
}

void mostrar(tListaEstudiantes& estudiante) {
	for (int i = 0; i < estudiante.cont; i++){
		mostrar(estudiante.estudiante[i]);
	}
}

void destruir(tListaEstudiantes& estudiantes) {
	delete[] estudiantes.estudiante;
}
