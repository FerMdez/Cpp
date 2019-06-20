#include "listaLonja.h"
using namespace std;

//Funciones auxiliares:
bool busquedaRecursiva(tListaLotes & lista, tLotes& nuevo, int& ini, int& fin, int& pos);


void inicializar(tListaLotes & lista){
	lista.cont = 0;
}

int numLotes(tListaLotes & lista){
	return lista.cont;
}

bool insertar(tListaLotes & lista, tLotes& nuevo){
	bool insertado = false;
	int pos = 0;


	if (!buscar(lista, nuevo, pos)) {
		lista.lote[lista.cont] = new tLotes;
		lista.lote[lista.cont]->lote = nuevo.lote;
		lista.lote[lista.cont]->tipo = nuevo.tipo;
		lista.lote[lista.cont]->precio = nuevo.precio;
		lista.lote[lista.cont]->peso = nuevo.peso;
		lista.cont++;
	}
	else {
		lista.lote[lista.cont] = new tLotes;
		for (int i = lista.cont; i > pos; i--){
			lista.lote[i] = lista.lote[i - 1];
		}
		lista.lote[pos]->tipo = nuevo.tipo;
		lista.lote[pos]->lote = nuevo.lote;
		lista.lote[pos]->precio = nuevo.precio;
		lista.lote[pos]->peso = nuevo.peso;
		lista.cont++;
		insertado = true;
	}

	return insertado;
}

bool cargar(tListaLotes & lista){
	bool carga = false;
	ifstream archivo;
	tLotes aux;
	inicializar(lista);

	archivo.open("datos.txt");
	if (!archivo.is_open()) {
		cout << "Error al caragar el archivo." << endl;
	}
	else {
		while (!archivo.fail() && lista.cont < MAX_LOTES) {
			archivo >> aux.lote;
			archivo >> aux.tipo;
			archivo >> aux.precio;
			archivo >> aux.peso;
			if (!archivo.eof()) {
				insertar(lista, aux);
			}
		}
		carga = true;
	}

	return carga;
}

bool buscar(tListaLotes& lista, tLotes& nuevo, int& pos){
	bool encontrado = false;
	int ini = 0, fin = lista.cont - 1;

	encontrado = busquedaRecursiva(lista, nuevo, ini, fin, pos);

	return encontrado;
}

bool busquedaRecursiva(tListaLotes& lista, tLotes& nuevo, int& ini, int& fin, int& pos) {
	bool encontrado = false;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (nuevo < *lista.lote[pos]) {
			fin = pos - 1;
			encontrado = busquedaRecursiva(lista, nuevo, ini, fin, pos);
		}
		else if (*lista.lote[pos] < nuevo){
			ini = pos + 1;
			encontrado = busquedaRecursiva(lista, nuevo, ini, fin, pos);
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}

void obeternerLote(tListaLotes& lista, tLotes* lote, int& pos){
	lote = lista.lote[pos];
}

void mostrar(tListaLotes& lista, tListaComprador& comprador){
	for (int i = 0; i < comprador.cont; i++){
		mostrarPrecio(*lista.lote[i], *comprador.comprador[i]);
	}
}

void liberar(tListaLotes & lista){
	for (int i = 0; i < lista.cont; i++){
		delete lista.lote[i];
	}
}
