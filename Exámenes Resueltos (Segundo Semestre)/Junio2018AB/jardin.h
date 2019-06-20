#ifndef _JARDIN
#define _JARDIN

#include "coordenada.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Constantes:
const int DIM = 50;

//Tipos:
typedef struct tParcela{
	int aguaNecesaria;
	int aguaRegada;
};

typedef struct tJardin {
	tParcela parcela[DIM][DIM];
	int numF, numC;
};

//Funciones:
bool cargarJardin(tJardin& jardin, std::ifstream& archivo);
void mostrarJardin(tJardin& jardin);
void regar(tJardin& jardin, tCoordenada& coordenada);
int calcularPuntuacion(tJardin& jardin);
bool plantaCondenada(tJardin& jardin, tCoordenada& coordenada);
bool esLibre(const tJardin& jardin, tCoordenada coordenada);


#endif // !_JARDIN
