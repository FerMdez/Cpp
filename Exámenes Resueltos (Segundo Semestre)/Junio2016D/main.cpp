//Examen Junio de 2016 - FP
//Grupo D
//Fernando M�ndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "ListaPeliculas.h"
#include "CheckML.h"
using namespace std;


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.
	system("chcp 1252"); //As� la consola puede imprimir caracteres especiales del espa�ol.
	system("cls");


	tListaPeliculas lista;
	string nombre;

	if (cargar(lista)) {
		cout << "Introduzca nombre del actor: ";
		getline(cin, nombre);
		//mostrar(lista);
		filtrarPorActor(lista, nombre);
	}
	else {
		cout << "No se ha podido cargar el archivo." << endl;
	}

	destruir(lista); //Libera la memoria din�mica.

	system("PAUSE");
	return 0;
}