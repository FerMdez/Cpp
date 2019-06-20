//Examen Febrero 2014 - Grupos D y G.
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int NP = 10;
const int CLASES = 4;

//Tipos:
typedef enum tClase{papeleria, alimentacion, limpieza, informatica};
typedef struct tProveedor {
	string CIF;
	tClase clase;
	int pedidos;
	int coste;
};
typedef tProveedor tProveedores[NP];
typedef struct tListaProveedores {
	tProveedores proveedor;
	int contador;
};

typedef struct tGastos {
	tClase clase;
	int gasto;
};
typedef tGastos tListaGastos[CLASES];

//Funciones:
void inicializa(tListaProveedores&);
bool carga(tListaProveedores&);
void tIntToClase(tListaProveedores&, const int&);
void ejecutarMenu(tListaProveedores&);
int menu();
bool guardar(tListaProveedores&);
int buscarProveedor(tListaProveedores&, const string&);
void nuevoPedido(tListaProveedores&, const string&, const int&);
void mostrar(tListaProveedores&);
void mostrarIntervalo(tListaProveedores&, const int&, const int&);
void totalesXclase(tListaProveedores&);
void iniciaGastos(tListaGastos&);

int main() {
	tListaProveedores proveedores;

	if (carga(proveedores)) {
		ejecutarMenu(proveedores);
		if (guardar(proveedores)) {
			cout << "Guardado correctamente." << endl;
		}
		else {
			cout << "Error al guardar el archivo." << endl;
		}
	}
	else {
		cout << "Error al cargar el archivo." << endl;
		system("PAUSE");
	}

	return 0;
}

void inicializa(tListaProveedores& proveedores) {
	proveedores.contador = 0;
	for (int i = 0; i < NP; i++){
		proveedores.proveedor[i].CIF = "";
		proveedores.proveedor[i].clase = informatica;
		proveedores.proveedor[i].pedidos = 0;
		proveedores.proveedor[i].coste = 0;
	}
}

bool carga(tListaProveedores& proveedores) {
	bool cargado = false;
	ifstream archivo;
	int claseAUX;

	inicializa(proveedores);
	archivo.open("proveedores.txt");
	if (!archivo.is_open()) {
		cargado = false;
	}
	else {
		archivo >> proveedores.proveedor[proveedores.contador].CIF;
		while ((proveedores.proveedor[proveedores.contador].CIF != "X") && (proveedores.contador < NP)) {
			archivo >> claseAUX;
			tIntToClase(proveedores, claseAUX);
			archivo >> proveedores.proveedor[proveedores.contador].pedidos;
			archivo >> proveedores.proveedor[proveedores.contador].coste;
			proveedores.contador++;
			archivo >> proveedores.proveedor[proveedores.contador].CIF;
		}
		cargado = true;
	}
	archivo.close();

	return cargado;
}

void tIntToClase(tListaProveedores& proveedores, const int& aux) {
	switch (aux){
	case 0: proveedores.proveedor[proveedores.contador].clase = papeleria; break;
	case 1: proveedores.proveedor[proveedores.contador].clase = alimentacion; break;
	case 2: proveedores.proveedor[proveedores.contador].clase = limpieza; break;
	case 3: proveedores.proveedor[proveedores.contador].clase = informatica; break;
	default:
		break;
	}
}

