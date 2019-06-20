#include "ListaContratos.h"
using namespace std;

//Funciones auxiliares:
bool buscar(tListaContratos& lista, string& nif, int& ini, int& fin, int& pos);

bool cargarContratos(tListaContratos& lista, tPrioridades& prioridades) {
	bool carga = false;
	ifstream archivo;
	int numContratos = 0;

	lista.cont = 0;

	archivo.open("contratos.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar los contratos." << endl;
	}
	else {
		archivo >> numContratos;
		archivo.ignore();
		while(!archivo.fail() && lista.cont < numContratos){
			lista.contrato[lista.cont] = new tContrato;
			if (insertarContrato(lista, prioridades, archivo)) {
				lista.cont++;
			}
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

bool insertarContrato(tListaContratos& lista, tPrioridades& prioridades, ifstream& archivo) {
	bool insertado = false;
	int ini = 0, fin = lista.cont - 1, pos = 0, numTareas = 0;

	if (!buscar(lista, lista.contrato[lista.cont]->nif, ini, fin, pos)) {
		getline(archivo, lista.contrato[lista.cont]->nombre);
		archivo >> lista.contrato[lista.cont]->nif;
		archivo >> lista.contrato[lista.cont]->sueldo;
		archivo >> numTareas;
		lista.contrato[lista.cont]->lista.cont = 0;
		while (!archivo.fail() && lista.contrato[lista.cont]->lista.cont < numTareas) {
			if (cargarTareas(lista.contrato[lista.cont]->lista, prioridades, archivo)) {
				lista.contrato[lista.cont]->lista.cont++;
			}
		}
		insertado = true;
	}

	return insertado;
}

//
bool buscar(tListaContratos& lista, string& nif, int& ini, int& fin, int& pos) {
	bool encontrado = false;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (nif < lista.contrato[pos]->nif) {
			fin = pos - 1;
			encontrado = buscar(lista, lista.contrato[lista.cont]->nif, ini, fin, pos);;
		}
		else if (lista.contrato[pos]->nif < nif) {
			ini = pos + 1;
			encontrado = buscar(lista, lista.contrato[lista.cont]->nif, ini, fin, pos);;
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}
//

void mostrarContratos(tListaContratos& lista) {
	for (int i = 0; i < lista.cont; i++){
		cout << right << setw(3) << i + 1 << ".-"
			<< setw(30) << lista.contrato[i]->nombre
			<< setw(15) << lista.contrato[i]->nif
			<< setw(5) << "(" << lista.contrato[i]->lista.cont << ")"
			<< setw(10) << fixed << setprecision(2) << lista.contrato[i]->sueldo << endl;
	}
}

int seleccionarContratos(tListaContratos& lista) {
	int linea = 0;

	mostrarContratos(lista);
	cout << endl << "Introduzca el número la linea del contrato que desea seleccionar: ";
	cin >> linea;
	linea--;

	return linea;
}

void liberar(tListaContratos& lista) {
	for (int i = 0; i < lista.cont; i++){
		delete lista.contrato[i];
	}
}