//Examen Febrero 2017 - Grupos A, E, D y G.
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int MAX_APUNTES = 500;

//Tipos:
typedef struct tFecha {
	int dia, mes, anio;
};
typedef struct tApunte {
	tFecha fecha;
	float importe;
	string concepto;
};
typedef tApunte tApuntes[MAX_APUNTES];
typedef struct tCuenta {
	tApuntes apunte;
	int contador;
};

//Funciones:
void inicializa(tCuenta&);
bool cargar(tCuenta&);
float nomina(tCuenta&);
float gastoMedio(tCuenta&, const int&);
void mostrar(tCuenta&);
void ejecutarMenu(tCuenta&);
int menu();


int main() {
	tCuenta cuenta;

	ejecutarMenu(cuenta);

	return 0;
}

void inicializa(tCuenta& cuenta) {
	cuenta.contador = 0;
	for (int i = 0; i < MAX_APUNTES; i++){
		cuenta.apunte[i].fecha.dia = 0;
		cuenta.apunte[i].fecha.mes = 0;
		cuenta.apunte[i].fecha.anio = 0;
		cuenta.apunte[i].importe = 0;
		cuenta.apunte[i].concepto = "";
	}
}

bool cargar(tCuenta& cuenta) {
	bool carga = false;
	ifstream archivo;
	string nomArchivo;

	inicializa(cuenta);

	cout << "Introduzca nombre del archivo (sin extension): ";
	cin >> nomArchivo;
	nomArchivo += ".txt";
	archivo.open(nomArchivo);
	if (!archivo.is_open()){
		cout << "Error al cargar el archivo." << endl;
		carga = false;
	}
	else {
		archivo >> cuenta.apunte[cuenta.contador].fecha.dia;
		while ((cuenta.apunte[cuenta.contador].fecha.dia != -1) && (cuenta.contador < MAX_APUNTES)) {
			archivo >> cuenta.apunte[cuenta.contador].fecha.mes;
			archivo >> cuenta.apunte[cuenta.contador].fecha.anio;
			archivo >> cuenta.apunte[cuenta.contador].importe;
			archivo >> cuenta.apunte[cuenta.contador].concepto;
			cuenta.contador++;
			archivo >> cuenta.apunte[cuenta.contador].fecha.dia;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

float nomina(tCuenta& cuenta) {
	bool encontrado = false;
	int i = 0;
	float nomina = 0;

	while ((!encontrado) && (i < cuenta.contador)) {
		if (cuenta.apunte[i].concepto == "Salario") {
			nomina = cuenta.apunte[i].importe;
			encontrado = true;
		}
		else {
			i++;
		}
	}

	return nomina;
}

float gastoMedio(tCuenta& cuenta, const int& anio) {
	float gasto = 0;
	int i = 0;

	while ((i < cuenta.contador)) {
		if ((cuenta.apunte[i].fecha.anio == anio) && (cuenta.apunte[i].concepto == "Luz")) {
			gasto += (-1 * cuenta.apunte[i].importe);
		}
		i++;
	}

	return gasto;
}

void mostrar(tCuenta& cuenta) {
	cout << setw(2) << right << "DIA"
		<< setw(5) << "MES"
		<< setw(10) << "ANIO"
		<< setw(10) << "IMPORTE"
		<< setw(15) << "CONCEPTO" << endl;
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < cuenta.contador; i++){
		cout << setw(2) << right << cuenta.apunte[i].fecha.dia
			<< setw(5) << cuenta.apunte[i].fecha.mes
			<< setw(10) << cuenta.apunte[i].fecha.anio
			<< setw(10) << cuenta.apunte[i].importe
			<< setw(15) << cuenta.apunte[i].concepto << endl;
	}
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
}

void ejecutarMenu(tCuenta& cuenta) {
	int opc = 1;
	float anio;

	while (opc != 0) {
		opc = menu();
		switch (opc){
		case 0: break;
		case 1: 
			if (cargar(cuenta)) {
				cout << "Cargado correctamente." << endl;
			}
			else {
				cout << "No se ha podido cargar el archivo." << endl;
			}
			break;
		case 2: cout << "El importe de la primera nomina es: " << nomina(cuenta) << endl; break;
		case 3: 
			cout << "Introduzca un anio: ";
			cin >> anio;
			cout << "El gasto medio de la luz en el anio " << anio << " fue: " << gastoMedio(cuenta, anio) << endl; break;
		case 4: mostrar(cuenta); break;
		default:
			break;
		}
		system("PAUSE");
		system("cls");
	}
}

int menu() {
	int opc = 0;

	cout << setw(25) << setfill('=') << "MENU" << setw(25) << "\n" << setfill(char(0));
	cout << "1.-Cargar cuenta de un fichero." << endl;
	cout << "2.-Importe de la ultima nomina." << endl;
	cout << "3.-Gasto medio de luz en un anio." << endl;
	cout << "4.-Mostrar por pantalla" << endl;
	cout << "0.-Salir" << endl;
	cout << setw(50) << setfill('=') <<"\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc>4);

	return opc;
}