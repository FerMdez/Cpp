#ifndef H_LISTACONTRATOS_H
#define H_LISTACONTRATOS_H

#include"ListaTareas.h"

//Constantes:
const int MAX_CONTRATOS = 100;

//Tipos:
typedef struct tContrato {
	std::string nombre, nif;
	tListaTareas lista;
	double sueldo;
};

typedef struct tListaContratos {
	tContrato *contrato[MAX_CONTRATOS]; //Ordenados por NIF.
	int cont;
};

//Funciones:
bool cargarContratos(tListaContratos& lista, tPrioridades& prioridades);
bool insertarContrato(tListaContratos& lista, tPrioridades& prioridades, std::ifstream& archivo);
void mostrarContratos(tListaContratos& lista);
int seleccionarContratos(tListaContratos& lista);
void liberar(tListaContratos& lista);


#endif // !H_LISTACONTRATOS_H
