//Sudoku - Fernando M�ndez Torrubiano
#ifndef H_LISTAJUGADORES_H
#define H_LISTAJUGADORES_H
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "RegistroJugador.h"

//Constantes:
//const int MAX_JGD = 9;

//Tipos:
typedef struct tListaJugadores {
	tRegJugador** jugadores; //El primer asterisco indica que el array es din�mico, el segundo indica que cada campo del array son punteros a datos.
	int capacidad;
	int contador;
};


//Funciones:
void iniciar(tListaJugadores& lista); //Inicializa�lista�a�lista�vac�a.
bool cargar(tListaJugadores& lista); //Guarda�en�lista�el�contenido del�archivo�listaJugadores.txt;�devuelve�un�booleano�que�indica�si�la�carga�se�ha�podido�realizar.
void mostrar(const tListaJugadores& lista); //Visualiza�en�la�consola la�lista�de�jugadores�dada.
bool guardar(const tListaJugadores& lista); //Almacena�en�el�archivo registroJugadores.txt�el�contenido�de�lista�y�devuelve�un�valor�booleano� indicando�si�la�acci�n�fue�posible.Debe�respetar�el�formato�indicado�para�el� archivo.
bool buscar(const tListaJugadores& lista, const tRegJugador& jugador, int& pos); //Busca en lista al jugador; devuelve true y la posici�n(pos) en la que se encuentra si el jugador est� en la lista; devuelve false y la posici�n(pos) en la que deber�a estar si el jugador no est� en la lista. Debes implementar una b�squeda binaria utilizando el operador < del m�dulo RegistroJugador.
bool actualizar(tListaJugadores& lista, const tRegJugador& jugador); //Si�el�jugador�se�encuentra�ya�en�la�lista, actualiza�su�informaci�n�con�los nuevos puntos; en otro caso, si la lista no�est�llena, lo inserta�ordenadamente�en�la�lista.
void mostrarXRanking(const tListaJugadores& lista); //Muestra�los jugadores�de la lista dada ordenados por ranking�(decrecientemente�por puntos, y�a�igualdad�de�puntos�crecientemente�por�identificador).
void ampliar(tListaJugadores& lista, int num); //Ampl�a el tama�o del array din�mico de lista a num elemento m�s.Los datos de los jugadores que ya existen en la lista deben mantenerse.
void liberar(tListaJugadores& lista); //Libera la memoria din�mica usada por lista.

#endif
