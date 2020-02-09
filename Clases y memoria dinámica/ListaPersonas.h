/*
	Fernando Méndez
	https://fernmend.ddns.net
	C++ | Clases y memoria dinámica.
*/

#ifndef _LISTA
#define _LISTA

#include <iostream>
#include <string>
#include <conio.h>
#include "persona.h"

class ListaPersonas{
public:
	//Constructoras:
	ListaPersonas();
	ListaPersonas(int);

	//Métodos públicos:
	void liberar(); //Libera la memoria dinámica.
	void agregar(); //Añade objectos de la clase Persona a la lista.
	void mostrar(); //Muestra la lista de personas.

private:
	//Atributos:
	Persona** _persona;
	int _capacidad, _contador;

	//Métodos privados:
	void ampliar(); //Amplia la lista en caso de que se alcance la máxima capacidad.
	bool salir(); //Lee una tecla. Si es "ESC", devuleve true (false en caso contratio).

};

#endif // !_LISTA