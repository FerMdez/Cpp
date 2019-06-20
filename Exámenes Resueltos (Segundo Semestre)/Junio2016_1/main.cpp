//Examen Junio 2016 - FP
//Grupo_1
//Fernando Méndez Torrubiano

#include "ListaReproduccion.h"
#include "checkML.h"
using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta fugas de memoria.
	system("chcp 1252"); //Castellano.
	system("cls");
	srand(1);

	tListaTemas listaTemas;
	tListaReproduccion listaReproduccion;
	int origen, fin;
	
	if (cargar(listaTemas)) {
		cout << "Nombre: ";
		cin >> listaReproduccion.nombreLista;
		do {
			cout << "Numero de temas: ";
			cin >> listaReproduccion.capacidad;
		} while (listaReproduccion.capacidad < 0 || listaReproduccion.capacidad > listaTemas.cont);

		nueva(listaReproduccion);
		for (int i = 0; i < listaReproduccion.capacidad; i++){
			listaReproduccion.elemento[i].puntero = listaTemas.tema[0 + rand() % listaReproduccion.capacidad];
			listaReproduccion.elemento[i].valoracion = 0 + rand() % listaReproduccion.capacidad;
			if (!insertar(listaReproduccion, listaReproduccion.elemento[i])) {
				i--;
			}
		}
		mostrar(listaReproduccion);

		origen = 4;
		//origen = 0 + rand() % listaReproduccion.capacidad;
		fin = 0;
		//fin = 0 + rand() % listaReproduccion.capacidad;
		cout << "Cambio de orden: " << origen + 1 << " al " << fin + 1 << endl;
		modificarOrden(listaReproduccion, origen, fin);
		mostrar(listaReproduccion);

		system("PAUSE");
	}
	else {
		cout << "Fin del programa." << endl;
		system("PAUSE");
	}

	destruir(listaTemas);
	destruir(listaReproduccion);

	return 0;
}