#include "Grupos.h"
using namespace std;

void nuevo(tGrupo& grupo, string& id, int& aula) {
	grupo.id = id;
	grupo.aula = aula;
	grupo.cont = 0;
	grupo.alumnos = new tAlumno[MAX_ALUMNOS];
}

void leer(tListaMatriculas& listaMatriculas, tGrupo& grupo) {
	int linea;
	string correo;
	int pos = 0;

	seleccionarMatricula(listaMatriculas, linea);
	cout << "Correo: ";
	cin >> correo;

	if ((grupo.cont < MAX_ALUMNOS) && (!buscarAlumno(grupo, listaMatriculas.matriculas[linea - 1]->nif, pos))) {
		insertarAlumno(grupo, listaMatriculas.matriculas[linea-1], correo);
	}
	else {
		cout << "NO se ha podido añadir al alumno." << endl;
	}

}

void mostrarAlumno(tAlumno& alumno) {
	cout << right << setw(25) << alumno.puntero->apellido << setw(20) << alumno.correo << endl;
}

void insertarAlumno(tGrupo& grupo, tMatricula* matricula, string& correo) {
	//grupo.alumnos[grupo.cont].puntero = new tMatricula;
	grupo.alumnos[grupo.cont].puntero = matricula;
	grupo.alumnos[grupo.cont].correo = correo;
	grupo.cont++;
	cout << "Alumno añadido correctamente al grupo." << endl;
}

bool buscarAlumno(tGrupo& grupo, string& nif, int& pos) {
	bool encontrado = false;

	while (!encontrado && pos < grupo.cont) {
		if (grupo.alumnos[pos].puntero->nif == nif) {
			encontrado = true;
		}
		else {
			pos++;
		}
	}

	return encontrado;
}

void eliminarAlumno(tGrupo& grupo, string& nif) {
	int pos = 0;

	buscarAlumno(grupo, nif, pos);
	for (int i = pos; i < grupo.cont; i++){
		grupo.alumnos[i] = grupo.alumnos[i + 1];
	}
	grupo.cont--;
}

void mostrarGrupo(tGrupo& grupo) {
	int pos = 0;

	while (pos < grupo.cont) {
		cout << right << setw(2) << pos+1 << ".";
		mostrarAlumno(grupo.alumnos[pos]);
		pos++;
	}
}

void liberar(tGrupo& grupo) {
//	for (int i = 0; i < grupo.cont; i++) {
//		delete grupo.alumnos[i].puntero;
//	}
	delete[] grupo.alumnos;
}

