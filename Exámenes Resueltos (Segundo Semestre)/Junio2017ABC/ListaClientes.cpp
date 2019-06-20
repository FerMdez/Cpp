#include "ListaClientes.h"
using namespace std;

void mostrar(tCliente& cliente) {
	cout << setw(10) << cliente.login
		<< setw(15) << cliente.fechaAlta
		<< setw(10) << cliente.edad << setw(2) << "años"
		<< setw(10) << cliente.ciudad << endl;
}

bool cargar(tListaClientes& lista) {
	bool carga = false;
	ifstream archivo;
	int i = 0;

	lista.cont = 0;

	archivo.open("clientes.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar los clientes." << endl;
	}
	else {
		archivo >> i;
		while (!archivo.fail() && lista.cont < i) {
			lista.cliente[lista.cont] = new tCliente;
			archivo >> lista.cliente[lista.cont]->login;
			archivo >> lista.cliente[lista.cont]->fechaAlta;
			archivo >> lista.cliente[lista.cont]->edad;
			archivo >> lista.cliente[lista.cont]->ciudad;
			lista.cont++;
		}
		carga = true;
	}
	
	return carga;
}

void mostrar(tListaClientes& lista, int& i) { //Recursiva.

	if (i < lista.cont) {
		cout << setw(2) << i;
		mostrar(*lista.cliente[i]);
		i++;
		mostrar(lista, i);
	}
}

void liberar(tListaClientes& lista) {
	for (int i = 0; i < lista.cont; i++){
		delete lista.cliente[i];
	}
//	delete[] lista.cliente;
}