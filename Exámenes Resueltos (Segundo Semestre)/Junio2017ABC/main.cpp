//Examen Junio 2017 - FP
//Grupos A, B y C
//Fernando Méndez Torrubiano

#include "ListaCitas.h"
#include "CheckML.h"
using namespace std;

//Funciones auxiliares:
int menu(); //Muestra el menú de opciones.

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Muestra fugas de memoria.
	system("chcp 1252"); //Castellano.
	system("cls");

	tListaCitas listaCitas;
	tListaClientes lista;
	tCliente cliente1, cliente2;
	tCita cita;

	int opc = -1;
	int i = 0, c1, c2;

	if (cargar(lista)) {
		nuevaLista(listaCitas);
		while (opc != 0){
			opc = menu();
			i = 0;
			switch (opc){
			case 1:
				mostrar(lista, i);
				break;
			case 2:
				mostrar(lista, i);
				cout << "Cliente 1: ";
				cin >> c1;
				cita.puntero1 = lista.cliente[c1];
				cout << "Cliente 2: ";
				cin >> c2;
				cita.puntero2 = lista.cliente[c2];
				cout << "Lugar de la cita: ";
				cin >> cita.lugar;
				cout << "Valoración de la cita: ";
				cin >> cita.valoracion;
				inserta(listaCitas, cita);
				break;
			case 3: 
				muestra(listaCitas);
				break;
			default:
				break;
			}
		}
	}
	else {
		cout << "Fin del programa." << endl;
		system("PAUSE");
	}
	liberar(lista);
	libera(listaCitas);

	return 0;
}

int menu() {
	int opc = 0;
	cout << "1.-Mostrar lista de clientes." << endl;
	cout << "2.-Nueva cita." << endl;
	cout << "3.-Mostrar todas las citas (ordenasdas por valoración)." << endl;
	cout << "0.-SALIR" << endl;

	do {
		cout << "Introduzca una opción:";
		cin >> opc;
	} while (opc < 0 || opc > 3);

	return opc;
}