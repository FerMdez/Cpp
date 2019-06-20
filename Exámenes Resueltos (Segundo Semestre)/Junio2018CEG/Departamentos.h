#ifndef H_DEPARTAMENTOS_H
#define H_DEPAETAMENTOS_H

#include "ListaContratos.h"

//Constantes:
const int MAX_EMPLEADOS = 50;

//Tipos:
typedef struct tEmpleado {
	tContrato *puntero;
	int numero;
};

typedef struct tDepartamento {
	tEmpleado *empleado;
	int cont;
	std::string id;
};

//Funciones:
void inicializar(tDepartamento& departamento, std::string& id);
int buscarEmpleado(tDepartamento& departamento, std::string& nif);
bool insertarEmpleado(tListaContratos& contratos, tDepartamento& departamento, int&);
void mostrarEmpleado(tEmpleado& empleado, int& pos);
void mostrarDepartamentos(tDepartamento& departamento);
void liberar(tDepartamento& departamento);

#endif // !H_DEPARTAMENTOS_H

