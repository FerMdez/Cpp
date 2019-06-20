#include "jardin.h"
using namespace std;

bool cargarJardin(tJardin& jardin, ifstream& archivo) {
	bool carga = false;
	int F, C;
	//ifstream archivo;

	//archivo.open(jardin);
	//if (!archivo.is_open()) {
	//	cout << "No se ha podido cargar el jardin." << endl;
	//}
	//else {
	archivo >> jardin.numF;
	archivo >> jardin.numC;
		for (int i = 0; i < jardin.numF; i++){
			for (int j = 0; j < jardin.numC; j++){
				archivo >> jardin.parcela[i][j].aguaNecesaria;
				jardin.parcela[i][j].aguaRegada = 0;
			}
		}
		carga = true;
	//}
	//archivo.close();

	return carga;
}

void mostrarJardin(tJardin& jardin) {
	for (int i = 0; i < jardin.numF; i++){
		for (int j = 0; j < jardin.numC; j++){
			cout << jardin.parcela[i][j].aguaNecesaria << " ";
		}
		cout << endl;
	}
}

void regar(tJardin& jardin, tCoordenada& coordenada) {
	tCoordenada nc;

	for (int i = 0; i < 8; i++){
		calcularCoordenada(coordenada, i, nc);
		jardin.parcela[nc._fila][nc._columna].aguaRegada++;
	}
}

int calcularPuntuacion(tJardin& jardin) {
	int puntos = 0;

	for (int i = 0; i < jardin.numF; i++){
		for (int j = 0; j < jardin.numC; j++){
			if (jardin.parcela[i][j].aguaRegada > jardin.parcela[i][j].aguaNecesaria) {
				puntos += (jardin.parcela[i][j].aguaRegada - jardin.parcela[i][j].aguaNecesaria);
			}
			else if (jardin.parcela[i][j].aguaRegada == jardin.parcela[i][j].aguaNecesaria) {
				puntos += jardin.parcela[i][j].aguaNecesaria;
			}
		}
	}

	return puntos;
}

bool plantaCondenada(tJardin& jardin, tCoordenada& coordenada) {
	bool encontrada = false;
	int i = -1, j = 0;
	
	while (!encontrada && i < jardin.numF) {
		i++;
		while (!encontrada && j < jardin.numC) {
			if (jardin.parcela[i][j].aguaNecesaria < jardin.parcela[i][j].aguaRegada) {
				encontrada = true;
			}
			else {
				j++;
			}
		}
	}

	coordenada = crearCoordenada(i, j);

	return encontrada;
}

bool esLibre(const tJardin& jardin, tCoordenada coordenada) {
	bool libre = false;

	if (coordenada._fila < jardin.numF && coordenada._columna < jardin.numC && jardin.parcela[coordenada._fila][coordenada._columna].aguaNecesaria == 0) {
		libre = true;
	}

	return libre;
}
