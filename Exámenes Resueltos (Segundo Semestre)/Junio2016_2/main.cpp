//Examen Junio 2016 - FP
//Grupo_2
//Fernando Méndez Torrubiano

#include "ListaGrupos.h"
#include "checkML.h"
using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta fugas de memoria.
	system("chcp 1252");//Castellano.
	system("cls");

	tListaGrupos grupos;
	string NIF;
	int pos = 0;

	if (cargar(grupos)) {
		mostrar(grupos);
		cout << endl << "Introduce un NIF: ";
		cin >> NIF;
		if (buscar(grupos, NIF, pos)) {
			cout << "Grupo: " << grupos.grupo[pos]->id << endl;
		}
		else {
			cout << "No se ha encontrado el alumno." << endl;
		}
	}
	else {
		cout << "FIN DEL PROGRAMA." << endl;
	}
	system("PAUSE");
	destruir(grupos);

	return 0;
}