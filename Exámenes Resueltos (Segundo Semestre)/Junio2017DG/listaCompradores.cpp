#include "listaCompradores.h"
using namespace std;

void iniciar(tListaComprador & lista){
	lista.capacidad = 10;
	lista.cont = 0;
	lista.comprador = new tComprador*[lista.capacidad];
}

bool insertar(tListaComprador& lista, tComprador& comprador){
	bool insertado = false;
	int pos = 0;

	if(!buscar(lista, comprador, pos)){
		lista.comprador[lista.cont] = new tComprador;
		lista.comprador[lista.cont]->id = comprador.id;
		lista.comprador[lista.cont]->importe = comprador.importe;
		lista.cont++;
		insertado = true;
	}
	else {
		lista.comprador[pos]->importe += comprador.importe;
	}

	return insertado;
}

bool buscar(tListaComprador & lista, tComprador& comprador, int& pos){
	bool encontrado = false;

	while (!encontrado &&  pos < lista.cont) {
		if (lista.comprador[pos]->id == comprador.id) {
			encontrado = true;
		}
		else {
			pos++;
		}
	}

	return encontrado;
}

void mostrar(tListaComprador & lista){
	for (int i = 0; i < lista.cont; i++){
		cout << right << setw(10) << "Comprador: " << lista.comprador[i]->id
			<< setw(10) << "Total: " << lista.comprador[i]->importe << endl;
	}
}

void liberar(tListaComprador & lista){
	for (int i = 0; i < lista.cont; i++){
		delete lista.comprador[i];
	}

	delete[] lista.comprador;
}
