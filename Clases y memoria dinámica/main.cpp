/*
	Fernando Méndez
	https://fernmend.ddns.net
	C++ | Clases y memoria dinámica.
*/

#include "ListaPersonas.h"
#include "checkML.h"


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.

	ListaPersonas lista = ListaPersonas();

	lista.agregar();
	lista.mostrar();
	system("PAUSE");

	lista.liberar();
	return 0;
}