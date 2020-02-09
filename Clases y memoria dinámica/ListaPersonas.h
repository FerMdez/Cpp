/*
	Fernando M�ndez
	https://fernmend.ddns.net
	C++ | Clases y memoria din�mica.
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

	//M�todos p�blicos:
	void liberar(); //Libera la memoria din�mica.
	void agregar(); //A�ade objectos de la clase Persona a la lista.
	void mostrar(); //Muestra la lista de personas.

private:
	//Atributos:
	Persona** _persona;
	int _capacidad, _contador;

	//M�todos privados:
	void ampliar(); //Amplia la lista en caso de que se alcance la m�xima capacidad.
	bool salir(); //Lee una tecla. Si es "ESC", devuleve true (false en caso contratio).

};

#endif // !_LISTA