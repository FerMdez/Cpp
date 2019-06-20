#include "Reparto.h"
using namespace std;

bool cargar(tReparto& reparto, ifstream& archivo){
	bool carga = false;

	if (!archivo.fail()) {
		getline(archivo, reparto.nombre);
		carga = true;
	}

	return carga;
}

bool aparece(tReparto& reparto, string & nombre, int & pos){
	bool encontrado = false;

	return encontrado;
}
