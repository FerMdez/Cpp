//Sudoku - Fernando Méndez Torrubiano
#include "TableroSudoku.h"
using namespace std;

bool cargar(tTableroSudoku& tablero, string nombreFichero) {
	bool carga = false;
	ifstream archivo;
	char ch; int num;
	tablero.numVacias = 0;

	archivo.open(nombreFichero);
	if (!archivo.is_open()) {
		carga = false;
	}
	else {
		for (int i = 0; i < MAXDIM; i++) {
			for (int j = 0; j <= MAXDIM; j++) {
				if (j != MAXDIM) {
					archivo.get(ch);
					switch (ch) {
					case ' ': iniciar(tablero.casilla[i][j], 0, vacia); tablero.numVacias++; break;
					default: num = (int)ch - 48; iniciar(tablero.casilla[i][j], num, fija); break;
					}
				}
				else {
					archivo.get(ch);
				}
			}
		}
		carga = true;
	}

	return carga;
}

void mostrar(const tTableroSudoku& tablero) {

	for (int i = 0; i < MAXDIM; i++){
		if (i % 3 == 0) {
			cout << setfill('-') << setw(32) << "\n" << setfill(char(0));
		}
		for (int j = 0; j < MAXDIM; j++){
			if ((j % 3 == 0)) {
				cout << "|";
			}
			mostrar(tablero.casilla[i][j]);
		}
		cout << "|" << "\n";
	}
	cout << setfill('-') << setw(32) << "\n" << setfill(char(0));

}

bool actualizar(tTableroSudoku& tablero, tCoor cor, int num) {
	bool actualizado = false;

	if ((tablero.casilla[cor.fila][cor.col].estado != fija) && (pertenece(tablero.casilla[cor.fila][cor.col].posibles, num))) {
		actualizar(tablero.casilla[cor.fila][cor.col], num, rellena);
		actualizado = true;
		tablero.numVacias--;
	}

	return actualizado;
}

bool borrar(tTableroSudoku& tablero, tCoor cor) {
	bool borrado = false;

	if ((tablero.casilla[cor.fila][cor.col].numero != 0) && (tablero.casilla[cor.fila][cor.col].estado != fija)) {
		borrado = true;
		incluir(tablero.casilla[cor.fila][cor.col].posibles, tablero.casilla[cor.fila][cor.col].numero);
		tablero.casilla[cor.fila][cor.col].numero = 0;
		tablero.casilla[cor.fila][cor.col].estado = vacia;
		tablero.numVacias++;
	}
	
	return borrado;
}

void mostrarCandidatos(const tTableroSudoku& tablero, tCoor cor) {

	if ((tablero.casilla[cor.fila][cor.col].estado == vacia) || (tablero.casilla[cor.fila][cor.col].estado == rellena)) {
			cout << "CANDIDATOS:";
			mostrar(tablero.casilla[cor.fila][cor.col].posibles);
	}
	else {
		cout << "La casilla está fija." << endl;
	}
	cout << endl;
}

void cargarCandidatos(tTableroSudoku& tablero, tCoor cor) {

	//FILAS:
	for (int i = 0; i < MAXDIM; i++) {
		if (tablero.casilla[cor.fila][i].estado != vacia) {
			quitar(tablero.casilla[cor.fila][cor.col].posibles, tablero.casilla[cor.fila][i].numero);
		}
	}

	//COLUMNAS:
	for (int i = 0; i < MAXDIM; i++) {
		if (tablero.casilla[i][cor.col].estado != vacia) {
			quitar(tablero.casilla[cor.fila][cor.col].posibles, tablero.casilla[i][cor.col].numero);
		}
	}

	//SUBCUADRADO:
	int iniFil = (cor.fila / 3) * 3;
	int finFil = iniFil + 3;
	int iniCol = (cor.col / 3) * 3;
	int finCol = iniCol + 3;

	for (int i = iniFil; i < finFil; i++) {
		for (int j = iniCol; j < finCol; j++) {
			if (tablero.casilla[i][j].estado != vacia) {
				quitar(tablero.casilla[cor.fila][cor.col].posibles, tablero.casilla[i][j].numero);
			}
		}
	}

}

void completarSimples(tTableroSudoku& tablero) {
	for (int i = 0; i < MAXDIM; i++){
		for (int j = 0; j < MAXDIM; j++){
			if (actualizarSimple(tablero.casilla[i][j])) {
				tablero.numVacias--;
			}
		}
	}
}

int numVacias(const tTableroSudoku& tablero) {
	int numV = tablero.numVacias;

	return numV;
}