//Exámen Febrero 2014 - Grupos C, E y F.
//Fernando Méndez Torrubinao

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


//Constantes:
const int NUM_PLAYERS = 10;

//Tipos:
typedef struct tJugador {
	string nombre;
	string equipo;
	int numPartidos;
	int minutos;
	int goles;
};
typedef tJugador tJugadores[NUM_PLAYERS];
typedef struct tListaJugadores {
	tJugadores jugador;
	int contador;
};

//Funciones:
void inicializa(tListaJugadores&);
bool cargar(tListaJugadores&);
void ejecutarMenu(tListaJugadores&);
int menu();
void filtrarLista(tListaJugadores&, const string&);
bool actualizarJugador(tListaJugadores&, const string&, const int&, const int&, int& pos);
void consultarMaxGoleador(tListaJugadores& jugadores);
void guardar(tListaJugadores&);

int main() {
	tListaJugadores jugadores;

	if (cargar(jugadores)) {
		ejecutarMenu(jugadores);
		guardar(jugadores);
	}
	else {
		cout << "Fin del programa." << endl;
		system("PAUSE");
	}

	return 0;
}

void inicializa(tListaJugadores& jugadores) {
	jugadores.contador = 0;
	for (int i = 0; i < NUM_PLAYERS; i++){
		jugadores.jugador[i].nombre = "";
		jugadores.jugador[i].equipo = "";
		jugadores.jugador[i].numPartidos = 0;
		jugadores.jugador[i].minutos = 0;
		jugadores.jugador[i].goles = 0;
	}
}

bool cargar(tListaJugadores& jugadores) {
	bool cargado = false;
	ifstream archivo;

	inicializa(jugadores);
	archivo.open("players.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar el archivo." << endl;
		cargado = false;
	}
	else {
		archivo >> jugadores.jugador[jugadores.contador].nombre;
		while ((jugadores.jugador[jugadores.contador].nombre != "XXX") && (jugadores.contador < NUM_PLAYERS)) {
			archivo >> jugadores.jugador[jugadores.contador].equipo;
			archivo >> jugadores.jugador[jugadores.contador].numPartidos;
			archivo >> jugadores.jugador[jugadores.contador].minutos;
			archivo >> jugadores.jugador[jugadores.contador].goles;
			jugadores.contador++;
			archivo >> jugadores.jugador[jugadores.contador].nombre;
		}
		cargado = true;
	}
	archivo.close();

	return cargado;
}

void ejecutarMenu(tListaJugadores& jugadores) {
	int opc = 1;
	string codigo, nombre;
	int min, goles, pos = 0;;

	while (opc != 0) {
		opc = menu();
		switch (opc){
		case 0: break;
		case 1:
			cout << "Introduzca equipo ('TODOS' para ver todos los jugadores): ";
			cin >> codigo;
			filtrarLista(jugadores, codigo); 
			break;
		case 2:
			cout << "Introduzca nombre del jugador: ";
			cin >> nombre;
			cout << "Introduzca minutos jugados: ";
			cin >> min;
			cout << "Introduzca goles marcados: ";
			cin >> goles;
			if (actualizarJugador(jugadores, nombre, min, goles, pos)) {
				cout << "Actualizado correctamente:" << endl;
				cout << setw(25) << setfill('-') << "\n" << setfill(char(0))
					<< jugadores.jugador[pos].nombre << setw(5)
					<< jugadores.jugador[pos].equipo << setw(5)
					<< jugadores.jugador[pos].numPartidos << setw(5)
					<< jugadores.jugador[pos].minutos << setw(5)
					<< jugadores.jugador[pos].goles << endl
					<< setw(25) << setfill('-') << "\n" << setfill(char(0));
			}
			else {
				cout << "Error al actualizar" << endl;
			}
			break;
		case 3: consultarMaxGoleador(jugadores); break;
		default:
			break;
		}
		system("PAUSE");
		system("cls");
	}
}

