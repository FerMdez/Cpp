//Examen Febrero 2018 - Grupos C, G e I
//Fernando Méndez Torrubiano
//Versión 2

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int MAX_NAV = 24;

//Tipos:
typedef struct tNavio {
	string nombre;
	string empresa;
	float eslora;
	float toneladas;
	bool peaje;
};
typedef tNavio tNavios[MAX_NAV];
typedef struct tListaNavios {
	tNavios navio;
	int contador;
};

//Funciones:
void inicializa(tListaNavios&);
bool cargar(tListaNavios&);
void muestraNavios(tListaNavios&);
bool crearNavio(tListaNavios&);
bool insertarNavio(tListaNavios&, tNavio&);
bool cobrarNavio(tListaNavios&, const string&);
float peajeNavio(tListaNavios&, const int&);
float peajePagado(tListaNavios&);
void ejecutarMenu(tListaNavios&);
int menu();
bool guardar(tListaNavios&);


int main() {
	tListaNavios navios;

	if (cargar(navios)) {
		ejecutarMenu(navios);
		if (guardar(navios)) {
			cout << "Guardado correctamente." << endl;
		}
		else {
			cout << "Error al guardar el archivo." << endl;
		}
	}
	else {
		cout << "Fin del programa." << endl;
	}

	return 0;
}

void inicializa(tListaNavios& navios) {
	navios.contador = 0;
	for (int i = 0; i < MAX_NAV; i++){
		navios.navio[i].nombre = "";
		navios.navio[i].empresa = "";
		navios.navio[i].eslora = 0;
		navios.navio[i].toneladas = 0;
		navios.navio[i].peaje = false;
	}
}

bool cargar(tListaNavios& navios) {
	bool cargado = false;
	ifstream archivo;
	string aux = "";

	inicializa(navios);
	archivo.open("navios.txt");
	if(!archivo.is_open()){
		cout << "No se ha podido cargar el archivo." << endl;
		cargado = false;
	}
	else {
		archivo >> navios.navio[navios.contador].nombre;
		while ((navios.navio[navios.contador].nombre != "XXX") && (navios.contador < MAX_NAV)) {
			archivo >> navios.navio[navios.contador].empresa;
			archivo >> navios.navio[navios.contador].eslora;
			archivo >> navios.navio[navios.contador].toneladas;
			archivo >> aux;
			if (aux == "true") {
				navios.navio[navios.contador].peaje = true;
			}
			else {
				navios.navio[navios.contador].peaje = false;
			}
			navios.contador++;
			archivo >> navios.navio[navios.contador].nombre;
		}
		cargado = true;
	}
	archivo.close();

	return cargado;
}

void muestraNavios(tListaNavios& navios) {
	cout << setw(15) << right << "NOMBRE"
		<< setw(20) << "EMPRESA"
		<< setw(10) << "ESLORA"
		<< setw(15) << "TONELADAS"
		<< setw(25) << "PEAJE" << endl;
	cout << setw(100) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < navios.contador; i++){
		cout << setw(15) << right << navios.navio[i].nombre
			<< setw(20) << navios.navio[i].empresa
			<< setw(10) << fixed << setprecision(2) << navios.navio[i].eslora
			<< setw(15) <<  setprecision(2) << navios.navio[i].toneladas;
		cout << setw(10) << peajeNavio(navios, i) << "$" << setw(12);
		if (navios.navio[i].peaje == true) {
			cout << "PAGADO." << endl;
		}
		else {
			cout << "NO PAGADO." << endl;
		}
	}
	cout << setw(100) << setfill('=') << "\n" << setfill(char(0));
	cout << "Total pagado: " << peajePagado(navios) << endl;
}

bool crearNavio(tListaNavios& navios) {
	tNavio nuevoNavio;

	cout << "Introduzca nombre del navio: ";
	cin >> nuevoNavio.nombre;
	cout << "Introduzca empressa fabricante: ";
	cin >> nuevoNavio.empresa;
	cout << "Introduzca eslora (en metros): ";
	cin >> nuevoNavio.eslora;
	cout << "Introduzca toneladas de carga: ";
	cin >> nuevoNavio.toneladas;
	nuevoNavio.peaje = false;

	return insertarNavio(navios, nuevoNavio);
}

bool insertarNavio(tListaNavios& navios, tNavio& nuevoNavio) {

	if (navios.contador < MAX_NAV){
		navios.navio[navios.contador].nombre = nuevoNavio.nombre;
		navios.navio[navios.contador].empresa = nuevoNavio.empresa;
		navios.navio[navios.contador].eslora = nuevoNavio.eslora;
		navios.navio[navios.contador].toneladas = nuevoNavio.toneladas;
		navios.navio[navios.contador].peaje = nuevoNavio.peaje;
		navios.contador++;
	}
	
	return (navios.contador < MAX_NAV) ? true : false;
}

bool cobrarNavio(tListaNavios& navios, const string& nombre) {
	int i = 0;
	bool encontrado = false;

	while ((!encontrado) && (i <= navios.contador)) {
		if (navios.navio[i].nombre == nombre) {
			navios.navio[i].peaje = true;
			encontrado = true;
		}
		else {
			i++;
		}
	}

	return (navios.navio[i].nombre == nombre) ? true : false;
}

float peajeNavio(tListaNavios& navios, const int& pos) {
	float pago = 0;

	if (navios.navio[pos].eslora <= 100) {
		pago = navios.navio[pos].toneladas * 2;
	}
	else {
		pago = navios.navio[pos].toneladas * 3;
	}
	
	return pago;
}

float peajePagado(tListaNavios& navios) {
	float total = 0;

	for (int i = 0; i < navios.contador; i++){
		if (navios.navio[i].peaje == true) {
			total += peajeNavio(navios, i);
		}
	}

	return total;
}

void ejecutarMenu(tListaNavios& navios) {
	int opc = 1;
	string nombre;

	while (opc != 0){
		opc = menu();
		switch (opc){
		case 0: break;
		case 1: muestraNavios(navios); break;
		case 2: 
			if (crearNavio(navios)) {
				cout << "Insertado correctamente." << endl;
			}
			else {
				cout << "Error al insertar." << endl;
			} 
			break;
		case 3: 
			cout << "Introduzca el nombre del navio a cobrar: ";
			cin >> nombre;
			if (cobrarNavio(navios, nombre)) {
				cout << "Cobrado." << endl;
			}
			else {
				cout << "Navio no encontrado." << endl;
			}
			break;
		default:
			break;
		}
		system("PAUSE");
		system("cls");
	}
}

int menu() {
	int opc = 0;

	cout << setw(20) << setfill('=') << "MENU" << setw(20) << "\n" << setfill(char(0));
	cout << "1.-Mostrar navios." << endl;
	cout << "2.-Insertar nuevo navio." << endl;
	cout << "3.-Realizar pago." << endl;
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 4);

	return opc;
}

bool guardar(tListaNavios& navios) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("navios.txt");
	if(!archivo.is_open()){
		cout << "Error al guardar." << endl;
		guardado = false;
	}
	else {
		for (int i = 0; i < navios.contador; i++){
			archivo << navios.navio[i].nombre << " "
				<< navios.navio[i].empresa << " "
				<< navios.navio[i].eslora << " "
				<< navios.navio[i].toneladas << " ";
			if (navios.navio[i].peaje == true) {
				archivo << "true" << endl;
			}
			else {
				archivo << "false" << endl;
			}
		}
		archivo << "XXX";
		guardado = true;
	}
	archivo.close();

	return guardado;
}