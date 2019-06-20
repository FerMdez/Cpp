//Examen Febrero 2011 - Grupos A, B y C.
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


//Constantes:
/*EJERCICIO 1*/
const int MAX_NUM = 1000;
const int NUM_CIFRAS = 5;
/*EJERCICIO 2*/
const int NUM_PIEZAS = 16 * 2;
const int NUM_JUGADORES = 2;
const int DIMENSIONES = 8;

//Tipos:
/*EJERCICIO 1*/
typedef struct tNumero {
	int numero;
	int contadorCifra;
};
typedef tNumero tNumeros[MAX_NUM];
typedef struct tListaNumeros {
	tNumeros numeros;
	int contador;
};
/*EJERCICIO 2*/
typedef enum tPieza { vacia, peon, torre, caballo, alfil, reina, rey };
typedef enum tColor { blanca, negra };
typedef struct tCelda {
	tPieza pieza;
	tColor color;
};
typedef tCelda tTablero[DIMENSIONES][DIMENSIONES];
typedef struct tPartida {
	tTablero tablero;
	int contador;
};

//Funciones:
void ejecutarMenu(tListaNumeros&, tPartida&);
int menu();
/*EJERCICIO 1*/
void inicializa(tListaNumeros&);
bool cargar(tListaNumeros&);
void procesar(tListaNumeros&);
bool guardar(tListaNumeros&);
/*EJERCICIO 2*/
void iniciaTablero(tPartida&);
bool cargar(tPartida&);
void colocar(tPartida&, const char&, const char&, const int&, const int&);
void posicion(tPartida&);
void mostrarCasilla(tPartida&, const int&, const int&);



int main() {
	tListaNumeros listaNum;
	tPartida partida;
	
	ejecutarMenu(listaNum, partida);

	return 0;
}

void ejecutarMenu(tListaNumeros& listaNum, tPartida& partida) {
	int opc = 1;

	while (opc != 0) {
		opc = menu();
		switch (opc){
		case 0: break;
		case 1:
			if (cargar(listaNum)) {
				cout << "Cargado correctamente." << endl;
				if (guardar(listaNum)) {
					cout << "Guardado correctamente." << endl;
				}
				else {
					cout << "Vauelva a intentarlo." << endl;
				}
			}
			else {
				cout << "FIN DEL PROGRAMA." << endl;
			}
			system("PAUSE");
			break;
		case 2:
			if (cargar(partida)) {
				posicion(partida);
			}
			break;
		default:
			break;
		}
		system("cls");
	}
}

int menu() {
	int opc = 0;

	cout << setw(35) << setfill('=') << "MENU" << setw(35) << "\n" << setfill(char(0));
	cout << "1.-Contar numero de cifras de los numeros del archivo 'entrada.txt'." << endl;
	cout << "2.-Partida de ajedrez." << endl;
	cout << "0.-Salir." << endl;
	cout << setw(70) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 2);

	return opc;
}

/*EJERCICIO 1*/
void inicializa(tListaNumeros& listaNum) {
	listaNum.contador = 0;

	for (int i = 0; i < MAX_NUM; i++) {
		listaNum.numeros[i].numero = 0;
		listaNum.numeros[i].contadorCifra = 1;
	}
}

bool cargar(tListaNumeros& listaNum) {
	bool carga = false;
	ifstream archivo;

	inicializa(listaNum);
	archivo.open("entrada.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar el archivo." << endl;
		carga = false;
	}
	else{
		while ((!archivo.eof()) && (listaNum.contador < MAX_NUM)) {
			archivo >> listaNum.numeros[listaNum.contador].numero;
			procesar(listaNum);
			listaNum.contador++;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void procesar(tListaNumeros& listaNum) {
	int aux = 0;

	aux = listaNum.numeros[listaNum.contador].numero;
	while (aux > 10) {
		aux /= 10;
		listaNum.numeros[listaNum.contador].contadorCifra++;
	}
}

bool guardar(tListaNumeros& listaNum) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("salida.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar." << endl;
		guardado = false;
	}
	else {
		archivo << setw(6) << right << "NUMERO" << setw(22) << "NUMERO DE CIFRAS" << endl;
		archivo << setw(30) << setfill('=') << "\n" << setfill(char(0));
		for (int i = 0; i < listaNum.contador; i++){
			archivo << setw(5) << right << listaNum.numeros[i].numero << setw(15) << setfill('.') << listaNum.numeros[i].contadorCifra << setfill(char(0)) << endl;
		}
		guardado = true;
	}
	archivo.close();

	return guardado;
}



/*EJERCICIO 2*/
void iniciaTablero(tPartida& partida) {
	partida.contador = 0;
	for (int i = 0; i < DIMENSIONES; i++){
		for (int j = 0; j < DIMENSIONES; j++){
			partida.tablero[i][j].pieza = vacia;
			partida.tablero[i][j].color = blanca;
		}
	}
}

bool cargar(tPartida& partida) {
	bool carga = false;
	ifstream archivo;
	char tipo, color;
	int fila, columna;

	iniciaTablero(partida);
	archivo.open("tablero.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar." << endl;
		carga = false;
	}
	else {
		while ((!archivo.eof()) && (partida.contador < NUM_PIEZAS)) {
			archivo >> tipo;
			archivo >> color;
			archivo >> fila;
			archivo >> columna;
			colocar(partida, tipo, color, fila, columna);
			partida.contador++;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void colocar(tPartida& partida, const char& tipo, const char& color, const int& fila, const int& columna) {
	
	if (color == 'B') {
		partida.tablero[fila][columna].color = blanca;
	}
	else {
		partida.tablero[fila][columna].color = negra;
	}
	switch (tipo){
	case 'P': partida.tablero[fila][columna].pieza = peon; break;
	case 'T': partida.tablero[fila][columna].pieza = torre; break;
	case 'A': partida.tablero[fila][columna].pieza = alfil; break;
	case 'C': partida.tablero[fila][columna].pieza = caballo; break;
	case 'Q': partida.tablero[fila][columna].pieza = reina; break;
	case 'R': partida.tablero[fila][columna].pieza = rey; break;
	default: partida.tablero[fila][columna].pieza = vacia;
		break;
	}
}

void posicion(tPartida& partida) {
	char continuar = 'N';
	int fila = 0, columna = 0;

	do {
		do {
			cout << "Introduzca una fila: ";
			cin >> fila;
		} while (fila < 0 || fila >= DIMENSIONES);
		do {
			cout << "Introduzca una columna: ";
			cin >> columna;
		} while (columna < 0 || columna >= DIMENSIONES);
		
		mostrarCasilla(partida, fila, columna);

		cout << "Quiere continuar (S/n)?";
		cin >> continuar;
	} while (continuar == 'S' || continuar == 's');
}

void mostrarCasilla(tPartida& partida, const int& fila, const int& columna) {

	switch (partida.tablero[fila][columna].pieza){
	case peon: cout << "Figura: PEON  "; break;
	case torre: cout << "Figura: TORRE  "; break;
	case alfil: cout << "Figura: ALFIL  "; break;
	case caballo: cout << "Figura: CABALLO  "; break;
	case reina: cout << "Figura: REINA  "; break;
	case rey: cout << "Figura: REY  "; break;
	default:
		cout << "Figura: NINGUNA" << endl;
		break;
	}
	
	switch (partida.tablero[fila][columna].color){
	case blanca: cout << "Color: BLANCA" << endl; break;
	case negra: cout << "Color: NEGRA" << endl; break;
	default:
		break;
	}

}