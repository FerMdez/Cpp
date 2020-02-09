/*
	Fernando Méndez
	https://fernmend.ddns.net
	C++ | Clases y memoria dinámica.
*/


#include "ListaPersonas.h"
using namespace std;


ListaPersonas::ListaPersonas(){
	_capacidad = 2;
	_contador = 0;
	_persona = new Persona * [_capacidad]; //Crea una lista de punteros (que en un futuro, apuntarán cada uno a una Persona(clase)).
}

inline ListaPersonas::ListaPersonas(int capacidad){
	_capacidad = capacidad;
	_contador = 0;
	_persona = new Persona * [_capacidad]; //Crea una lista de punteros (que en un futuro, apuntarán cada uno a una Persona(clase)).
}

void ListaPersonas::ampliar() {
	_capacidad *= 2;
	Persona** aux = new Persona * [_capacidad];

	for (int i = 0; i < _contador; i++) {
		aux[i] = _persona[i];
	}

	delete[] _persona;
	_persona = aux;
}

void ListaPersonas::liberar() {
	for (int i = 0; i < _contador; i++) {
		delete _persona[i];
	}

	delete[] _persona;
}

void ListaPersonas::agregar() {
	string nombre, apellidos, NIF, edad;

	do {
		if (_contador == _capacidad) { ampliar(); }
		cout << "Introduzca nombre de persona: " << endl;
		getline(cin, nombre);
		cout << "Introduzca apellidos: " << endl;
		getline(cin, apellidos);
		cout << "Introduzca NIF: " << endl;
		getline(cin, NIF);
		cout << "Introduzca edad: " << endl;
		getline(cin, edad);
		_persona[_contador] = new Persona(nombre, apellidos, NIF, edad);
		_contador++;
		cout << "Pulse 'ESC' para SALIR, 'ENTER' para continuar..." << endl;
	} while (!salir());
}

void ListaPersonas::mostrar() {
	cout << setw(10) << right << "NOMBRE" << setw(20) << "APELLIDOS" << setw(20) << "NIF" << setw(15) << "EDAD" << endl;
	cout << setw(75) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < _contador; i++) {
		_persona[i]->mostrar();
		cout << endl;
	}
}

bool ListaPersonas::salir() {
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