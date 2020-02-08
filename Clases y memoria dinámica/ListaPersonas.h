#ifndef _LISTA
#define _LISTA

#include <iostream>
#include <string>
#include <conio.h>
#include "persona.h"

//Constantes:

//Tipos:
typedef struct tListaPersonas {
	Persona** persona;
	int contador;
	int capacidad;
};

//Funciones:
void iniciar(tListaPersonas&); //Inicializa una lista din�mica de la clase Persona, con un contador a '0' y una capacidad inicial de '2'.
void ampliar(tListaPersonas&); //Amplia la lista en caso de que se alcance la capacidad m�xima.
void liberar(tListaPersonas&); //Libera la memoria din�mica.
void agregar(tListaPersonas&); //M�todo para agregar una nueva persona a la lista.
void mostrar(tListaPersonas&); //Muestra la lista de personas.
bool salir(); //Lee una tecla, devuelve true si la tecla es "ESC".

#endif // !_LISTA

