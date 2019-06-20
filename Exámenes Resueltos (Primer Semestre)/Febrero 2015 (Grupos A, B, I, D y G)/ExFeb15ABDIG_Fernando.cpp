//Exámen Febrero 2015 - Grupos A, B, D, I y G.
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int NUM_ASIG = 6;
const int MAX_RESERVAS = 3;

//Tipos:
typedef struct tAsignatura {
	string nombre;
	float creditos;
	int numGrupos;
};
typedef tAsignatura tAsignaturas[NUM_ASIG];

typedef struct tReserva {
	string nombre;
	int grupos;
};
typedef tReserva tReservas[MAX_RESERVAS];

typedef struct tProfesor {
	tAsignaturas asignatura;
	tReservas reserva;
	int contadorA;
	int contadorR;
};

//Funciones:
void inicia(tProfesor&);
bool cargar(tProfesor&);
bool guardar(tProfesor&);
void mostrarDisponibles(tProfesor&);
void leerReservas(tProfesor&);
int buscarAsignatura(tProfesor&, const string&);
void realizaReserva(tProfesor&, const int&);


int main() {
	tProfesor profesor;

	inicia(profesor);
	if (cargar(profesor)) {
		mostrarDisponibles(profesor);
		leerReservas(profesor); 
		mostrarDisponibles(profesor);
		if (guardar(profesor)) {
			cout << "Guardado correctamente." << endl;
		}
		else {
			cout << "Intentelo de nuevo." << endl;
		}
	}
	else {
		cout << "Fin del programa." << endl;
	}
	system("PAUSE");

	return 0;
}

void inicia(tProfesor& profesor) {
	profesor.contadorA = 0;
	profesor.contadorR = 0;
	for (int i = 0; i < NUM_ASIG; i++){
		profesor.asignatura[i].nombre = "";
		profesor.asignatura[i].creditos = 0;
		profesor.asignatura[i].numGrupos = 0;
		if (i < MAX_RESERVAS) {
			profesor.reserva[i].nombre = "";
			profesor.reserva[i].grupos = 0;
		}
	}
}

bool cargar(tProfesor& profesor) {
	bool carga = false;
	ifstream archivo;

	archivo.open("asignaturas.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar las asignaturas." << endl;
		carga = false;
	}
	else {
		archivo >> profesor.asignatura[profesor.contadorA].nombre;
		while ((profesor.asignatura[profesor.contadorA].nombre != "XXX") && (profesor.contadorA < NUM_ASIG)) {
			archivo >> profesor.asignatura[profesor.contadorA].creditos;
			archivo >> profesor.asignatura[profesor.contadorA].numGrupos;
			profesor.contadorA++;
			archivo >> profesor.asignatura[profesor.contadorA].nombre;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

bool guardar(tProfesor& profesor) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("asignaturas.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar las asignaturas." << endl;
		guardado = false;
	}
	else {
		for (int i = 0; i < profesor.contadorA; i++) {
			archivo << profesor.asignatura[i].nombre << " ";
			archivo << profesor.asignatura[i].creditos << " ";
			archivo << profesor.asignatura[i].numGrupos << endl;
		}
		archivo << "XXX";
		guardado = true;
	}
	archivo.close();

	return guardado;
}

void mostrarDisponibles(tProfesor& profesor) {
	cout << setw(3) << right << "NOMBRE"
		<< setw(10) << "CREDITOS"
		<< setw(20) << "GRUPOS DISPONIBLES" << endl;
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < profesor.contadorA; i++){
		if (profesor.asignatura[i].numGrupos > 0) {
			cout << setw(3) << right << profesor.asignatura[i].nombre
				<< setw(10) << profesor.asignatura[i].creditos
				<< setw(20) << profesor.asignatura[i].numGrupos << endl;
		}
	}
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));
}

void leerReservas(tProfesor& profesor) {
	string nombre;
	int existe = 0, numCreditos = 0;

	while ((nombre != "XXX") && (profesor.contadorR < MAX_RESERVAS)) {
		cout << "Introduzca nombre de la asignatura a reservar: ";
		cin >> nombre;
		existe = buscarAsignatura(profesor, nombre);
		if (existe != -1) {
			profesor.reserva[profesor.contadorR].nombre = nombre;
			realizaReserva(profesor, existe);
			numCreditos += profesor.asignatura[existe].creditos;
			profesor.contadorR++;
		}
		else {
			if (nombre != "XXX") {
				cout << "Asignatura no encontrada." << endl;
			}
		}
	}
	cout << endl << "Creditos reservados: " << numCreditos << endl << endl;
}

int buscarAsignatura(tProfesor& profesor, const string& nombre) {
	int i = NUM_ASIG - 1;
	bool encontrado = false;

	while ((profesor.asignatura[i].nombre != nombre) && (i > -1) && (!encontrado)) {
		if (profesor.asignatura[i].nombre == nombre) {
			encontrado = true;
		}
		else {
			i--;
		}
	}

	return i;
}

void realizaReserva(tProfesor& profesor, const int& pos) {
	int numGrupos = 0, resta = 0;

	do {
		cout << "Grupos a reservar (Quedan " << profesor.asignatura[pos].numGrupos << " grupos): ";
		cin >> numGrupos;
		resta = profesor.asignatura[pos].numGrupos - numGrupos;
	} while (resta < 0);

	profesor.asignatura[pos].numGrupos -= numGrupos;
}