#ifndef _LISTACLIENTES
#define _LISTACLIENTES

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

//Constantes:
const int MAX_CLIENTES = 50;

//Tipos:
typedef struct tCliente {
	std::string login, fechaAlta, ciudad;
	int edad;

};

typedef struct tListaClientes {
	tCliente *cliente[MAX_CLIENTES]; //NO ORDENADA.
	int cont;
};

//Funciones:
void mostrar(tCliente& cliente); 

bool cargar(tListaClientes& lista);
void mostrar(tListaClientes& lista, int&); //Recursiva
void liberar(tListaClientes& lista);

#endif // !
