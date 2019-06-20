#include "Tema.h"
using namespace std;

bool cargar(tTema& tema, ifstream& archivo) {
	bool carga = false;

	if (!archivo.fail()) {
		archivo >> tema.titulo;
		archivo >> tema.interprete;
		archivo >> tema.segundos;
		carga = true;
	}

	return carga;
}

void mostrar(tTema& tema) {
	cout << right << setw(7) << tema.titulo
		<< setw(15) << tema.interprete
		<< setw(10) << tema.segundos << " seg.";
}