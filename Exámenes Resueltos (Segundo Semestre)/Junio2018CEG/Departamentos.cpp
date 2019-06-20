#include "Departamentos.h"
using namespace std;

void inicializar(tDepartamento& departamento, std::string& id) {
	departamento.cont = 0;
	departamento.id = id;
	departamento.empleado = new tEmpleado[MAX_EMPLEADOS];
}

int buscarEmpleado(tDepartamento& departamento, std::string& nif) {
	int pos = departamento.cont - 1;
	bool encontrado = false;

	while (!encontrado && pos >= 0) {
		if (departamento.empleado[pos].puntero->nif == nif) {
			encontrado = true;
		}
		else {
			pos--;
		}
	}

	return pos;
}

bool insertarEmpleado(tListaContratos& contratos, tDepartamento& departamento, int& pos) {
	bool insertado = false;
	int i = buscarEmpleado(departamento, contratos.contrato[pos]->nif);

	if (i == -1) {
		departamento.empleado[departamento.cont].puntero = contratos.contrato[pos];
		departamento.cont++;
		departamento.empleado->numero = departamento.cont;
		insertado = true;
	}

	return insertado;
}

void mostrarEmpleado(tEmpleado& empleado, int& i) {
	cout << right << setw(3) << i+1 << ".-" << setw(25) << empleado.puntero->nombre << setw(10) << "num.: " << empleado.numero << endl;
}

void mostrarDepartamentos(tDepartamento& departamento) {
	for (int i = 0; i < departamento.cont; i++){
		mostrarEmpleado(departamento.empleado[i], i);
	}
}

void liberar(tDepartamento& departamento) {
	delete[] departamento.empleado;
}