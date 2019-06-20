#include "listaMatriculas.h"
using namespace std;

//Funciones auxiliares:
bool buscar(tListaMatriculas& lista, tMatricula& aux, int& ini, int& fin, int& pos); //Búsqueda Recursiva Binaria.
void iniciar(tMatricula& matricula, tMatricula& aux);

bool cargarMatriculas(tListaMatriculas& lista) {
	bool carga = false;
	ifstream archivo;
	tMatricula aux;
	int contAUX = 0;

	lista.cont = 0;
	lista.matriculas[lista.cont] = new tMatricula;

	archivo.open("matriculas.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar las matriculas." << endl;
	}
	else {
		archivo >> contAUX;
		while(!archivo.fail() && lista.cont < contAUX) {
			archivo.ignore();
			getline(archivo, aux.apellido);
			archivo >> aux.nombre;
			archivo >> aux.nif;
			archivo >> aux.tipo;
			archivo >> aux.asignaturas.cont;
			cargarAsignaturas(aux.asignaturas, archivo);

			aux.coste = 0;
			insertarMatricula(lista, aux);
		}
		carga = true;
	}

	return carga;
}

bool insertarMatricula(tListaMatriculas& lista, tMatricula& aux) {
	bool insertado = false;
	int pos = 0, ini = 0, fin = lista.cont - 1; //¡OJO! "fin" tiene que ser igual a "lista.cont - 1", si no, cuando hace la búsqueda, intenta comparar con la posición "lista.cont", la cual no está inicializada y da error.

	if (buscar(lista, aux, ini, fin, pos)) {
		iniciar(*lista.matriculas[pos], aux);
	}
	else {
		for (int i = lista.cont; i > pos; i--) {
			lista.matriculas[i] = lista.matriculas[i - 1];
		}
		lista.matriculas[pos] = new tMatricula;
		iniciar(*lista.matriculas[pos], aux);
		lista.cont++;
		insertado = true;
	}

	return insertado;
}

//
void iniciar(tMatricula& matricula, tMatricula& aux) {
	matricula.apellido = aux.apellido;
	matricula.nombre = aux.nombre;
	matricula.nif = aux.nif;
	matricula.coste = aux.coste;
	matricula.tipo = aux.tipo;
	matricula.asignaturas.cont = aux.asignaturas.cont;
	for (int i = 0; i < aux.asignaturas.cont; i++) {
		matricula.asignaturas.asignatura[i] = aux.asignaturas.asignatura[i];
		matricula.coste += (matricula.asignaturas.asignatura[i].creditos * 26.50);
	}
}
//

//
bool buscar(tListaMatriculas& lista, tMatricula& aux, int& ini, int& fin, int& pos) {
	bool encontrado = false;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (aux.apellido < lista.matriculas[pos]->apellido) {
			fin = pos - 1;
			encontrado = buscar(lista, aux, ini, fin, pos);
		}
		else if(lista.matriculas[pos]->apellido < aux.apellido){
			ini = pos + 1;
			encontrado = buscar(lista, aux, ini, fin, pos);
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}
//

void mostrarMatriculas(tListaMatriculas& lista) {
	cout << "La lista de matriculas cargada es: " << endl;
	for (int i = 0; i < lista.cont; i++){
		cout << right << setw(2) << i + 1 << "." << setw(25)
			<< lista.matriculas[i]->apellido << setw(20)
			<< lista.matriculas[i]->nif << setw(10)
			<< "(" << lista.matriculas[i]->asignaturas.cont << ")" << setw(5)
			<< lista.matriculas[i]->coste << endl;
	}
}

void seleccionarMatricula(tListaMatriculas& lista, int& linea) {
	cout << endl;
	mostrarMatriculas(lista);
	cout << endl;

	cout << "Introduce el numero de la linea del alumno que se quiere añadir al grupo: ";
	cin >> linea;
}

void liberar(tListaMatriculas& lista) {
	for (int i = 0; i < lista.cont; i++){
		delete lista.matriculas[i];
	}
}