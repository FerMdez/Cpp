#include "ListaEnvios.h"
using namespace std;

bool cargar(tListaEnvios& lista) {
	bool carga = false;
	ifstream archivo;
	int numEnvios = 0;

	lista.cont = 0;

	archivo.open("tienda.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar la tienda." << endl;
	}
	else {
		archivo >> numEnvios;
		while (!archivo.fail() && lista.cont < numEnvios) {
			lista.envio[lista.cont] = new tEnvio;
			if (cargar(*lista.envio[lista.cont], archivo)) {
				lista.cont++;
			}
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void mostrar(tListaEnvios& lista) {
	for (int i = 0; i < lista.cont; i++){
		mostrar(*lista.envio[i]);
	}
}

void ordenarPorCliente(tListaEnvios& lista) {

}

void ordenarPorCiudad(tListaEnvios& lista) {

}

void destruir(tListaEnvios& lista) {
	for (int i = 0; i < lista.cont; i++){
		destruir(*lista.envio[i]);
		delete lista.envio[i];
	}
}