void ejecutarMenu(tListaProveedores& proveedores) {
	int opc = 1, coste, max, min;
	string CIF;

	while (opc != 0) {
		opc = menu();
		switch (opc){
		case 0: break;
		case 1: 
			mostrar(proveedores);
			cout << endl << "Introduzca el CIF para el pedido: ";
			cin >> CIF;
			cout << "Introduzca el coste del pedido: ";
			cin >> coste;
			nuevoPedido(proveedores, CIF, coste);
			break;
		case 2:
			cout << "Introduzca un minimo: ";
			cin >> min;
			cout << "Introduzca un maximo: ";
			cin >> max;
			mostrarIntervalo(proveedores, max, min);
			break;
		case 3: totalesXclase(proveedores); break;
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
	cout << "1.-Nuevo pedido." << endl;
	cout << "2.-Proveedores con numero de pedidos en un intervalo." << endl;
	cout << "3.-Gastos por clase de proveedor." << endl;
	cout << "0.-SALIR." << endl;
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 3);

	return opc;
}

bool guardar(tListaProveedores& proveedores) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("proveedores.txt");
	if (!archivo.is_open()) {
		guardado = false;
	}
	else {
		for (int i = 0; i < proveedores.contador; i++)
		{
			archivo << proveedores.proveedor[i].CIF << " "
				<< proveedores.proveedor[i].clase << " "
				<< proveedores.proveedor[i].pedidos << " "
				<< proveedores.proveedor[i].coste << endl;
		}
		archivo << "X";
		guardado = true;
	}
	archivo.close();

	return guardado;
}

int buscarProveedor(tListaProveedores& proveedores, const string& CIF) {
	int pos = proveedores.contador;
	bool encontrado = false;

	while ((!encontrado) && (pos > -1)) {
		if (proveedores.proveedor[pos].CIF == CIF) {
			encontrado = true;
		}
		else {
			pos--;
		}
	}

	return pos;
}

void nuevoPedido(tListaProveedores& proveedores, const string& CIF, const int& coste) {
	int pos = buscarProveedor(proveedores, CIF);

	if (pos != -1) {
		proveedores.proveedor[pos].coste += coste;
		proveedores.proveedor[pos].pedidos++;
		cout << "Actualizado correctamente." << endl;
	}
	else {
		cout << "CIF no encontrado." << endl;
	}
}

void mostrar(tListaProveedores& proveedores) {
	cout << endl << setw(7) << "CIF"
		<< setw(20) << "PROVEEDOR"
		<< setw(13) << "NUM_PEDIDOS"
		<< setw(7) << "COSTE" << endl;
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < proveedores.contador; i++){
		cout << setw(10) << right << proveedores.proveedor[i].CIF
			<< setw(10) << proveedores.proveedor[i].clase
			<< setw(13) << proveedores.proveedor[i].pedidos
			<< setw(12) << proveedores.proveedor[i].coste << endl;
	}
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
}

void mostrarIntervalo(tListaProveedores& proveedores, const int& max, const int& min) {
	cout << endl << setw(7) << "CIF"
		<< setw(20) << "PROVEEDOR"
		<< setw(13) << "NUM_PEDIDOS"
		<< setw(7) << "COSTE" << endl;
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < proveedores.contador; i++) {
		if ((proveedores.proveedor[i].pedidos <= max) && (proveedores.proveedor[i].pedidos >= min)) {
			cout << setw(10) << right << proveedores.proveedor[i].CIF
				<< setw(10) << proveedores.proveedor[i].clase
				<< setw(13) << proveedores.proveedor[i].pedidos
				<< setw(12) << proveedores.proveedor[i].coste << endl;
		}
	}
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
}

void totalesXclase(tListaProveedores& proveedores) {
	tListaGastos gastos;

	iniciaGastos(gastos);
	for (int i = 0; i < CLASES; i++){
		for (int j = 0; j < NP; j++){
			if (proveedores.proveedor[j].clase == gastos[i].clase) {
				gastos[i].gasto += proveedores.proveedor[j].coste;
			}
		}
		switch (gastos[i].clase){
		case 0: cout << setw(12) << right << "Papeleria"; break;
		case 1: cout << setw(12) << right << "Alimentacion"; break;
		case 2: cout << setw(12) << right << "Limpieza"; break;
		case 3: cout << setw(12) << right << "Informatica"; break;
		default:
			break;
		}
		cout << setw(10) << right << gastos[i].gasto << endl;
	}
}

void iniciaGastos(tListaGastos& gastos) {
	gastos[0].clase = papeleria;
	gastos[1].clase = alimentacion;
	gastos[2].clase = limpieza;
	gastos[3].clase = informatica;
	for (int i = 0; i < CLASES; i++){
		gastos[i].gasto = 0;
	}
}