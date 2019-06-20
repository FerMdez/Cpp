#ifndef H_LOTES_H
#define H_LOTES_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "listaCompradores.h"

//Constantes:
const int MAX_LOTES = 300;

//Tipos:
typedef struct tLotes {
	std::string lote, tipo;
	float peso, precio;
	long long int id;
};

//Funciones:
bool operator<(tLotes& loteIzq, tLotes& loteDer);
bool operator==(tLotes& loteIzq, tLotes& loteDer);
void mostrarLote(const tLotes& lote);
void mostrarPrecio(tLotes& lote, tComprador& comprador);
void modificarLote(tLotes& lote, long long int& id, float& precio);

#endif // !H_LOTES_H

