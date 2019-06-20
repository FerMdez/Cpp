//Examen Febrero 2017 - Grupos: A, E, D y G.
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


//Constantes:
const int MAX_APUNTES = 500;


//Tipos:
typedef struct {
	int dia;
	int mes;
	int anio;
}tFecha;

typedef struct {
	tFecha fecha;
	float importe;
	string concepto;
}tApunte;

typedef tApunte tApuntes[MAX_APUNTES];

typedef struct {
	tApuntes apunte;
	int contador;
}tCuenta;


//Funciones:
void inicializa(tCuenta&);
bool cargar(tCuenta&);
int menu();
void ejecutarMenu(tCuenta&);
float nomina(tCuenta&);
float gastoLuz(tCuenta&, const int&);
void mostrar(tCuenta&);



int main() {
	tCuenta cuentas;

	ejecutarMenu(cuentas);

	return 0;
}

void inicializa(tCuenta& cuentas) {
	cuentas.contador = 0;
	for (int i = 0; i < MAX_APUNTES; i++) {
		cuentas.apunte[i].fecha.dia = 0;
		cuentas.apunte[i].fecha.mes = 0;
		cuentas.apunte[i].fecha.anio = 0;
		cuentas.apunte[i].importe = 0;
		cuentas.apunte[i].concepto = "";
	}
}

bool cargar(tCuenta& cuentas) {
	bool carga = false;
	string nombreFichero;
	ifstream archivo;

	inicializa(cuentas);

	cout << "Introduzca nombre del archivo: ";
	cin >> nombreFichero;
	nombreFichero += ".txt";
	archivo.open(nombreFichero);
	if (!archivo.is_open()) {
		cout << "Error al cargar el archivo." << endl;
		carga = false;
	}
	else {
		archivo >> cuentas.apunte[cuentas.contador].fecha.dia;
		while ((cuentas.apunte[cuentas.contador].fecha.dia != -1) && (cuentas.contador < MAX_APUNTES)) {
			archivo >> cuentas.apunte[cuentas.contador].fecha.mes;
			archivo >> cuentas.apunte[cuentas.contador].fecha.anio;
			archivo >> cuentas.apunte[cuentas.contador].importe;
			archivo >> cuentas.apunte[cuentas.contador].concepto;
			cuentas.contador++;
			archivo >> cuentas.apunte[cuentas.contador].fecha.dia;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

int menu() {
	int opc = 0;

	cout << setw(35) << setfill('=') << "\n" << setw(0) << setfill(char(0));
	cout << "1.-Cargar cuenta de fichero." << endl;
	cout << "2.-Importe de la primera nomina." << endl;
	cout << "3.-Gasto medio de la luz en un anio." << endl;
	cout << "4.-Mostrar por pantalla." << endl;
	cout << "0.-Salir." << endl;
	cout << setw(35) << setfill('=') << "\n" << setw(0) << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while ((opc < 0) || (opc > 4));

	return opc;
}

void ejecutarMenu(tCuenta& cuentas) {
	int opc = 1;
	int anio = 0;

	while (opc != 0) {
		opc = menu();
		switch (opc) {
		case 1: 
			if (cargar(cuentas)) { 
				cout << "Cargado correctamente." << endl; 
			}
			else {
				cout << "Vuelva a intentarlo." << endl; 
			} break;
		case 2: cout << "Primera nomina: " << nomina(cuentas) << endl; break;
		case 3: cout << "Introduzca un anio: ";
			cin >> anio;
			cout << "Gasto en " << anio << ": " << gastoLuz(cuentas, anio) << endl; break;
		case 4: mostrar(cuentas); break;
		case 0: break;
		}
		system("PAUSE");
		system("cls");
	}
}

float nomina(tCuenta& cuentas) {
	bool encontrado = false;
	int i = 0;

	while ((!encontrado) && (i < cuentas.contador)) {
		if (cuentas.apunte[i].concepto == "Salario") {
			encontrado = true;
		}
		else {
			i++;
		}
	}
	return cuentas.apunte[i].importe;
}

float gastoLuz(tCuenta& cuentas, const int& anio) {
	int i = 0;
	float gasto = 0;
	float importePositivo = 0;

	while (i < cuentas.contador) {
		if ((cuentas.apunte[i].concepto == "Luz") && (cuentas.apunte[i].fecha.anio == anio)) {
			importePositivo = -1 * cuentas.apunte[i].importe;
			gasto += importePositivo;
		}
		i++;
	}

	return gasto;
}

void mostrar(tCuenta& cuentas) {
	cout << "FECHA" << "     " << "IMPORTE" << "  " << right << "CONCEPTO" << endl;
	cout << setw(35) << setfill('-') << "\n" << setw(0) << setfill(char(0));
	for (int i = 0; i < cuentas.contador; i++) {
		cout << cuentas.apunte[i].fecha.dia << "/"
			<< cuentas.apunte[i].fecha.mes << "/"
			<< cuentas.apunte[i].fecha.anio << "     "  << left
			<< cuentas.apunte[i].importe << "  " << right
			<< cuentas.apunte[i].concepto << endl;
	}
	cout << setw(35) << setfill('-') << "\n" << setw(0) << setfill(char(0));
}