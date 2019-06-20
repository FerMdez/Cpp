#include "ListaContactos.h"
using namespace std;

bool cargar(tListaContactos& lista) {
	bool carga = false;
	ifstream archivo;
	int numContactos;

	lista.cont = 0;

	archivo.open("contactos.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar los contactos." << endl;
	}
	else {
		archivo >> numContactos;
		archivo.ignore();
		while (!archivo.fail() && lista.cont < numContactos) {
			lista.contacto[lista.cont] = new tContacto;
			if (cargar(*lista.contacto[lista.cont], archivo)) {
				lista.cont++;
			}
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void destruir(tListaContactos& lista) {
	for (int i = 0; i < lista.cont; i++){
		delete lista.contacto[i];
	}
}