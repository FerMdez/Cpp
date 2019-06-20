//Sudoku - Fernando Méndez Torrubiano
#include "ListaJugadores.h"
using namespace std;

//Funciones auxiliares:
bool busquedaRecursiva(const tListaJugadores& lista, const tRegJugador& jugador, int& pos, int& ini, int& fin); //Función auxiliar para realizar la búsqueda recursiva binaria.


void iniciar(tListaJugadores& lista) {
	lista.capacidad = 3;
	lista.contador = 0;
	lista.jugadores = new tRegJugador*[lista.capacidad];
}

bool cargar(tListaJugadores& lista) {
	bool carga = false;
	ifstream archivo;
	string id = "";
	int puntos = 0;
	
	iniciar(lista);

	archivo.open("registroJugadores.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar la lista de jugadores." << endl;
	}
	else {
		carga = true;
		archivo >> id;
		archivo >> puntos;
		while (!archivo.fail()) {
			if (lista.contador == lista.capacidad) {
				ampliar(lista, lista.capacidad);
			}
			lista.jugadores[lista.contador] = new tRegJugador;
			iniciar(*lista.jugadores[lista.contador], id, puntos);
			lista.contador++;
			archivo >> id;
			archivo >> puntos;
		}
		archivo.close();
	}

	return carga;
}

void mostrar(const tListaJugadores& lista) {
	cout << right << setw(8) << "POSICIÓN" << setw(12) << "JUGADOR" << setw(12) << "PUNTOS" << endl;
	cout << setfill(char('-')) << setw(35) << "\n" << setfill(char(0));
	for (int i = 0; i < lista.contador; i++){
		cout << setw(3) << i + 1 << "." << setw(7);
		mostrar(*lista.jugadores[i]);
	}
	cout << setfill(char('-')) << setw(35) << "\n" << setfill(char(0));
}

bool guardar(const tListaJugadores& lista) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("registroJugadores.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar el registro de jugadores." << endl;
	}
	else {
		for (int i = 0; i < lista.contador; i++){
			archivo << lista.jugadores[i]->id << " ";
			archivo << lista.jugadores[i]->puntos << endl;
		}
		guardado = true;
		archivo.close();
	}

	return guardado;
}

bool buscar(const tListaJugadores& lista, const tRegJugador& jugador, int& pos) {
	bool encontrado = false;
	int ini = 0, fin = lista.contador - 1;

	encontrado = busquedaRecursiva(lista, jugador, pos, ini, fin);

	return encontrado;
}

bool busquedaRecursiva(const tListaJugadores& lista, const tRegJugador& jugador, int& pos, int& ini, int& fin) {
	bool encontrado = false;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (jugador < *lista.jugadores[pos]) { //operator<(jugador, *lista.jugadores[pos])
			fin = pos - 1;
			encontrado = busquedaRecursiva(lista, jugador, pos, ini, fin);
			pos = fin;
		}
		else if (*lista.jugadores[pos] < jugador) { //operator<(*lista.jugadores[pos], jugador)
			ini = pos + 1;
			encontrado = busquedaRecursiva(lista, jugador, pos, ini, fin);
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}

bool actualizar(tListaJugadores& lista, const tRegJugador& jugador) {
	bool actualizado = false;
	int pos = 0;

	if (buscar(lista, jugador, pos)) {
		actualizar(*lista.jugadores[pos], jugador.puntos);
		actualizado = true;
	}
	else {
		if (lista.contador == lista.capacidad) {
			ampliar(lista, lista.capacidad);
		}
		pos++;
		for (int i = lista.contador; i > pos; i--) {
			lista.jugadores[i] = lista.jugadores[i - 1];
		}
		lista.jugadores[pos] = new tRegJugador;
		iniciar(*lista.jugadores[pos], jugador.id, jugador.puntos);
		lista.contador++;
	}

	return actualizado;
}

void mostrarXRanking(const tListaJugadores& lista) {
	tListaJugadores listaXRanking;
	int cont;

	//iniciar(listaXRanking);
	listaXRanking.capacidad = lista.contador + 1;
	listaXRanking.contador = lista.contador;
	listaXRanking.jugadores = new tRegJugador*[listaXRanking.capacidad];

	for (int i = 0; i < lista.contador; i++) {
		cont = i;
		listaXRanking.jugadores[i] = lista.jugadores[i];
		while ((cont > 0) && ((menorXRanking(*listaXRanking.jugadores[cont - 1], *listaXRanking.jugadores[cont])))) {
			listaXRanking.jugadores[listaXRanking.contador] = listaXRanking.jugadores[cont];
			listaXRanking.jugadores[cont] = listaXRanking.jugadores[cont - 1];
			listaXRanking.jugadores[cont - 1] = listaXRanking.jugadores[listaXRanking.contador];
			cont--;
		}
	}

	mostrar(listaXRanking);

	delete[] listaXRanking.jugadores;

}

/*//*/

void ampliar(tListaJugadores& lista, int num) {
	lista.capacidad += num;
	tRegJugador** aux = new tRegJugador*[lista.capacidad];
	for (int i = 0; i < lista.contador; i++) {
		aux[i] = lista.jugadores[i];
	}
	delete[] lista.jugadores;
	lista.jugadores = aux;
}

void liberar(tListaJugadores& lista) {
	for (int i = 0; i < lista.contador; i++){
		delete lista.jugadores[i];
	}

	delete[] lista.jugadores;
}