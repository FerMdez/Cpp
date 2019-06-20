//Sudoku - Fernando Méndez Torrubiano
#include "ListaSudokus.h"
using namespace std;

void iniciar(tListaSudokus& lista) {

	lista.contador = 0;
	for (int i = 0; i < MAX_SDK; i++){
		iniciar(lista.registro[i], "", 0);
	}

}

int numElems(const tListaSudokus& lista) {
	int num = lista.contador;

	return num;
}

bool cargar(tListaSudokus& lista) {
	bool carga = false;
	ifstream archivo;
	tListaSudokus aux;
	int cont = 0;

	iniciar(lista);
	
	archivo.open("registroSudokus.txt");
	if (!archivo.is_open()) {
		cout << "Error al leer los datos." << endl;
		carga = false;
	}
	else {
		while ((lista.contador < MAX_SDK) && (cargar(lista.registro[lista.contador], archivo))) {
			cont = lista.contador;
			while ((cont > 0) && (lista.registro[cont] < lista.registro[cont - 1])) { //(operator<(lista.registro[cont], lista.registro[cont - 1]))
				aux.registro[cont] = lista.registro[cont];
				lista.registro[cont] = lista.registro[cont - 1];
				lista.registro[cont - 1] = aux.registro[cont];
				cont--;
			}
			lista.contador++;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void mostrar(const tListaSudokus& lista) {

	cout << endl << right << setw(22) << "FICHERO DE CARGA" << setw(10) << "NIVEL" << endl;
	cout << setfill('-') << setw(45) << "\n" << setfill(char(0));
	for (int i = 0; i < lista.contador; i++) {
		cout << right << i + 1 << "." <<  setw(20) << lista.registro[i].nomTablero << setw(10) << lista.registro[i].puntos << endl;
	}
	cout << setfill('-') << setw(45) << "\n" << setfill(char(0));

}

////

bool guardar(const tListaSudokus& lista) {
	ofstream archivo;
	bool guardado = false;
	int i = 0;

	archivo.open("registroSudokus.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar." << endl;
	}
	else {
		while ((i < lista.contador) && (!guardado)) {
			if (guardar(lista.registro[i], archivo)) {
				i++;
			}
		}
		guardado = true;
	}

	return guardado;
}

bool buscar(const tListaSudokus& lista, string nombArch) {
	bool encontrado = false;
	int i = 0;

	while ((!encontrado) && (i < lista.contador)) {
		if (lista.registro[i].nomTablero != nombArch) {
			i++;
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}

bool insertar(tListaSudokus& lista, const tRegSudoku& sudoku) {
	bool insertado = false;
	tListaSudokus aux;
	int cont = 0;

	if (buscar(lista, sudoku.nomTablero)) {
		cout << "El tablero ya existe." << endl;
	}
	else {
		if (lista.contador < MAX_SDK) {	
			cont = lista.contador;
			while ((cont > 0) && (operator<(sudoku, lista.registro[cont - 1]))) {
				aux.registro[cont] = lista.registro[cont];
				lista.registro[cont] = lista.registro[cont - 1];
				lista.registro[cont - 1] = aux.registro[cont];
				cont--;
			}
			iniciar(lista.registro[cont], sudoku.nomTablero, sudoku.puntos);
			lista.contador++;
			insertado = true;
		}
		else {
			cout << "La lista está llena." << endl;
		}
	}

	return insertado;
}