//Exámen Febrero 2012 - Grupos A, B, D y G.
//Fernando Méndez Torrrubiano.

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


//Constantes:
const int NUMEROS = 50;
const int N = 5;

//Tipos:
typedef int tNumeros[NUMEROS];
typedef struct tSecuencia {
	tNumeros numero;
	int contador;
};

//Funciones:
void ejecutarMenu();
int menu();
void inicializa(tSecuencia&);
void getSecuencia(tSecuencia&, const int&);
double calcularEx(const int&, const int&);
int factorial(const int&);
bool guardar(tSecuencia&);
bool esCapicua(tSecuencia&, int&);
bool inverso(const int&);
void guardarAnteriores(tSecuencia, const int&);



int main() {

	ejecutarMenu();

	return 0;
}

void ejecutarMenu() {
	tSecuencia secuencia;
	int opc = 1, n = N, i = 0;

	while (opc != 0){
		opc = menu();
		switch (opc){
		case 0: break;
		case 1: 
			getSecuencia(secuencia, n); 
			n += 2; 
			system("PAUSE"); 
			break;
		case 2: 
			if (guardar(secuencia)) {
				if (esCapicua(secuencia, i)) {
					cout << "El numero " << secuencia.numero[i] << " de la posicion " << i + 1<< " es capicua." << endl;
					guardarAnteriores(secuencia, i);
				}
				else {
					cout << "No se ha encontrado ningun numero capicua." << endl;
				}
			}
			else {
				cout << "No se han podido guardar los numeros anteriores." << endl;
			}
				system("PAUSE"); 
				break;
		default:
			break;
		}
		system("cls");
	}
}

int menu() {
	int opc = 0;

	cout << setw(25) << setfill('=') << "MENU" << setw(25) << "\n" << setfill(char(0));
	cout << "1.-Calculos de 'e' elevado a 'x'" << endl;
	cout << "2.-Detecta capicua" << endl;
	cout << "0.-Salir" << endl;
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 2);

	return opc;
}

void inicializa(tSecuencia& secuencia) {
	secuencia.contador = 0;
	for (int i = 0; i < NUMEROS; i++){
		secuencia.numero[i] = 0;
	}
}

void getSecuencia(tSecuencia& secuencia, const int& n) {
	inicializa(secuencia);

	do {
		cout << "Introduzca un numero (-1 para terminar): ";
		cin >> secuencia.numero[secuencia.contador];
		if (secuencia.numero[secuencia.contador] >= 0) {
			secuencia.contador++;
		}
	} while ((secuencia.numero[secuencia.contador] != -1));

	cout << endl;
	for (int i = 0; i < secuencia.contador; i++){
		cout << "'e' elevado a " << secuencia.numero[i] << " da como resultado: " << fixed << setprecision(2) << calcularEx(secuencia.numero[i], n) << endl;
	}
}

double calcularEx(const int& x, const int& n) {
	double eALAx = 0;

	for (int i = 0; i < n; i++){
		eALAx += (pow(x, i)) / (factorial(i));
	}

	return eALAx;
}

int factorial(const int& n) {
	int factorial = 1;

	if (n == 0) {
		factorial = 1;
	}
	else {
		for (int i = 1; i <= n; i++) {
			factorial *= i;
		}
	}

	return factorial;
}

bool guardar(tSecuencia& secuencia) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("input.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar." << endl;
		guardado = false;
	}
	else {
		for (int i = 0; i <= secuencia.contador; i++){
			archivo << secuencia.numero[i] << endl;
		}
		guardado = true;
	}
	archivo.close();

	return guardado;
}

bool esCapicua(tSecuencia& secuencia, int& i) {
	bool encontrado = false;

	while ((!encontrado) && (i < secuencia.contador)) {
		if (inverso(secuencia.numero[i])) {
			encontrado = true;
		}
		else {
			i++;
		}
	}

	return encontrado;
}

bool inverso(const int& numero) {
	string num = to_string(numero);
	string aux;

	if (numero >= 10) {
		for (int i = num.length() - 1; i >= 0; i--) {
			aux += num[i];
		}
	}

	return (num == aux) ? true : false;
}

void guardarAnteriores(tSecuencia secuencia, const int& i) {
	ofstream archivo;

	archivo.open("output.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar." << endl;
	}
	else {
		for (int j = 0; j < i; j++) {
			archivo << secuencia.numero[j] << endl;
		}
	}
	archivo.close();
}