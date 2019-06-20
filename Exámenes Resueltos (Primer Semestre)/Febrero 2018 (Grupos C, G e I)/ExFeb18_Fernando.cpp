//Examen Febreo 2018
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int MAX_NAV = 24;

//Tipos:
typedef string tNombres[MAX_NAV];
typedef float tMedidas[MAX_NAV];

typedef struct tNavios {
	tNombres nombre;
	tNombres empresa;
	tMedidas eslora;
	tMedidas toneladas;
	tNombres peaje;
	int contador;
};

//Funciones:
void inicializa(tNavios&, tNavios&);
bool cargar(tNavios&);
void ejecutarMenu(tNavios&, tNavios&);
int menu();
void muestraNavios(tNavios&);
void crearNavio(tNavios&);
bool insertarNavio(tNavios&, tNavios&);
bool cobrarNavio(tNavios&);
float peajeNavio(tNavios&, const int pos);
float peajePagado(tNavios&);
void guardar(tNavios&);

int main() {
	tNavios nave;
	tNavios nuevo;
	bool carga = false;

	inicializa(nave, nuevo);
	carga = cargar(nave);
	if (carga) {
		ejecutarMenu(nave, nuevo);
	}
	else {
		system("PAUSE");
	}
	guardar(nave);

	return 0;
}

void inicializa(tNavios& nave, tNavios& nuevo) {

	for (int i = 0; i < MAX_NAV; i++) {
		nave.nombre[i] = "";
		nave.empresa[i] = "";
		nave.eslora[i] = 0;
		nave.toneladas [i]= 0;
		nave.peaje[i] = "";
	}
	nave.contador = 0;
	nuevo.contador = 0;
}

bool cargar(tNavios& nave) {
	ifstream archivo;
	bool carga = false;

	archivo.open("navios.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar el archivo." << endl;
		carga = false;
	}
	else {
		archivo >> nave.nombre[nave.contador];
		while ((nave.nombre[nave.contador] != "XXX") && (nave.contador < MAX_NAV)) {
			archivo >> nave.empresa[nave.contador];
			archivo >> nave.eslora[nave.contador];
			archivo >> nave.toneladas[nave.contador];
			archivo >> nave.peaje[nave.contador];
			nave.contador++;
			archivo >> nave.nombre[nave.contador];
		} 
		carga = true;
	}
	archivo.close();

	return carga;
}

void ejecutarMenu(tNavios& nave, tNavios& nuevo) {
	int opc = 1;
	bool insertado = false;

	while (opc != 0) {
		system("cls");
		opc = menu();
		switch (opc){
		case 1: muestraNavios(nave); break;
		case 2: crearNavio(nuevo); 
				insertado = insertarNavio(nave, nuevo);
				if (!insertado) {
					cout << "No se ha podido añadir un nuevo navio." << endl;
					system("PAUSE");
				}
				else{
					cout << "Navio insertado correctamente." << endl;
					system("PAUSE");
				}
				break;
		case 3: cobrarNavio(nave); break;
		case 0: break;
		default: break;
		}
	}
}

int menu() {
	int opc = 0;

	//cout << setfill('-') << setw(25) << "\n";
	cout << "1.-VER LISTA DE NAVIOS." << "\n";
	cout << "2.-AGREGAR NAVIO." << "\n";
	cout << "3.-COBRAR PEAJE." << "\n";
	cout << "0.-SALIR." << "\n";
	//cout << setfill('-') << setw(25) << "\n";

	do{
		cout << "\n Intruduzca una opcion: ";
		cin >> opc;
	} while ((opc < 0) || (opc > 3));

	return opc;
}

void muestraNavios(tNavios& nave) {
	cout << setfill(char(0))  << setw(15)
		<< left << "NOMBRE" << setw(15)
		<< left << "EMPRESA" << setw(15)
		<< left << "ESLORA" << setw(20)
		<< left << "DESPLAZAMIENTO" << setw(20)
		<< left << "PEAJE";

	cout << setw(85) << setfill('=') << "\n" << setfill(char(0)) << endl;
	for (int i = 0; i < nave.contador; i++) {
		cout << setw(15) << left << nave.nombre[i] << setw(15)
			<< left << nave.empresa[i] << setw(15)
			<< left  << fixed << setprecision(2) << nave.eslora[i] << setw(20)
			<< left << nave.toneladas[i] << setw(10);
			if (nave.peaje[i] == "true") {
				cout << peajeNavio(nave, i) << "PAGADO\n";
			}
			else {
				cout << peajeNavio(nave, i) << "NO PAGADO\n";
			}
	}
	cout << setw(85) << setfill('=') << "\n";
	cout << setw(0) << setfill(char(0)) << "\n";
	system("PAUSE");
}

void crearNavio(tNavios& nuevo) {
	string nombre;

	nuevo.contador++;
	cout << "Introduzca NOMBRE del navio: ";
	cin >> nuevo.nombre[nuevo.contador];
	cout << "Introduzca EMPRESA fabricante: ";
	cin >> nuevo.empresa[nuevo.contador];
	cout << "Introduzca ESLORA del navio: ";
	cin >> nuevo.eslora[nuevo.contador];
	cout << "Introduzca TONELADAS del navio: ";
	cin >> nuevo.toneladas[nuevo.contador];
	cout << "Introduzca PEAJE (true/false): ";
	cin >> nuevo.peaje[nuevo.contador];

}

bool insertarNavio(tNavios& nave, tNavios& nuevo) {
	bool insertado = false;

	if (nave.contador < MAX_NAV) {
		nave.nombre[nave.contador] = nuevo.nombre[nuevo.contador];
		nave.empresa[nave.contador] = nuevo.empresa[nuevo.contador];
		nave.eslora[nave.contador] = nuevo.eslora[nuevo.contador];
		nave.toneladas[nave.contador] = nuevo.toneladas[nuevo.contador];
		nave.peaje[nave.contador] = nuevo.peaje[nuevo.contador];
		nave.contador++;
		insertado = true;
	}
	else {
		insertado = false;
	}

	return insertado;
}

bool cobrarNavio(tNavios& nave) {
	bool encontrado = false;
	string nom;
	int i = 0;

	cout << "Introduzca el nombre del navio que quiere pagar: ";
	cin >> nom;

	while ((i < nave.contador) && (!encontrado)) {
		if (nave.nombre[i] == nom) {
			nave.peaje[i] = "true";
			encontrado = true;
		}
		i++;
	}

	return encontrado;
}

float peajeNavio(tNavios& nave, const int pos) {
	float precio = 0;

	if (nave.eslora[pos] <= 100) {
		precio = nave.toneladas[pos] * 2;
	}
	else {
		precio = nave.toneladas[pos] * 3;
	}

	return precio;
}

float peajePagado(tNavios& nave) {
	float pagos = 0;

	for (int i = 0; i < nave.contador; i++) {
		if (nave.peaje[i] == "true") {
			pagos += peajeNavio(nave, i);
		}
	}

	return pagos;
}

void guardar(tNavios& nave) {
	ofstream archivo;

	archivo.open("navios.txt");
	if(archivo.is_open()){
		for (int i = 0; i < nave.contador; i++) {
			archivo << nave.nombre[i] << " ";
			archivo << nave.empresa[i] << " ";
			archivo << nave.eslora[i] << " ";
			archivo << nave.toneladas[i] << " ";
			archivo << nave.peaje[i] << " " << endl;
		}
		archivo << "XXX";
	}
	archivo.close();
}