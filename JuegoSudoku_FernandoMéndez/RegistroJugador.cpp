//Sudoku - Fernando Méndez Torrubiano
#include "RegistroJugador.h"
using namespace std;

void iniciar(tRegJugador& jugador, std::string id, int puntos) {
	jugador.id = id;
	jugador.puntos = puntos;
}

void mostrar(const tRegJugador& jugador) {
	cout << right << setw(15) << jugador.id << setw(10) << jugador.puntos << endl;
}

void actualizar(tRegJugador& jugador, int puntos) {
	jugador.puntos += puntos;
}

bool operator<(const tRegJugador& regIzq, const tRegJugador& regDer) {
	tRegJugador regIzqMinus, regDerMinus;

	for (int i = 0; i < regIzq.id.length(); i++) {
		regIzqMinus.id += tolower(regIzq.id[i]);
	}
	for (int i = 0; i < regDer.id.length(); i++) {
		regDerMinus.id += tolower(regDer.id[i]);
	}

	return (regIzqMinus.id < regDerMinus.id);
}

bool menorXRanking(const tRegJugador& jug1, const tRegJugador& jug2) {
	bool menor = false;

	if (jug1.puntos == jug2.puntos) {
		if (jug2 < jug1) { //!operator<(jug1, jug2) || operator(jug2, jug1)
			menor = true;
		}
	}
	else {
		if ((jug1.puntos < jug2.puntos)) {
			menor = true;
		}
	}

	return menor;
}