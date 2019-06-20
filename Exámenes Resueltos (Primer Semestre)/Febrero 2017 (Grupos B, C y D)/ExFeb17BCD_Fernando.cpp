//Examen Febrero 2017 - Grupos B, C y D
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int N = 10;

//Tipos:
typedef struct tEquipo {
	string nombre;
	int puntos;
};
typedef struct tJornada {
	string local, visitante;
	int golesLocal, golesVisitante;
};
typedef tEquipo tEquipos[N];
typedef tJornada tPartidos[N / 2];
typedef struct tListaEquipos {
	tEquipos equipo;
	tPartidos partido;
	//En este examen no se necesita un contador.
};

//Funciones:
void inicia(tListaEquipos&);
bool cargarLiga(tListaEquipos&);
bool cargarJornada(tListaEquipos&);
void mostrarLiga(tListaEquipos&);
void mostrarJornada(tListaEquipos&);
int menu();
void ejecutarMenu(tListaEquipos&);
bool actualizarLiga(tListaEquipos&);
void mostrarPrimero(tListaEquipos&);
void guardarLiga(tListaEquipos&);
void ordenar(tListaEquipos&);

int main() {
	tListaEquipos equipos;

	inicia(equipos);
	if ((cargarLiga(equipos)) && (cargarJornada(equipos))) {
		ejecutarMenu(equipos);
		guardarLiga(equipos);
	}
	else {
		cout << "FIN DEL PROGRAMA." << endl;
		system("PAUSE");
	}

	return 0;
}

void inicia(tListaEquipos& equipos) {
	for (int i = 0; i < N; i++){
		equipos.equipo[i].nombre = "";
		equipos.equipo[i].puntos = 0;
		if (i < N / 2) {
			equipos.partido[i].local = "";
			equipos.partido[i].visitante = "";
			equipos.partido[i].golesLocal = 0;
			equipos.partido[i].golesVisitante = 0;
		}
	}
}

bool cargarLiga(tListaEquipos& equipos) {
	bool carga = false;
	ifstream archivo;
	
	archivo.open("liga.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar la liga." << endl;
		carga = false;
	}
	else {
		for (int i = 0; i < N; i++) {
			archivo >> equipos.equipo[i].nombre;
			archivo >> equipos.equipo[i].puntos;
		}
		ordenar(equipos);
		carga = true;
	}
	archivo.close();

	return carga;
}

void ordenar(tListaEquipos& equipos) {
	string auxiliar;
	int aux, pos;

	for (int i = 0; i < N; i++) {
		pos = i;
		while ((equipos.equipo[pos].puntos > equipos.equipo[pos - 1].puntos) && (pos > 0)) {
			auxiliar = equipos.equipo[pos].nombre;
			equipos.equipo[pos].nombre = equipos.equipo[pos - 1].nombre;
			equipos.equipo[pos - 1].nombre = auxiliar;

			aux = equipos.equipo[pos].puntos;
			equipos.equipo[pos].puntos = equipos.equipo[pos - 1].puntos;
			equipos.equipo[pos - 1].puntos = aux;

			pos--;
		}
	}
}

