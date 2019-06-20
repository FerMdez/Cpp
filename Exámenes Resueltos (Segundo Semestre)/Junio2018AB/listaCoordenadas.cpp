#include "listaCoordenadas.h"
using namespace std;

void crearVacia(tListaCoordenadas& listaCoor) {
	for (int i = 0; i < MAX_COORDENADAS; i++){
		listaCoor.coordenada[i]._fila = 0;
		listaCoor.coordenada[i]._columna = 0;
	}
	listaCoor.cont = 0;
}

bool buscar(tListaCoordenadas& listaCoor, tCoordenada& coordenada) {
	bool encontrada = false;
	int i = 0;

	while (!encontrada && i < listaCoor.cont) {
		if (listaCoor.coordenada[i] == coordenada) {
			encontrada = true;
		}
		else {
			i++;
		}
	}

	return encontrada;
}

bool insertar(tListaCoordenadas& listaCoor, tCoordenada& coor) {
	bool insertado = false;

	if (!buscar(listaCoor, coor)) {
		listaCoor.coordenada[listaCoor.cont] = coor;
		listaCoor.cont++;
		insertado = true;
	}

	return insertado;
}

bool sacar(tListaCoordenadas& listaCoor, tCoordenada& coor) {
	bool sacada = false;

	if (listaCoor.cont > 1) {
		coor = listaCoor.coordenada[listaCoor.cont];
		listaCoor.cont--;
		sacada = true;
	}

	return sacada;
}