//Exámen Febro de 2016.
//Grupos F y G.
//Fernando Méndez Torubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int NUM_EQUIPOS = 25;

//Tipos:
typedef enum tCategoria{principiante, intermedio, avanzado, experto};
typedef struct tEquipo {
	string nombre;
	tCategoria liga;
	int partidasJugadas;
	int partidasGanadas;
	bool disponible;

};
typedef tEquipo tEquipos[NUM_EQUIPOS];
typedef struct tListaEquipos {
	tEquipos equipo;
	int contador;
};

//Funciones:
void inicializa(tListaEquipos&);
bool cargarDatos(tListaEquipos&);
void guardarDatos(tListaEquipos&);
void tInttoLiga(tListaEquipos&, const int);
int menu();
void ejecutarMenu(tListaEquipos&);
void jugarPartida(tListaEquipos&);
bool buscarEquipos(tListaEquipos&, const string, int&);
bool buscarContrarios(tListaEquipos&, const int, string&);
void apuntarResultado(tListaEquipos&);
void actualizarGanador(tListaEquipos&, const int&);
void actualizarPerdedor(tListaEquipos&, const int&);

int main() {
	tListaEquipos equipos;

	if (cargarDatos(equipos)) {
		ejecutarMenu(equipos);
	}
	else {
		cout << "Fin del programa." << endl;
		system("PAUSE");
	}

	return 0;
}

void inicializa(tListaEquipos& equipos) {
	equipos.contador = 0;
	for (int i = 0; i < NUM_EQUIPOS; i++){
		equipos.equipo[i].nombre = "";
		equipos.equipo[i].liga = principiante;
		equipos.equipo[i].partidasJugadas = 0;
		equipos.equipo[i].partidasGanadas = 0;
		equipos.equipo[i].disponible = false;
	}
}

