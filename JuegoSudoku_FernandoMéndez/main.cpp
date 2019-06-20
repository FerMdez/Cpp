//Sudoku - Fernando Méndez Torrubiano
#include "juegoSudoku.h"
#include "ListaSudokus.h"
#include "ListaJugadores.h"
#include "UtilidadesWin.h"
#include <iomanip>
using namespace std;

//Funciones: 
char menu();
void ejecutarMenu(tListaSudokus&, tListaJugadores&);

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.

	tListaSudokus lista;
	tListaJugadores listaJug;
	castellano();

	if ((cargar(listaJug)) && (cargar(lista))) {
		ejecutarMenu(lista, listaJug);
	}
	else {
		cout << "Fin del programa." << endl;
	}
	if ((guardar(lista)) && (guardar(listaJug))) {
		cout << "Guardado correctamente." << endl;
	}
	else {
		cout << "Error al guardar el archivo." << endl;
	}
	liberar(listaJug);
	pausa();

	cout << "Good bye :3" << endl;
	return 0;
}

void ejecutarMenu(tListaSudokus& lista, tListaJugadores& listaJug) {
	tRegSudoku sudoku;
	tRegJugador jugador;
	char opc = '1';
	int numSudo = 0, puntos = 0;

	do {
		clear();
		opc = menu();
		switch (opc){
		case '1':
			mostrar(lista);
			do {
				cout << "Introduce el número de sudoku al que deseas jugar ('0' para abortar): ";
				cin >> numSudo;
			} while (numSudo < 0 || numSudo > lista.contador);
			if (numSudo != 0) {
				iniciar(sudoku, lista.registro[numSudo - 1].nomTablero, lista.registro[numSudo - 1].puntos);
				puntos = jugar(sudoku);
				cout << "Juego finalizado. Puntos: " << puntos << endl;
				if (puntos != 0) {
					cout << endl << "Introduzca su ID de usuario: ";
					cin >> jugador.id;
					jugador.puntos = puntos;
					actualizar(listaJug, jugador);
				}
			}
			pausa();
			break;
		case '2': mostrar(listaJug); pausa(); break;
		case '3': mostrarXRanking(listaJug); pausa(); break;
		case '4': 
			mostrar(lista);
			cout << "Introduzca el nombre del sudoku a insertar: ";
			cin >> sudoku.nomTablero; 
			cout << "Introduzca la puntuación del sudoku: ";
			cin >> sudoku.puntos;
			insertar(lista, sudoku); 
			pausa();
			break;
		case '0':
			break;
		default:
			break;
		}
	} while (opc != '0');
}

char menu() {
	//Parámetros: no tiene.
	//Devuelve: la opción del menú elegida por el usuario.

	char opc = '1';

	cout << "<" << setfill(char('-')) << setw(25) << "Menu" << setw(22) << ">" << "\n" << setfill(char(0));
	cout << "1 - Jugar" << endl;
	cout << "2 - Ver jugadores ordenados por identificador." << endl;
	cout << "3 - Ver jugadores ordenados por puntos." << endl;
	cout << "4 - Incorporar sudoku." << endl;
	cout << "0 - Salir" << endl;
	cout << "<" << setfill(char('-')) << setw(47) << ">" << "\n" << setfill(char(0));
	cout << endl;

	cout << "Seleccione una opcion del menu: ";
	cin >> opc;
	while (opc != '0' && opc != '1' && opc != '2' && opc != '3' && opc != '4') {
		cout << "Seleccione una opción del menu (entre 0 y 4): ";
		cin >> opc;
	}

	return opc;
}