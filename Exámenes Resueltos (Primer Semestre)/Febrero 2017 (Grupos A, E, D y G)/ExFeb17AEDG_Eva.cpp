// Eva Verdú Rodríguez 51220965B
// LAB: 10
// PTO: 12

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_APUNTES = 500;

typedef struct tFecha {
	int dia;
	int mes;
	int año;
};

typedef struct tApunte {
	tFecha fecha;
	float impor;
	string concep;
};

typedef struct tCuenta {
	tApunte apunte [MAX_APUNTES];
	int cont;
};

int menu();
void cargar(tCuenta & cuenta, string fichero);
void Nomina(const tCuenta cuenta);
void GastoLuzAño(const tCuenta cuenta, int año);
void mostrar(const tCuenta cuenta);

int main() {
	int opc, año;
	tCuenta cuenta;
	cuenta.cont = 0;
	string fichero = "apuntes.txt";
	opc = menu();
	do{
		switch (opc) {
		case 1:
			cargar(cuenta, fichero);
			break;
		case 2:
			Nomina(cuenta);
			break;
		case 3:
			cout << "Introduzca año para calcular el gasto medio: ";
			cin >> año;
			GastoLuzAño(cuenta, año);
			break;
		case 4:
			mostrar(cuenta);
			break;
		}
		opc = menu();
	} while (opc != 0);

	system("pause");
	return 0;
}

int menu() {
	int opc;
	do {
		cout << "Elige una opción: " << endl;
		cout << "1 Cargar cuenta de fichero" << endl;
		cout << "2 Importe de la primera nómina" << endl;
		cout << "3 Gasto medio de luz en un año" << endl;
		cout << "4 Mostrar por pantalla" << endl;
		cout << "0 Salir" << endl;
		cin >> opc;
	} while (opc < 0 || opc > 4);

	return opc;
}

void cargar(tCuenta & cuenta, string fichero){
	ifstream archivo;
	archivo.open(fichero);
	int aux;
	if (archivo.is_open()) {
		archivo >> aux;
		while (aux != -1 && cuenta.cont != MAX_APUNTES) {
			cuenta.apunte[cuenta.cont].fecha.dia = aux;
			archivo >> cuenta.apunte[cuenta.cont].fecha.mes;
			archivo >> cuenta.apunte[cuenta.cont].fecha.año;
			archivo >> cuenta.apunte[cuenta.cont].impor;
			archivo >> cuenta.apunte[cuenta.cont].concep;
			archivo >> aux;
			cuenta.cont++;
		}
		archivo.close();
	}
	else {
		cout << "Archivo no encontrado" << endl;
	}
}

void Nomina(const tCuenta cuenta) {
	float nomina = 0;
	bool found = false;
	int i = 0;
	while (i < cuenta.cont && !found) {
		if (cuenta.apunte[i].concep == "Salario") {
			nomina = cuenta.apunte[i].impor;
			found = true;
		}
		else {
			i++;
		}
	}
	if (nomina != 0) {
		cout << "El importe de la primera nomina es: " << fixed << setprecision(2) << nomina << " euros." << endl;
	}
	else {
		cout << "No hay salarios" << endl;
	}
	
}

void GastoLuzAño(const tCuenta cuenta, int año) {
	float numLuz = 0;
	float sum = 0;
	float media = 0;
	for (int i = 0; i < cuenta.cont; i++) {
		if (cuenta.apunte[i].fecha.año == año && cuenta.apunte[i].concep == "Luz") {
			sum += cuenta.apunte[i].impor;
			numLuz++;
		}
	}
	media = sum / numLuz;
	media = media * -1;
	cout << " Gasto medio del año " << año << " es: " << media << endl;
}

void mostrar(const tCuenta cuenta) {
	for (int i = 0; i < cuenta.cont; i++){
	
		cout << setfill('0') << setw(2) << internal << cuenta.apunte[i].fecha.dia <<" "
			 << setw(2) << cuenta.apunte[i].fecha.mes << " "
			 << setfill(' ') << setw(5) << cuenta.apunte[i].fecha.año
			 << right << fixed << setprecision(2) << setw(10) << cuenta.apunte[i].impor  << " "
			 << setw(10) << left << cuenta.apunte[i].concep << " " << endl;
		
	}
}
