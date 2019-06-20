//Sudoku - Fernando Méndez Torrubiano
#include "CasillaSudoku.h"
using namespace std;

void iniciar(tCasillaSudoku& casilla, int numero, tEstadoCasilla estado) {
	casilla.estado = estado;
	casilla.numero = numero;
	iniLLeno(casilla.posibles);
}

bool actualizar(tCasillaSudoku & casilla, int numero, tEstadoCasilla estado) {
	bool actualizado = false;

	if (estado != fija) {
		if (pertenece(casilla.posibles, numero)) {
			casilla.numero = numero;
			casilla.estado = estado;
			actualizado = true;
		}
	}

	return actualizado;
}

bool actualizarSimple(tCasillaSudoku& casilla) {
	bool actualizado = false;

	if (casilla.estado == vacia) {
		if (numElems(casilla.posibles) == 1) {
			for (int i = 0; i <= MAX_INTERVALOS; i++){
				if (pertenece(casilla.posibles, i)) {
					casilla.numero = i;
				}
			}
			casilla.estado = rellena;
			iniVacio(casilla.posibles);
			actualizado = true;
		}
	}
	return actualizado;
}

void mostrar(const tCasillaSudoku& casilla) {

	cout << "  ";
	colorFondo(casilla.estado); 
	if (casilla.estado == vacia) { cout << " "; }
	else { cout << casilla.numero; }
	colorFondo(0);

}