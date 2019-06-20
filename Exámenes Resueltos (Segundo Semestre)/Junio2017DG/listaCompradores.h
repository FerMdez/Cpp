#ifndef H_LISTACOMPRADORES_H
#define H_LISTACOMPRADORES_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

//Constantes:

//Tipos:
typedef struct tComprador {
	long long int id, importe;
};

typedef struct tListaComprador {
	tComprador** comprador;
	int cont, capacidad;
};

//Funciones:
void iniciar(tListaComprador& lista);
bool insertar(tListaComprador& lista, tComprador& comprador);
bool buscar(tListaComprador& lista, tComprador& comprador, int& pos);
void mostrar(tListaComprador& lista);
void liberar(tListaComprador& lista);

#endif // !H_LISTACOMPRADORES_H
