//Sudoku - Fernando Méndez Torrubiano
#include "UtilidadesWin.h"
using namespace std;

void colorFondo(tColor color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void castellano() {
	system("chcp 1252"); //Así la consola puede imprimir caracteres especiales del español.
}

void pausa() {
	system("PAUSE");
}

void clear() {
	system("cls");
}