/*
Apellidos: Verdú Rodríguez
Nombre: Eva
DNI: 51220965B
Puesto: 15
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
using namespace std;

//Constantes:
const int MAX_NAV = 24;
const string CENT = "XXX";

typedef struct tNavios{
	string nom;
	string empr;
	float esl;
	float ton;
	string pag;
};

typedef tNavios tListaNav[MAX_NAV];

typedef struct tListaNavios {
	tListaNav lista;
	int cont;
};

//Funciones:
int menu();
bool cargar(tListaNavios & lista); //Carga el archivo.
void muestraNavios(const tListaNavios lista);
float peajeNavio(const tNavios navio);
float peajePagado(const tListaNavios lista);
void crearNavio(tListaNavios & lista);
bool insertaNavio(const tNavios navio, tListaNavios & lista);
bool cobrarNavio(tListaNavios & lista, string name);


int main() {
	tListaNavios lista;
	string name;
	bool cobrar = true;
	bool ok = cargar(lista);
	int opc=0;
	if (ok) {
		do{
			opc = menu();
			switch (opc) {
			case 1:
				muestraNavios(lista);
				break;
			case 2:
				crearNavio(lista);
				break;
			case 3:
				cout << "Introduce Nombre del Navio: ";
				cin >> name;
				cobrar = cobrarNavio(lista , name);
				if (!cobrar) {
					cout << "Error. Barco no encontrado" << endl;
				}
				break;
			}
		} while (opc != 0);
	}
	else {
		cout << "Error al abrir el archivo" << endl;
	}
	system("pause");
	return 0;
}

int menu() {
	int opc;
	cout << "---------------------------------" << endl;
	cout << "Elige una opcion: " << endl;
	cout << "1 - Muestra la lista" << endl;
	cout << "2 - Nuevo navio" << endl;
	cout << "3 - Pagar navio" << endl;
	cout << "0 - Salir" << endl;
	cout << "---------------------------------" << endl;
	cin >> opc;
	while (opc < 0 || opc > 3) {
		cout << "Error. Ponga un valor entre 0 y 3." << endl;
	}
	return opc;
}

bool cargar(tListaNavios & lista){
	bool ok = true;
	string aux;
	ifstream archivo;
	lista.cont = 0;

	archivo.open("navios.txt");
	if (archivo.is_open()) {
		archivo >> lista.lista[lista.cont].nom;
		while((lista.lista[lista.cont].nom != CENT) && (lista.cont < MAX_NAV)) {
			archivo >> lista.lista[lista.cont].empr;
			archivo >> lista.lista[lista.cont].esl;
			archivo >> lista.lista[lista.cont].ton;
			archivo >> lista.lista[lista.cont].pag;
			lista.cont++;
			archivo >> lista.lista[lista.cont].nom;
		}
		archivo.close();
	}
	else {
		ok = false;
	}
	
	return ok;
}

void muestraNavios(const tListaNavios lista) {
	int i = 0;
	float peaje = 0;
	cout << "Navio" << setw(20) << "Empresa" << setw(20) << "Eslora" << setw(20) << "Toneladas" << setw(20) << "Peaje" << setw(20) << endl;
	cout << setw(100) << setfill('=') << "\n";
	cout << setw(100) << setfill(' ') << "\n";
	for (int i = 0; i < lista.cont; i++){
		cout << setw(20) << left << lista.lista[i].nom;
		cout << setw(20) << lista.lista[i].empr;
		cout << fixed << setprecision(2) << setw(15) << lista.lista[i].esl;
		cout << setw(15) << lista.lista[i].ton;
		peaje = peajeNavio(lista.lista[i]);
		if (lista.lista[i].pag == "true") {
			cout << setw(10) << right << peaje  << " Pagado"  << endl;
		}
		else {
			cout << setw(10) << right << peaje << " No Pagado" << endl;
		}
	}
	cout << setw(100) << setfill('=') << '\n';
	float total = peajePagado(lista);
	cout << "Precio total: " << total << endl;
	cout << setw(100) << setfill(' ') << '\n';
}

float peajeNavio(const tNavios navio) {
	float peaje;
	if (navio.esl < 100) {
		peaje = navio.ton * 2;
	}
	else {
		peaje = navio.ton * 3;
	}
	return peaje;
}

float peajePagado(const tListaNavios lista) {
	float total = 0;
	for (int i = 0; i < lista.cont; i++){
		if (lista.lista[i].pag == "true") {
			float peaje = peajeNavio(lista.lista[i]);
			total += peaje;
		}
	}
	return total;
}

void crearNavio(tListaNavios & lista) {
	tNavios navio;
	cout << "Introduzca nombre: ";
	cin >> navio.nom;
	cout << "Introduzca compañia: ";
	cin >> navio.empr;
	cout << "Introduzca eslora: ";
	cin >> navio.esl;
	cout << "Introduzca tonaledas: ";
	cin >> navio.ton;
	navio.pag = "false";
	if (insertaNavio(navio, lista)) {
		cout << "Se ha insertado correctamente" << endl;
		cout << setw(100) << setfill(' ') << '\n';
	}
	else {
		cout << "No se pudo introducir" << endl;
		cout << setw(100) << setfill(' ') << '\n';
	}
}

bool insertaNavio(const tNavios navio, tListaNavios & lista) {
	bool insertar = true;;
	if (lista.cont < MAX_NAV) {
		lista.lista[lista.cont].nom = navio.nom;
		lista.lista[lista.cont].empr = navio.empr;
		lista.lista[lista.cont].esl = navio.esl;
		lista.lista[lista.cont].ton = navio.ton;
		lista.lista[lista.cont].pag = navio.pag;
		lista.cont++;
	}
	else {
		insertar = false;
	}
	return insertar;
}
	
bool cobrarNavio(tListaNavios & lista, string name) {
	bool cobrar = false;
	int i = 0;
	while (!cobrar && i < lista.cont ) {
		if (lista.lista[i].nom == name) {
			lista.lista[i].pag = "true";
			cobrar = true;
		}
		i++;
	}
	return cobrar;
}