bool cargarJornada(tListaEquipos& equipos) {
	bool carga = false;
	ifstream archivo;

	archivo.open("jornada.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar la jornada." << endl;
		carga = false;
	}
	else {
		for (int i = 0; i < N / 2; i++) {
			archivo >> equipos.partido[i].local;
			archivo >> equipos.partido[i].golesLocal;
			archivo >> equipos.partido[i].visitante;
			archivo >> equipos.partido[i].golesVisitante;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void mostrarLiga(tListaEquipos& equipos) {
	cout << setw(7) << right << "EQUIPO" << setw(15) << right << "PUNTOS" << endl;
	cout << setfill('=') << setw(25) << "\n" << setfill(char(0)) << setw(0);
	for (int i = 0; i < N; i++){
		cout << setw(7) << right << equipos.equipo[i].nombre 
			<< setw(15) << right << equipos.equipo[i].puntos << endl;
	}
	cout << setfill('=') << setw(25) << "\n" << setfill(char(0)) << setw(0);
}

void mostrarJornada(tListaEquipos& equipos) {
	cout << setw(5) << right << "LOCAL" << setw(10) << "GOLES" << setw(20) << "VISITANTE" << setw(10) << "GOLES" << endl;
	cout << setfill('=') << setw(50) << "\n" << setfill(char(0)) << setw(0);
	for (int i = 0; i < N/2; i++) {
		cout << setw(4) << right << equipos.partido[i].local << left
			<< setw(2) << right << setw(10) << equipos.partido[i].golesLocal << left
			<< setw(4) << right <<setw(20) << equipos.partido[i].visitante << left
			<< setw(2) << right <<setw(10) << equipos.partido[i].golesVisitante << endl;
	}
	cout << setfill('=') << setw(50) << "\n" << setfill(char(0)) << setw(0);
}

int menu() {
	int opc = 0;

	cout << setw(35) << setfill('=') << "\n" << setfill(char(0)) << setw(0);
	cout << "1.-MOSTRAR CLASIFICACION DE LA LIGA." << endl;
	cout << "2.-MOSTRAR ULTIMA JORNADA." << endl;
	cout << "3.-ACTUALIZAR LIGA." << endl;
	cout << "4.-MOSTRAR PRIMER CLASIFICADO." << endl;
	cout << "0.-SALIR." << endl;
	cout << setw(35) << setfill('=') << "\n" << setfill(char(0)) << setw(0);

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 4);

	return opc;
}

void ejecutarMenu(tListaEquipos& equipos) {
	int opc = 1;

	while (opc != 0) {
		opc = menu();
		switch (opc) {
		case 1: mostrarLiga(equipos); break;
		case 2: mostrarJornada(equipos); break;
		case 3: if (actualizarLiga(equipos)) { cout << "ACTUALIZADA CORRECTAMENTE." << endl; }
				else { cout << "ERROR AL ACTUALIZAR." << endl; } break;
		case 4: mostrarPrimero(equipos); break;
		case 0: break;
		}
		system("Pause");
		system("cls");
	}
}

bool actualizarLiga(tListaEquipos& equipos) {
	bool encontrado = false;
	int j = 0;

	for (int i = 0; i < N/2; i++){
		if (equipos.partido[i].golesLocal > equipos.partido[i].golesVisitante) {
			j = 0;
			while (!encontrado && j < N) {
				if (equipos.equipo[j].nombre == equipos.partido[i].local) {
					equipos.equipo[j].puntos += 3;
					encontrado = true;
				}
				j++;
			}
		}
		if (equipos.partido[i].golesLocal < equipos.partido[i].golesVisitante) {
			j = 0;
			while (!encontrado && j < N) {
				if (equipos.equipo[j].nombre == equipos.partido[i].visitante) {
					equipos.equipo[j].puntos += 3;
				}
				j++;
			}
		}
		if (equipos.partido[i].golesLocal == equipos.partido[i].golesVisitante) {
			j = 0;
			while (j < N) {
				if (equipos.equipo[j].nombre == equipos.partido[i].local) {
					equipos.equipo[j].puntos += 1;
				}
				if (equipos.equipo[j].nombre == equipos.partido[i].visitante) {
					equipos.equipo[j].puntos += 1;
				}
				j++;
			}
			encontrado = true;
		}
	}
	ordenar(equipos);

	return encontrado;
}

void mostrarPrimero(tListaEquipos& equipos) {
	ordenar(equipos);
	cout << "Primer equipo en la liga: " << equipos.equipo[0].nombre << " con " << equipos.equipo[0].puntos << " puntos." << endl;
}

void guardarLiga(tListaEquipos& equipos) {
	ofstream archivo;

	archivo.open("liga.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar los datos." << endl;
	}
	else {
		for (int i = 0; i < N; i++) {
			archivo << equipos.equipo[i].nombre << " ";
			archivo << equipos.equipo[i].puntos << endl;
		}
	}
	archivo.close();
}