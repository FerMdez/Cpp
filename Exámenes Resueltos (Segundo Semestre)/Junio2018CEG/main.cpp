//Examen Junio 2018 - FP
//Grupos C, E y G.
//Fernando Méndez Torrubiano

#include "Departamentos.h"
#include "checkML.h"
using namespace std;

int menu();

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Muestra fugas de memoria.
	system("chcp 1252"); //Castellano.
	system("cls");

	tDepartamento dpto;
	tListaContratos lista;
	tPrioridades prioridades;
	tEmpleado empleado;
	string id, nif;
	int opcion, pos = -1;


	if (cargarPrioridades(prioridades)) {
		if (cargarContratos(lista, prioridades)) {
			cout << "Identificador del departamento: ";
			cin >> id;
			cout << endl;
			inicializar(dpto, id);
			do {
				opcion = menu();
				switch (opcion){
				case 1:
					pos = seleccionarContratos(lista);
					if (!insertarEmpleado(lista, dpto, pos)) {
						cout << "Error al insertar el empleado." << endl;
					}
					break;
				case 2:
					cout << "NIF del emplieado: ";
					cin >> nif;
					cout << endl;
					pos = buscarEmpleado(dpto, nif);
					if (pos != -1) {
						mostrarTareas(dpto.empleado[pos].puntero->lista);
					}
					else {
						cout << "El empleado no está en el departamento." << endl;
					}
					cout << endl;
					break;
				case 3:
					if (dpto.cont != 0) {
						cout  << endl << "Los empleados del departamento '" << dpto.id  << "' son:" << endl;
						mostrarDepartamentos(dpto);
					}
					else {
						cout << "No hay empleados." << endl;
					}
					cout << endl;
					break;
				default:
					break;
				}
			} while (opcion != 0);

			liberar(lista);
			liberar(dpto);	
		}
		else {
			cout << "Error al cargar la lista de contratos." << endl;
		}
	}
	else {
		cout << "Error al cargar las prioridades." << endl;
	}

	return 0;
}

int menu() {
	int opc = -1;

	cout << "1.-Insertar empleado en nuevo dpto." << endl;
	cout << "2.-Mostrar tareas de un empleado." << endl;
	cout << "3.-Mostrar los empleados actuales de un dpto." << endl;
	cout << "0.-SALIR." << endl;
	do {
		cout << "Introduzca una opc: ";
		cin >> opc;
	} while (opc < 0 || opc > 3);
	
	return opc;
}