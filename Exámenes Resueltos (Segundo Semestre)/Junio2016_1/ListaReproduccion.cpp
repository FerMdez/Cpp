#include "ListaReproduccion.h"
using namespace std;

void nueva(tListaReproduccion& lista) {
	//La capacidad y el nombre se guardan directamente en el main().

	lista.elemento = new tElemento[lista.capacidad];
	lista.cont = 0;
}

bool insertar(tListaReproduccion& lista, tElemento& elemento) {
	bool insertado = false;
	int ini = 0, fin = lista.cont - 1, pos = 0;

	if (!buscar(lista, elemento.puntero[pos].titulo, ini, fin, pos)) {
		lista.elemento[lista.cont].puntero = elemento.puntero;
		lista.elemento[lista.cont].valoracion = elemento.valoracion;
		lista.cont++;
		insertado = true;
	}
	else {
		lista.elemento[pos].puntero = elemento.puntero;
		lista.elemento[pos].valoracion = elemento.valoracion;
	}

	return insertado;
}

bool buscar(tListaReproduccion& lista, std::string titulo, int& ini, int& fin, int& pos) {
	bool encontrado = false;
	
	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (titulo < lista.elemento[pos].puntero->titulo) {
			fin = pos - 1;
			encontrado = buscar(lista, titulo, ini, fin, pos);
		}
		else if (lista.elemento[pos].puntero->titulo < titulo) {
			ini = pos + 1;
			encontrado = buscar(lista, titulo, ini, fin, pos);
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}

void mostrar(tListaReproduccion& lista) {
	cout << "Lista: " << lista.nombreLista << endl;
	for (int i = 0; i < lista.cont; i++){
		cout << i + 1 << ".-";
		mostrar(*lista.elemento[i].puntero);
		cout << " (" << lista.elemento[i].valoracion << ")" << endl;
	}
}

void modificarOrden(tListaReproduccion& lista, int& origen, int& fin) {
	tElemento aux;
	aux = lista.elemento[origen];

	for (int i = origen; i > fin - 1; i--){
		lista.elemento[i] = lista.elemento[i - 1];
	}

	lista.elemento[fin] = aux;
}

void destruir(tListaReproduccion& lista) {
	delete[] lista.elemento;
}