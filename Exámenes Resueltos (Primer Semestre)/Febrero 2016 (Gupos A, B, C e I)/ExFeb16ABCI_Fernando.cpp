//Exámen Febrero 2016 - Grupos A, B, C e I
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int N = 50;

//Tipos:
typedef enum { embarcando, operado, retrasado, suspendido }tEstado;
typedef struct {
	string numVuelo;
	char terminal;
	int puertaEmb;
	tEstado estVuelo;
	string destino;
}tVuelo;
typedef tVuelo tVuelos[N];
typedef struct {
	tVuelos vuelo;
	int contador;
}tListaVuelos;

//Funciones:
void inizializa(tListaVuelos&);
bool cargar(tListaVuelos&);
void tIntToEstado(tListaVuelos&, const int);
int menu();
void ejecutarMenu(tListaVuelos&);
void guardar(tListaVuelos&);
void obtenerInfoVuelo(tListaVuelos&);
void actualizaEstVuelo(tListaVuelos&);
int buscarVuelo(tListaVuelos&, const string&);
void mostrarVuelo(tListaVuelos&, const string&);
void actualizarVuelo(tListaVuelos&, const int&, const int&);


int main() {
	tListaVuelos vuelos;

	if (cargar(vuelos)) {
		ejecutarMenu(vuelos);
	}
	else {
		cout << "Fin del programa." << endl;
		system("PAUSE");
	}

	return 0;
}

void inicializa(tListaVuelos& vuelos) {
	vuelos.contador = 0;
	for (int i = 0; i < N; i++) {
		vuelos.vuelo[i].numVuelo = "";
		vuelos.vuelo[i].terminal = char(0);
		vuelos.vuelo[i].puertaEmb = 0;
		vuelos.vuelo[i].estVuelo = suspendido;
		vuelos.vuelo[i].destino = "";
	}
}

bool cargar(tListaVuelos& vuelos) {
	bool carga = false;
	int AUX;
	ifstream archivo;

	inicializa(vuelos);
	archivo.open("salidas.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar el archivo." << endl;
		carga = false;
	}
	else {
		archivo >> vuelos.vuelo[vuelos.contador].numVuelo;
		while ((vuelos.vuelo[vuelos.contador].numVuelo != "XXX") && (vuelos.contador < N)) {
			archivo >> vuelos.vuelo[vuelos.contador].terminal;
			archivo >> vuelos.vuelo[vuelos.contador].puertaEmb;
			archivo >> AUX;
			tIntToEstado(vuelos, AUX);
			getline(archivo, vuelos.vuelo[vuelos.contador].destino);
			vuelos.contador++;
			archivo >> vuelos.vuelo[vuelos.contador].numVuelo;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void tIntToEstado(tListaVuelos& vuelos, const int AUX) {
	switch (AUX) {
		case 0: vuelos.vuelo[vuelos.contador].estVuelo = embarcando; break;
		case 1: vuelos.vuelo[vuelos.contador].estVuelo = operado; break;
		case 2: vuelos.vuelo[vuelos.contador].estVuelo = retrasado; break;
		case 3: vuelos.vuelo[vuelos.contador].estVuelo = suspendido; break;
	}
}

int menu() {
	int opc = 0;

	cout << setw(40) << setfill('=') << "\n";
	cout << "1.-Obtener informacion de un vuelo." << endl;
	cout << "2.-Actualizar estado del un vuelo." << endl;
	cout << "0.-Salir." << endl;
	cout << setw(40) << setfill('=') << "\n" << setw(0) << setfill(char(0));
	
	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 2);

	return opc;
}

void ejecutarMenu(tListaVuelos& vuelos) {
	int opc = 1;
	while (opc != 0) {
		opc = menu();
		switch (opc) {
		case 1: obtenerInfoVuelo(vuelos); break;
		case 2: actualizaEstVuelo(vuelos); break;
		case 0: guardar(vuelos); break;
		}
		system("cls");
	}
}

void guardar(tListaVuelos& vuelos) {
	ofstream archivo;

	archivo.open("pendientes.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar." << endl;
	}
	else {
		for (int i = 0; i < vuelos.contador; i++){
			if ((vuelos.vuelo[i].estVuelo == retrasado) || (vuelos.vuelo[i].estVuelo == suspendido)) {
				archivo << vuelos.vuelo[i].numVuelo << " ";
				archivo << vuelos.vuelo[i].terminal << " ";
				archivo << vuelos.vuelo[i].puertaEmb << " ";
				archivo << vuelos.vuelo[i].estVuelo << "";
				archivo << vuelos.vuelo[i].destino << endl;
			}
		}
	}
	archivo.close();
}

void obtenerInfoVuelo(tListaVuelos& vuelos) {
	string numVuelo;
	int encontrado;

	cout << "Introduzca numero de vuelo: ";
	cin >> numVuelo;

	encontrado = buscarVuelo(vuelos, numVuelo);
	if (encontrado != -1) {
		mostrarVuelo(vuelos, numVuelo);
	}
	else {
		cout << "Vuelo no encontrado." << endl;
	}
	system("PAUSE");
}

void actualizaEstVuelo(tListaVuelos& vuelos) {
	string numVuelo;
	int encontrado;
	int nuevoEst;

	do {
		cout << "Introduzca un numero de vuelo: ";
		cin >> numVuelo;
		encontrado = buscarVuelo(vuelos, numVuelo);
	} while (encontrado == -1);

	cout << endl << "ESTADOS: (0)embarcando, (1)operado, (2)retrasado, (3)suspendido." << endl;
	cout << "Introduzca un nuevo estado: ";
	cin >> nuevoEst;
	actualizarVuelo(vuelos, encontrado, nuevoEst);
	cout << "Actualizado correctamente." << endl;
	system("PAUSE");
}

int buscarVuelo(tListaVuelos& vuelos, const string& numVuelo) {
	int pos = 0;

	while ((vuelos.vuelo[pos].numVuelo != numVuelo) && (pos < vuelos.contador)) {
		pos++;
	}
	if (pos == vuelos.contador) {
		pos = -1;
	}

	return pos;
}

void mostrarVuelo(tListaVuelos& vuelos, const string& numVuelo) {
	int pos = buscarVuelo(vuelos, numVuelo);

	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
	cout << "Numero de vuelo: " << setw(15) << vuelos.vuelo[pos].numVuelo << endl
		<< "Terminal: " << setw(15) << vuelos.vuelo[pos].terminal << endl
		<< "Puerta de Embarque: " << setw(15) << vuelos.vuelo[pos].puertaEmb << endl
		<< "Estado: " << setw(15) << vuelos.vuelo[pos].estVuelo << endl
		<< "Destino: " << setw(15) << vuelos.vuelo[pos].numVuelo << endl;
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
}

void actualizarVuelo(tListaVuelos& vuelos, const int& pos, const int& estadVuelo) {
	switch (estadVuelo) {
	case 0: vuelos.vuelo[pos].estVuelo = embarcando; break;
	case 1: vuelos.vuelo[pos].estVuelo = operado; break;
	case 2: vuelos.vuelo[pos].estVuelo = retrasado; break;
	case 3: vuelos.vuelo[pos].estVuelo = suspendido; break;
	}
}