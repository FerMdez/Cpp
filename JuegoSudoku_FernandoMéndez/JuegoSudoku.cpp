//Sudoku - Fernando Méndez Torrubiano
#include "JuegoSudoku.h"
using namespace std;

void mostrar(const tJuegoSudoku& juego) {

	mostrar(juego.registro);
	mostrar(juego.tablero);

}

int jugar(const tRegSudoku& sudoku) {
	tJuegoSudoku juego;
	int puntos = 0;
		
	juego.registro.nomTablero = sudoku.nomTablero;
	juego.registro.puntos = sudoku.puntos;
	if (cargar(juego.tablero, sudoku.nomTablero)) {
		clear();
		mostrar(juego);
		ejecutarSubMenu(juego, puntos);
	}
	else {
		cout << "No se ha podido cargar el tablero." << endl;
	}

	return puntos;
}

void ejecutarSubMenu(tJuegoSudoku& juego, int& puntos) {
	tCoor coordenadas;
	char opc = '1';
	int num = 0;
	bool resuelto = false;

	do {
		actulizarCandidatos(juego, coordenadas);
		opc = subMenu();
		switch (opc) {
		case '1':
			pedirCoordenadas(coordenadas);
			mostrarCandidatos(juego.tablero, coordenadas);
			pausa();
			break;
		case '2':
			pedirCoordenadas(coordenadas);
			do {
				cout << endl << "Introduzca un numero [1-9]: ";
				cin >> num;
			} while ((num < 1) || (num > MAXDIM));

			if (actualizar(juego.tablero, coordenadas, num)) {
				cout << "Casilla actualizada correctamente." << endl;
			}
			else {
				cout << "No se ha podido actualizar esa casilla." << endl;
			}
			pausa();
			break;
		case '3':
			pedirCoordenadas(coordenadas);
			if (borrar(juego.tablero, coordenadas)) {
				cout << "Borrado correctamente." << endl;
			}
			else {
				cout << "No se puede borrar esa casilla." << endl;
			}
			pausa();
			break;
		case '4':
			if (cargar(juego.tablero, juego.registro.nomTablero)) {
				cout << "Tablero reiniciado correctamente." << endl;
			}
			pausa();
			break;
		case '5':
			completarSimples(juego.tablero);
			break;
		}

		if (numVacias(juego.tablero) == 0) {
			resuelto = true;
			puntos = juego.registro.puntos;
		}
		clear();
		mostrar(juego);
	} while ((opc != '0') && (!resuelto));
}

char subMenu() {
	char opc = '1';

	cout << endl << "<" << setfill(char('-')) << setw(35) << "OPCIONES DE JUEGO" << setw(18) << ">" << "\n" << setfill(char(0));
	cout << "1 - Ver posibles valores de una casilla vacía" << endl;
	cout << "2 - Colocar valor en una casilla" << endl;
	cout << "3 - Borrar valor de una casilla" << endl;
	cout << "4 - Reiniciar el tablero" << endl;
	cout << "5 - Autocompletar celdas simples" << endl;
	cout << "0 - Abortar la resolución y volver al menú principal" << endl;
	cout << "<" << setfill(char('-')) << setw(53) << ">" << "\n" << setfill(char(0));


	cout << "Seleccione una opcion: ";
	cin >> opc;
	while (opc != '0' && opc != '1' && opc != '2' && opc != '3' && opc != '4' && opc != '5') {
		cout << "Seleccione una opción del menu (entre 0 y 5): ";
		cin >> opc;
	}

	return opc;
}

void pedirCoordenadas(tCoor& coordenadas) {
	do {
		cout << "Introduzca fila [1-9]: ";
		cin >> coordenadas.fila;
	} while ((coordenadas.fila < 1) || (coordenadas.fila > MAXDIM));
	coordenadas.fila -= 1;
	do {
		cout << "Introduzca columna [1-9]: ";
		cin >> coordenadas.col;
	} while ((coordenadas.col < 1) || (coordenadas.col > MAXDIM));
	coordenadas.col -= 1;
}

void actulizarCandidatos(tJuegoSudoku& juego, tCoor& coordenadas) {
	for (int i = 0; i < MAXDIM; i++) {
		for (int j = 0; j < MAXDIM; j++) {
			coordenadas.fila = i;
			coordenadas.col = j;
			cargarCandidatos(juego.tablero, coordenadas);
		}
	}
}