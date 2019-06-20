//Examen Junio 2017 - FP
//Grupos D y G
//Fernando Méndez Torrubiano

using namespace std;
#include "listaLonja.h"
#include "CheckML.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.
	system("chcp 1252"); //Castellano
	system("cls");

	tListaLotes listaLotes;
	tListaComprador listaComprador;
	iniciar(listaComprador);
	tComprador aux;
	int i = 0;

	if (cargar(listaLotes)) {
		while (i < listaLotes.cont) {
			mostrarLote(*listaLotes.lote[i]);
			cout << "Introduzca comprador y precio: ";
			cin >> aux.id;
			cin >> aux.importe;
			insertar(listaComprador, aux);
			i++;
		}
		mostrar(listaComprador);
		mostrar(listaLotes, listaComprador);
	}
	else {
		cout << "Error al cargar la lista." << endl;
	}
	system("PAUSE");

	liberar(listaLotes);
	liberar(listaComprador);

	return 0;
}