bool cargarDatos(tListaEquipos& equipos) {
	bool carga = false;
	ifstream archivo;
	int AUXliga = 0;

	inicializa(equipos);
	archivo.open("equipos.txt");
	if (!archivo.is_open()) {
		cout << "Archivo no encontrado." << endl;
		carga = false;
	}
	else {
		archivo >> equipos.equipo[equipos.contador].nombre;
		while ((equipos.equipo[equipos.contador].nombre != "XXX") && (equipos.contador < NUM_EQUIPOS)) {
			archivo >> AUXliga;
			tInttoLiga(equipos, AUXliga);
			archivo >> equipos.equipo[equipos.contador].partidasJugadas;
			archivo >> equipos.equipo[equipos.contador].partidasGanadas;
			archivo >> equipos.equipo[equipos.contador].disponible;
			equipos.contador++;
			archivo >> equipos.equipo[equipos.contador].nombre;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void tInttoLiga(tListaEquipos& equipos, const int AUXliga) {
	switch (AUXliga){
	case 0: equipos.equipo[equipos.contador].liga = principiante; break;
	case 1: equipos.equipo[equipos.contador].liga = intermedio; break;
	case 2: equipos.equipo[equipos.contador].liga = avanzado; break;
	case 3: equipos.equipo[equipos.contador].liga = experto; break;
	}
}

int menu() {
	int opc = 0;

	cout << setw(25) << setfill('=') << "\n";
	cout << "1.- Jugar Partida." << endl;
	cout << "2.- Apuntar resultado." << endl;
	cout << "0.- Salir." << endl;
	cout << setw(25) << setfill('=') << "\n" << setw(0) << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 2);

	return opc;
}

void ejecutarMenu(tListaEquipos& equipos) {
	int opc = 1;

	while (opc != 0) {
		opc = menu();
		switch (opc){
		case 1: jugarPartida(equipos); break;
		case 2: apuntarResultado(equipos); break;
		case 0: guardarDatos(equipos); break;
		default:
			break;
		}
		system("cls");
	}
}

void jugarPartida(tListaEquipos& equipos) {
	string nomEquipo, nomContrario;
	int pos = 0;

	cout << "Introduzca el nombre de su equipo: ";
	cin >> nomEquipo;
	if (buscarEquipos(equipos, nomEquipo, pos)) {
		if (buscarContrarios(equipos, pos, nomContrario)) {
			cout << "Rival encontrado: " << nomContrario << endl;
		}
		else {
			equipos.equipo[pos].disponible = true;
		}
	}
	else {
		cout << "Equipo no encontrado." << endl;
	}
	system("PAUSE");
}

bool buscarEquipos(tListaEquipos& equipos, const string nomEquipo, int& posicion) {
	bool encontrado = false;

	while ((!encontrado) && (posicion < equipos.contador)) {
		if (equipos.equipo[posicion].nombre == nomEquipo) {
			encontrado = true;
		}
		else {
			posicion++;
		}
	}
	return encontrado;
}

bool buscarContrarios(tListaEquipos& equipos, const int pos, string& nomContrario) {
	bool encontrado = false;
	int i = 0;
	int numPartidasJugadas = 25;

	for (int i = 0; i < equipos.contador; i++) {
		if ((equipos.equipo[i].liga == equipos.equipo[pos].liga) && (i != pos) && (numPartidasJugadas >= equipos.equipo[i].partidasJugadas)) {
			numPartidasJugadas = equipos.equipo[i].partidasJugadas;
		}
	}

	while ((!encontrado) && (i < equipos.contador)) {
		if ((equipos.equipo[i].liga == equipos.equipo[pos].liga) && (i != pos) && (numPartidasJugadas == equipos.equipo[i].partidasJugadas)) {
			nomContrario = equipos.equipo[i].nombre;
			encontrado = true;
		}
		else {
			i++;
		}
	}

	return encontrado;
}

void apuntarResultado(tListaEquipos& equipos) {
	string nomGanador, nomPerdedor;
	int posGanador = 0, posPerdedor = 0;

	do {
		cout << "Introduzca el nombre del equipo GANADOR: ";
		cin >> nomGanador;
	} while (!buscarEquipos(equipos, nomGanador, posGanador));
	actualizarGanador(equipos, posGanador);

	do {
		cout << "Introduzca el nombre del equipo PERDEDOR: ";
		cin >> nomPerdedor;
	} while (!buscarEquipos(equipos, nomPerdedor, posPerdedor));
	actualizarPerdedor(equipos, posPerdedor);

	cout << endl << "Resultados actualizados correctamente." << endl;
	system("PAUSE");
}

void actualizarGanador(tListaEquipos& equipos, const int& pos) {
	int partidasPerdidas = 0, diferencia = 0;

	equipos.equipo[pos].partidasJugadas++;
	equipos.equipo[pos].partidasGanadas++;

	partidasPerdidas = equipos.equipo[pos].partidasJugadas - equipos.equipo[pos].partidasGanadas;
	diferencia = equipos.equipo[pos].partidasGanadas - partidasPerdidas;
	if (diferencia > 25) {
		switch (equipos.equipo[pos].liga) {
		case principiante: equipos.equipo[pos].liga = intermedio; break;
		case intermedio: equipos.equipo[pos].liga = avanzado; break;
		case avanzado: equipos.equipo[pos].liga = experto; break;
		case experto: equipos.equipo[pos].liga = experto; break;
		}
		equipos.equipo[pos].partidasJugadas = 0;
		equipos.equipo[pos].partidasGanadas = 0;
	}
	
	equipos.equipo[pos].disponible = false;
}

void actualizarPerdedor(tListaEquipos& equipos, const int& pos) {
	int partidasPerdidas = 0;

	equipos.equipo[pos].partidasJugadas++;

	partidasPerdidas = equipos.equipo[pos].partidasJugadas - equipos.equipo[pos].partidasGanadas;
	if (partidasPerdidas > 20) {
		switch (equipos.equipo[pos].liga) {
		case principiante: equipos.equipo[pos].liga = principiante; break;
		case intermedio: equipos.equipo[pos].liga = principiante; break;
		case avanzado: equipos.equipo[pos].liga = intermedio; break;
		case experto: equipos.equipo[pos].liga = avanzado; break;
		}
		equipos.equipo[pos].partidasJugadas = 0;
		equipos.equipo[pos].partidasGanadas = 0;
	}

	equipos.equipo[pos].disponible = false;
}

void guardarDatos(tListaEquipos& equipos) {
	ofstream archivo;

	archivo.open("equipos.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar el archivo." << endl;
		system("PAUSE");
	}
	else {
		for (int i = 0; i < equipos.contador; i++){
			archivo << equipos.equipo[i].nombre << endl;
			archivo << equipos.equipo[i].liga << " ";
			archivo << equipos.equipo[i].partidasJugadas << " ";
			archivo << equipos.equipo[i].partidasGanadas << " ";
			archivo << equipos.equipo[i].disponible << endl;
		}
		archivo << "XXX";
	}
	archivo.close();
}