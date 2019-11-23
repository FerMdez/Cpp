/*
	Fernando Méndez	| @HumperCobra
	https://fernmend.ddns.net
	All rights reserved | 23/11/2019
*/

#include <iostream>
#include <string>
#include <iomanip>
//#include "checkML.h"
/********************ARCHIVO checkML.h********************/
#ifdef _DEBUG  
#define _CRTDBG_MAP_ALLOC  

#include <stdlib.h>  
#include <crtdbg.h>  

#ifndef DBG_NEW  
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )  
#define new DBG_NEW 

#endif  
#endif
/*********************************************************/
using namespace std;

//Constantes:
const int MAX = 15;

//Tipos:
typedef struct tPersona {
	string name, secondName;
	string id;
};

typedef struct tListaPersonas {
	tPersona** persona;
	int capacidad;
	int contador;
};

//Funciones:
void iniciar(tListaPersonas&); //Inicia la lista con capacidad = 3 y contador = 0.
void liberar(tListaPersonas&); //Libera la memoria dinámica. Se debe llamar antes de finalizar el programa para evitar fugas.
void ampliar(tListaPersonas&); //Redimensiona la lista en caso de que el contador haya alcanzado la capacidad máxima actual.


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.

	tListaPersonas lista;
	iniciar(lista);

	srand(time(NULL));

	int i = 1;
	string pos;

	cout << setw(5) << "NOMBRE" << setw(15) << "APELLIDO" << setw(15) << "ID" << endl;
	cout << setfill('-') << setw(50) << "\n" << setfill(char(0));
	while (lista.contador < MAX){
		if (lista.contador == lista.capacidad) {
			ampliar(lista);
		}
		else {
			pos = to_string(i);
			lista.persona[lista.contador] = new tPersona; //Reserva memoria para una "tPersona".
			lista.persona[lista.contador]->name = "Persona" + pos;
			lista.persona[lista.contador]->secondName = "Apellido" + pos;
			pos += rand();
			lista.persona[lista.contador]->id = pos;
			cout << setw(5) << lista.persona[lista.contador]->name << setw(15) << lista.persona[lista.contador]->secondName << setw(15) << lista.persona[lista.contador]->id << endl;
			lista.contador++;
			i++;
		}
	}
	cout << setfill('-') << setw(50) << "\n" << setfill(char(0));
	system("PAUSE");

	liberar(lista);
	return 0;
}

void iniciar(tListaPersonas& lista) {
	lista.capacidad = 3;
	lista.contador = 0;
	lista.persona = new tPersona*[lista.capacidad]; //Crea una lista de punteros (que en un futuro, apuntarán cada uno a "tPersona").
}

void ampliar(tListaPersonas& lista) {
	lista.capacidad *= 2;
	tPersona** aux = new tPersona*[lista.capacidad];

	for (int i = 0; i < lista.contador; i++){
		aux[i] = lista.persona[i];
	}

	delete[] lista.persona;
	lista.persona = aux;
}

void liberar(tListaPersonas& lista) {
	for (int i = 0; i < lista.contador; i++){
		delete lista.persona[i];
	}
	
	delete[] lista.persona;
}























































































/*
	Fernando Méndez	| @HumperCobra
	https://fernmend.ddns.net
	All rights reserved | 23/11/2019
*/