int menu() {
	int opc = 0;

	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));
	cout << "1.-Filtrar lista." << endl;
	cout << "2.-Actualizar jugador." << endl;
	cout << "3.-Consultar maximo goleador" << endl;
	cout << "0.-SALIR" << endl;
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 3);

	return opc;
}

void filtrarLista(tListaJugadores& jugadores, const string& codigo) {
	cout << setw(70) << setfill('_') << "\n" << setfill(char(0));
	cout << endl << setw(15) << right << "JUGADOR"
		<< setw(20) << "PARTIDOS JUGADOS"
		<< setw(20) << "MINUTOS JUGADOS"
		<< setw(10) << "GOLES" << endl;
	cout << setw(70) << setfill('_') << "\n" << endl;
	cout << setw(35) << setfill('=') << codigo << setw(35) << "\n" << setfill(char(0));
	for (int i = 0; i < jugadores.contador; i++){
		if ((jugadores.jugador[i].equipo == codigo) || (codigo == "TODOS") || (codigo == "todos")) {
			cout << setw(15) << right << jugadores.jugador[i].nombre
				<< setw(15) << jugadores.jugador[i].numPartidos
				<< setw(20) << jugadores.jugador[i].minutos
				<< setw(15) << jugadores.jugador[i].goles << endl;
		}
	}
	cout << setw(70) << setfill('=') << "\n" << setfill(char(0));
}

bool actualizarJugador(tListaJugadores& jugadores, const string& nombre, const int& min, const int& goles, int& i) {
	bool actualizado = false;

	while ((!actualizado) && (i < jugadores.contador)) {
		if ((jugadores.jugador[i].nombre == nombre) && (min > 0) && (goles > 0)) {
			jugadores.jugador[i].minutos += min;
			jugadores.jugador[i].goles += goles;
			jugadores.jugador[i].numPartidos++;
			actualizado = true;
		}
		else {
			i++;
		}
	}

	return actualizado;
}

void consultarMaxGoleador(tListaJugadores& jugadores) {
	int maxGoles = 0;
	tListaJugadores goleadores;

	for (int i = 0; i < jugadores.contador; i++){
		if (jugadores.jugador[i].goles > maxGoles) {
			maxGoles = jugadores.jugador[i].goles;
		}
	}

	goleadores.contador = 0;
	cout << setw(20) << setfill('-') << "PICHICHIS" << setw(20) << setfill('-') << "\n" << setfill(char(0));
	for (int i = 0; i < jugadores.contador; i++){
		if (jugadores.jugador[i].goles == maxGoles) {
			goleadores.jugador[goleadores.contador].nombre = jugadores.jugador[i].nombre;
			goleadores.jugador[goleadores.contador].equipo = jugadores.jugador[i].equipo;
			goleadores.jugador[goleadores.contador].numPartidos = jugadores.jugador[i].numPartidos;
			goleadores.jugador[goleadores.contador].minutos = jugadores.jugador[i].minutos;
			goleadores.jugador[goleadores.contador].goles = jugadores.jugador[i].goles;
			cout << setw(10) << right << goleadores.jugador[goleadores.contador].nombre << setw(5)
				<< goleadores.jugador[goleadores.contador].equipo << setw(5)
				<< goleadores.jugador[goleadores.contador].numPartidos << setw(5)
				<< goleadores.jugador[goleadores.contador].minutos << setw(5)
				<< goleadores.jugador[goleadores.contador].goles << endl;
			goleadores.contador++;
		}
	}
	cout << setw(40) << setfill('-') << "\n" << setfill(char(0));
	
}

void guardar(tListaJugadores& jugadores) {
	ofstream archivo;

	archivo.open("players.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar." << endl;
		system("PAUSE");
	}
	else {
		for (int i = 0; i < jugadores.contador; i++){
			archivo << jugadores.jugador[i].nombre << " "
				<< jugadores.jugador[i].equipo << " "
				<< jugadores.jugador[i].numPartidos << " "
				<< jugadores.jugador[i].minutos << " "
				<< jugadores.jugador[i].goles << endl;
		}
		archivo << "XXX";
	}
	archivo.close();
}