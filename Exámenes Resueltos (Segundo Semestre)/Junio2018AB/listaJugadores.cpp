#include "listaJugadores.h"
using namespace std;

//Funciones auxiliares:
bool buscarBinaria(tListaJugadores& jugadores, std::string nombre, int& ini, int& fin, int& pos);

void iniciar(tListaJugadores& lista) {
	lista.cont = 0;
	lista.capacidad = 10;
	lista.jugador = new tJugador*[lista.capacidad];
}

bool cargarJugadores(tListaJugadores& lista, ifstream& archivo) {
	bool carga = false;
	//ifstream archivo;

	iniciar(lista);

	//archivo.open(nomArchivo);
	//if (!archivo.is_open()) {
	//	cout << "Error al cargar la lista de jugadores." << endl;
	//}
	//else {
		while (!archivo.fail()) {
				lista.jugador[lista.cont] = new tJugador;
				archivo >> lista.jugador[lista.cont]->nombre;
				archivo >> lista.jugador[lista.cont]->puntos;
				lista.cont++;
		}
		lista.cont--;
		carga = true;
	//}
	//archivo.close();

	return carga;
}

bool guardarJugadores(tListaJugadores& lista, ofstream& archivo) {
	bool guardado = false;
	//ofstream archivo;

	//archivo.open(nomArchivo);
	//if (!archivo.is_open()) {
	//	cout << "No se pueden guardar los jugadores." << endl;
	//}
	//else {
		for (int i = 0; i < lista.cont; i++){
			archivo << lista.jugador[i]->nombre << " "
				<< lista.jugador[i]->puntos << endl;
		}
	//}
	//archivo.close();

	return guardado;
}

void mostrarJugadores(const tListaJugadores& jugadores) {
	for (int i = 0; i < jugadores.cont; i++) {
		cout << right << setw(15) << jugadores.jugador[i]->nombre
			<< setw(5) << jugadores.jugador[i]->puntos << endl;
	}
	system("PAUSE");
}

bool buscar(tListaJugadores& jugadores, std::string nombre, int& pos) {
	bool encontrado = false;
	int ini = 0, fin = jugadores.cont - 1;
	pos = 0;

	encontrado = buscarBinaria(jugadores, nombre, ini, fin, pos);

	return encontrado;
}

bool buscarBinaria(tListaJugadores& jugadores, std::string nombre, int& ini, int& fin, int& pos) {
	bool encontrado = false;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (nombre < jugadores.jugador[pos]->nombre) {
			fin = pos - 1;
			encontrado = buscarBinaria(jugadores, nombre, ini, fin, pos);
		}
		else if (jugadores.jugador[pos]->nombre < nombre) {
			ini = pos + 1;
			encontrado = buscarBinaria(jugadores, nombre, ini, fin, pos);
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}

void actualizarPuntuacion(tListaJugadores& jugadores, string nombre, int puntos) {
	int pos = 0;

	if (!buscar(jugadores, nombre, pos)) {
		for (int i = jugadores.cont; i >= pos; i--) {
			jugadores.jugador[i] = jugadores.jugador[i - 1];
		}
		jugadores.cont++;
		jugadores.jugador[pos] = new tJugador;
	}
	jugadores.jugador[pos]->nombre = nombre;
	jugadores.jugador[pos]->puntos = puntos;
}

void mostrarPorPuntos(const tListaJugadores& lista) {
	int cont;
	tListaJugadores aux;

	aux.cont = lista.cont + 1;
	aux.capacidad = lista.capacidad;
	aux.jugador = new tJugador*[aux.capacidad];
	
	for (int i = 0; i < lista.cont; i++){
		cont = i;
		aux.jugador[i] = lista.jugador[i];
		while (cont > 0 && aux.jugador[cont - 1]->puntos < aux.jugador[cont]->puntos) {
			aux.jugador[aux.cont] = aux.jugador[cont];
			aux.jugador[cont] = aux.jugador[cont - 1];
			aux.jugador[cont - 1] = aux.jugador[aux.cont];
			cont--;
		}
	}

	aux.cont = lista.cont;
	mostrarJugadores(aux);

	delete[] aux.jugador;
}

void liberar(tListaJugadores& jugadores) {
	for (int i = 0; i < jugadores.cont; i++){
		delete jugadores.jugador[i];
	}
	delete[] jugadores.jugador;
}