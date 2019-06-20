#include "Estudiante.h"
using namespace std;

bool cargar(tEstudiante& estudiante, std::ifstream& archivo) {
	bool cargar = false;

	if (!archivo.fail()) {
		archivo.ignore();
		getline(archivo, estudiante.nombre);
		archivo >> estudiante.NIF;
		archivo >> estudiante.fechaMatricula;
		archivo >> estudiante.nota;
		cargar = true;
	}

	return cargar;
}

void mostrar(tEstudiante& estudiante) {
	cout << right << setw(9) << estudiante.NIF
		<< setw(2) << "-" << setw(2)
		<< setw(8) << estudiante.fechaMatricula
		<< setw(2) << "-" << setw(2)
		<< setw(3) << estudiante.nota
		<< setw(2) << "-" << setw(2)
		<< setw(20) << estudiante.nombre << endl;
}