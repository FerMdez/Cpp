#include "ListaGrupos.h"
using namespace std;

bool cargar(tListaGrupos& grupos) {
	bool carga = false;
	ifstream archivo;
	int numAlum = 0;

	grupos.cont = 0;

	archivo.open("notas.txt");
	if (!archivo.is_open()) {
		cout << "No se ha podido cargar las notas." << endl;
	}
	else {
		while (!archivo.fail()) {
			grupos.grupo[grupos.cont] = new tGrupo;
			archivo >> grupos.grupo[grupos.cont]->id;
			archivo >> numAlum;
			if (cargar(grupos.grupo[grupos.cont]->estudiantes, archivo, numAlum)) {
				grupos.cont++;
				carga = true;
			}
		}
	}
	archivo.close();

	return carga;
}

void mostrar(tListaGrupos& grupos) {
	cout << setfill(char('-')) << setw(50) << "\n" << setfill(char(0));
	for (int i = 0; i < grupos.cont; i++){
		cout << "GRUPO: " << grupos.grupo[i]->id << endl;
		mostrar(grupos.grupo[i]->estudiantes);
		cout << setfill(char('-')) << setw(50) << "\n" << setfill(char(0));
	}
}

bool buscar(tListaGrupos& grupos, std::string NIF, int& i) {
	bool encontrado = false, busqueda = false;
	int ini = 0, fin = grupos.grupo[i]->estudiantes.cont - 1, pos = 0;
	
	if (!busqueda && i < grupos.cont) {
		encontrado = buscar(grupos.grupo[i]->estudiantes, NIF, ini, fin, pos);
		if (encontrado) {
			busqueda = true;
		}
		else {
			i++;
			busqueda = buscar(grupos, NIF, i);
		}
	}
	return busqueda;
}

void destruir(tListaGrupos grupos) {
	for (int i = 0; i <= grupos.cont; i++){
		destruir(grupos.grupo[i]->estudiantes);
		delete grupos.grupo[i];
	}
}