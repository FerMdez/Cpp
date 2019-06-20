#include "Contacto.h"
using namespace std;

bool cargar(tContacto& contacto, std::ifstream& archivo) {
	bool carga = false;
	if (!archivo.fail()) {
		getline(archivo, contacto.id);
		getline(archivo, contacto.nombre);
		getline(archivo, contacto.email);
		getline(archivo, contacto.tlf);
		carga = true;
	}

	return carga;
}

void mostrar(tContacto& contacto) {
	cout << right << setw(10) << "Contacto: "
		<< setw(10) << contacto.id
		<< " - " << setw(20) << contacto.nombre << endl
		<< setw(10) << "Email: " << setw(20) << contacto.email
		<< " - " << setw(5) << "tlf.:" << setw(10) << contacto.tlf << endl;
}