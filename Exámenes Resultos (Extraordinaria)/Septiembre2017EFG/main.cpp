//Examen Junio 2017 - FP
//Grupos E, F y G
//Fernando Méndez Torrubiano

using namespace std;

#include "Grupos.h"
#include "CheckML.h"

int menu();

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.
	system("chcp 1252");

	tGrupo grupo;
	tListaMatriculas lista;
	tAlumno alumno;

	string id, nif;
	int opcion, aula;
	bool ok = false;

	if (cargarMatriculas(lista)) {
		cout << "Introduce un identificador del grupo: ";
		cin >> id;
		cout << "Introduce el aula: ";
		cin >> aula;

		nuevo(grupo, id, aula);

		do {
			opcion = menu();
			switch (opcion){
			case 1:
				leer(lista, grupo);
				break;
			case 2: 
				cout << "NIF del alumno a eliminar: ";
				cin >> nif;
				eliminarAlumno(grupo, nif);
				break;
			case 3:
				cout << endl;
				mostrarGrupo(grupo);
				cout << endl;
				break;
			default:
				break;
			}
		} while (opcion != 0);
		//
	}
	else {
		cout << "Fin del programa." << endl;
	}

	liberar(lista);
	liberar(grupo);

	return 0;
}

int menu() {
	int opc = -1;

	cout << "1.-Añadir un alumno al grupo." << endl;
	cout << "2.-Eliminar un alumno del grupo." << endl;
	cout << "3.-Mostrar el estado actual del grupo." << endl;
	cout << "0.-SALIR." << endl;

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 3);
	return opc;
}