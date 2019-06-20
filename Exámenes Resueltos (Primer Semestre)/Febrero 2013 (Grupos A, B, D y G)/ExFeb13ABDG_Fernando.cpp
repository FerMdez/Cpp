//Examen Febrero 2013 - Grupos A, B, D y G.
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


//Constantes:
const int MAX_NUM = 100;

//Tipos:
typedef int tNumeros[MAX_NUM];
typedef struct tSecuencia {
	tNumeros numeros;
	int contador;
};


//Funciones:
void ejecutarMenu();
int menu();
bool generar(tSecuencia&, const int&);
bool guardar(tSecuencia&);
void recorrer(tSecuencia&);
bool esFeliz(int&);
bool buscar(tSecuencia&, int&, int&);


int main() {

	ejecutarMenu();

	return 0;
}

void ejecutarMenu() {
	tSecuencia secuencia;
	int opc = 1, maximo, error, i = 1;
	bool generado = false;

	while (opc != 0) {
		opc = menu();
		switch (opc){
		case 0: break;
		case 1: 
			cout << "Introduzca el limite superior para los numeros de la secuencia: ";
			cin >> maximo;
			if (generar(secuencia, maximo)) {
				cout << "Secuencia generada correctamente." << endl;
				generado = true;
			}
			else {
				cout << "Error al generar la secuencia." << endl;
			}
			system("PAUSE");
			break;
		case 2:
			if (generado == true) {
				recorrer(secuencia);
			}
			else {
				cout << "Primero debes generar una secuencia." << endl;
			}
			system("PAUSE"); 
			break;
		case 3: 
			if (generado == true) {
				cout << "Introduzca un error: ";
				cin >> error;
				if (buscar(secuencia, error, i)) {
					cout << "Encontrado en la linea " << i << " (diferencia: " << error << ")." << endl;
				}
				else {
					cout << "No encontrado." << endl;
				}
			}
			else {
				cout << "Primero debes generar una secuencia." << endl;
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
	cout << "1.-Generar una secuencia." << endl;
	cout << "2.-Procesar la secuencia" << endl;
	cout << "3.-Buscar en la secuencia." << endl;
	cout << "0.-Salir" << endl;
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 3);

	return opc;
}

bool generar(tSecuencia& secuencia, const int& maximo) {
	secuencia.contador = 0;

	do{
		cout << "Introduzca un numero (0 para terminar): ";
		cin >> secuencia.numeros[secuencia.contador];
		if ((secuencia.numeros[secuencia.contador] < maximo) && (secuencia.numeros[secuencia.contador] > 0)) {
			secuencia.contador++;
		}
	} while ((secuencia.numeros[secuencia.contador] != 0));

	return guardar(secuencia) ? true : false;
}

bool guardar(tSecuencia& secuencia) {
	bool save = false;
	ofstream archivo;

	archivo.open("datos.txt");
	if (!archivo.is_open()) {
		save = false;
	}
	else {
		for (int i = 0; i < secuencia.contador; i++){
			archivo << secuencia.numeros[i] << endl;
		}
		archivo << -1;
		save = true;
	}

	return save;
}

void recorrer(tSecuencia& secuencia) {
	int numero = 0;

	for (int i = 0; i < secuencia.contador; i++){
		numero = secuencia.numeros[i];
		if (esFeliz(numero)) { cout << "El numero: " << secuencia.numeros[i] << " ES FELIZ." << endl; }
		else { cout << "El numero: " << secuencia.numeros[i] << " NO ES FELIZ." << endl; }
	
	}
}

bool esFeliz(int& num) {
	int digito[10] = { 0,0,0,0,0,0,0,0,0,0 }, i = 0, aux;

	do {
		if (num > 10) { //Igualamos una variable auxiliar al valor anterior del número (si el número, es mayor de 10).
			aux = num; 
		} 
		else { //Si el número es menor que 10, igualamos el auxiliar a 10 para que entre en el bucle y procese el número.
			aux = 10; 
		} 
		while (aux >= 10) { //Si el auxiliar es mayor o igual a 10, significa que el número aun tiene más de dos cifras y por tanto hay que continuar extrayendo dichas cifras.
			digito[i] = num % 10; //Hacemos el módulo 10 del número para extraer el digito correspondiente a las unidades.
			num -= digito[i]; //Restamos al número el valor de las unidades, para hacerlo potencia de 10.
			aux = num; //Igualamos una variable auxiliar al valor anterior del número. Porque en la siguiente comprobación del bucle, el número estará dividido entre 10 y daría una vuelta menos.
			num /= 10; //Dividimos el número entre 10 para en la siguiente vuelta del bucle, seguir extrayendo el próximo dígito, que antes eran las decenas y ahora correcponderá a las unidades.
			i++; //Sumamos uno para guardar la siguiente cifra en la próxima posición del vector. Como vamos a sumar los dígitos, nos da igual que se guarden en orden inverso.
		}

		num = 0;
		for (int j = 0; j < i; j++) {
			num += pow(digito[j], 2); //Calculamos la suma de las potencias cuadradas de cada uno de los dígitos del número.
		}
		i = 0;
	} while (num >= 10);

	return (num == 1) ? true : false;
}

bool buscar(tSecuencia& secuencia, int& error, int& i) {
	bool encontrado = false;

	while ((!encontrado) && (i < secuencia.contador)) {
		if ((secuencia.numeros[i] - secuencia.numeros[i - 1]) < error) {
			error = secuencia.numeros[i] - secuencia.numeros[i - 1];
			encontrado = true;
		}
		i++;
	}

	return encontrado;
}