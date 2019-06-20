#include "ItemPedido.h"
using namespace std;

bool cargar(tItem& item, std::ifstream& archivo) {
	bool carga = false;

	archivo.ignore();
	getline(archivo, item.id);
	getline(archivo, item.nombre);
	archivo >> item.cantidad;

	if (!archivo.fail()) { carga = true; }

	return carga;
}

void mostrar(tItem& item) {
	cout << right << setw(15) << item.id
		<< setw(2) << "-" << setw(2)
		<< setw(25) << item.nombre
		<< setw(5) << "(" << item.cantidad << ")" << endl;
}