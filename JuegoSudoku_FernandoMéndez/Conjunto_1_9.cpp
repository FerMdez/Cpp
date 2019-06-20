//Sudoku - Fernando Méndez Torrubiano
#include "Conjunto_1_9.h"
using namespace std;

void iniVacio(tConjunto_1_9& c) {

	for (int i = 0; i <= MAX_INTERVALOS; i++) {
		c.boleano[i] = false;
	}
	c.cardinal = 0;
}

void iniLLeno(tConjunto_1_9& c) {

	for (int i = 0; i <= MAX_INTERVALOS; i++) {
		c.boleano[i] = true;
	}
	c.cardinal = MAX_INTERVALOS;
}

bool pertenece(const tConjunto_1_9& c, int e) {
	bool encontrado = false;

	if (c.boleano[e - 1] == true) {
		encontrado = true;
	}

	return encontrado;

}

void incluir(tConjunto_1_9& c, int e) {

	if ((c.cardinal < MAX_INTERVALOS)) {
		c.boleano[e - 1] = true;
		c.cardinal++;
	}

}

void quitar(tConjunto_1_9& c, int e) {

	if (pertenece(c, e)) {
		c.boleano[e - 1] = false;
		c.cardinal--;
	}

}

int numElems(const tConjunto_1_9& c) {
	int num = c.cardinal;

	return num;
}

void mostrar(const tConjunto_1_9& c) {

	for (int i = 1; i <= MAX_INTERVALOS; i++){
		if (pertenece(c, i)) {
			cout << right << setw(5) << i;
		}
	}

}