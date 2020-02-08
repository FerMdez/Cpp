#include "ListaPersonas.h"
#include "checkML.h"


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.

	tListaPersonas personas;

	iniciar(personas);

	agregar(personas);
	mostrar(personas);
	system("PAUSE");

	liberar(personas);
	return 0;
}