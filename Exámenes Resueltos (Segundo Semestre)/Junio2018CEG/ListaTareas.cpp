#include "ListaTareas.h"
using namespace std;

bool cargarPrioridades(tPrioridades& prioridad) {
	bool carga = false;
	ifstream archivo;

	archivo.open("prioridades.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar las prioridades." << endl;
	}
	else {
		for (int i = 0; i < ANIOS; i++) {
			for (int j = 0; j < MAX_TIPOS; j++){
				archivo >> prioridad[i][j];
			}
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

bool cargarTareas(tListaTareas& lista, tPrioridades& prioridades, ifstream& archivo) {
	bool carga = false;
	
	if (!archivo.fail()) {
		archivo >> lista.tarea[lista.cont].codigo;
		archivo.ignore();
		getline(archivo, lista.tarea[lista.cont].descripcion);
		lista.tarea[lista.cont].tiempo = calcularTiempo(lista, prioridades);
		carga = true;
	}
	
	return carga;
}

int calcularTiempo(tListaTareas& lista, tPrioridades& prioridades) {
	int tiempo = 0;

	for (int i = 0; i < ANIOS; i++){
		for (int j = 0; j < MAX_TIPOS; j++){
			tiempo += prioridades[i][j];
		}
	}
	tiempo /= (ANIOS*MAX_TIPOS);
	tiempo *= 20;

	floor(tiempo);

	return tiempo;
}

void mostrarTareas(tListaTareas& lista) {
	for (int i = 0; i < lista.cont; i++){
		cout << right << setw(2) << lista.tarea[i].codigo
			<< setw(40) << lista.tarea[i].descripcion
			<< setw(5) << lista.tarea[i].tiempo << endl;
	}
}