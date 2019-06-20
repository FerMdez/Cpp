#include "ListaTemas.h"
using namespace std;

bool cargar(tListaTemas& lista) {
	bool carga = false;
	ifstream archivo;
	int numTemas = 0;

	lista.cont = 0;

	archivo.open("temas.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar los temas." << endl;
	}
	else {
		archivo >> numTemas;
		while (!archivo.fail() && lista.cont < numTemas) {
			lista.tema[lista.cont] = new tTema;
			if (cargar(*lista.tema[lista.cont], archivo)) {
				lista.cont++;
			}
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void destruir(tListaTemas& lista) {
	for (int i = 0; i < lista.cont; i++){
		delete lista.tema[i];
	}
}