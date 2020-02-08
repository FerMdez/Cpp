#include "ListaPersonas.h"
using namespace std;

void iniciar(tListaPersonas& lista) {
	lista.capacidad = 2;
	lista.contador = 0;
	lista.persona = new Persona * [lista.capacidad]; //Crea una lista de punteros (que en un futuro, apuntarán cada uno a "tPersona").
}

void ampliar(tListaPersonas& lista) {
	lista.capacidad *= 2;
	Persona** aux = new Persona * [lista.capacidad];

	for (int i = 0; i < lista.contador; i++) {
		aux[i] = lista.persona[i];
	}

	delete[] lista.persona;
	lista.persona = aux;
}

void liberar(tListaPersonas& lista) {
	for (int i = 0; i < lista.contador; i++) {
		delete lista.persona[i];
	}

	delete[] lista.persona;
}

void agregar(tListaPersonas& lista) {
	string nombre, apellidos, NIF, edad;

	do {
		if (lista.contador == lista.capacidad) { ampliar(lista); }
		cout << "Introduzca nombre de persona: " << endl;
		getline(cin, nombre);
		cout << "Introduzca apellidos: " << endl;
		getline(cin, apellidos);
		cout << "Introduzca NIF: " << endl;
		getline(cin, NIF);
		cout << "Introduzca edad: " << endl;
		getline(cin, edad);
		lista.persona[lista.contador] = new Persona(nombre, apellidos, NIF, edad);
		lista.contador++;
		cout << "Pulse 'ESC' para SALIR, 'ENTER' para continuar..." << endl;
	} while (!salir());
}

void mostrar(tListaPersonas& lista) {
	cout << setw(10) << right << "NOMBRE" << setw(20) << "APELLIDOS" << setw(20) << "NIF" << setw(15) << "EDAD" << endl;
	cout << setw(75) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < lista.contador; i++) {
		lista.persona[i]->mostrar();
		cout << endl;
	}
}

bool salir() {
	int tecla = 27;
	bool ESC = false;

	cin.sync();
	tecla = _getch();
	if (tecla != 0xe0) {
		if (tecla == 27) {
			ESC = true;
		}
	}

	return ESC;
}