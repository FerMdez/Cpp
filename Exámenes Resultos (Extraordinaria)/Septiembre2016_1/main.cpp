//Examen Septiembre 2016 - FP
//Grupos: _1
//Fernando Méndez Torrubiano

#include "ListaEnvios.h"
#include "checkML.h"
using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF  | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.
	system("chcp 1252"); //Castellano
	system("cls");

	tListaEnvios envios;

	if (cargar(envios)) {
		mostrar(envios);
		//
	}
	else {
		cout << "FIN DEL PROGRAMA." << endl;
	}
	system("PAUSE");

	destruir(envios);

	return 0;
}