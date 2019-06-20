//Examen Febrero 2014 - Grupos A, B e I.
//Fernando Méndez Torrubiano.

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int NPO = 10;
const int NPNecesitados = 1;


//Tipos:
typedef struct tProducto {
	string nombre;
	float peso;
	float precio;
};
typedef tProducto tProductos[NPO];
typedef struct tListaProductos {
	tProductos producto;
	int contador;
};


//Funciones:
void inicializa(tListaProductos&);
bool cargar(tListaProductos&);
void ejecutarMenu(tListaProductos&);
int menu();
bool guardar(tListaProductos&);
tListaProductos leerCesta(tListaProductos&);
int buscarProducto(tListaProductos&, const string&);
void realizarCompra(tListaProductos&, tListaProductos&);
void mostrarAgotados(tListaProductos&);


int main() {
	tListaProductos productos;

	if (cargar(productos)) {
		ejecutarMenu(productos);
		if (guardar(productos)) {
			cout << "Guardado correctamente." << endl;
		}
		else {
			cout << "Error al guardar." << endl;
		}
	}
	else {
		cout << "Fin del programa." << endl;
	}
	system("PAUSE");

	return 0;
}

void inicializa(tListaProductos& productos) {
	productos.contador = 0;
	for (int i = 0; i < NPO; i++){
		productos.producto[i].nombre = "";
		productos.producto[i].peso = 0;
		productos.producto[i].precio = 0;
	}
}

bool cargar(tListaProductos& productos) {
	bool carga = false;
	ifstream archivo;

	inicializa(productos);
	archivo.open("almacen.txt");
	if (!archivo.is_open()) {
		cout << "No se ha encotrado el archivo." << endl;
		carga = false;
	}
	else {
		getline(archivo, productos.producto[productos.contador].nombre);
		while ((productos.producto[productos.contador].nombre != "XXX") && (productos.contador < NPO)) {
			archivo >> productos.producto[productos.contador].peso;
			archivo >> productos.producto[productos.contador].precio;
			productos.contador++;
			archivo.ignore(1, ' ');
			getline(archivo, productos.producto[productos.contador].nombre);
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void ejecutarMenu(tListaProductos& productos) {
	tListaProductos cesta;
	int opc = 1;

	while (opc != 0) {
		opc = menu();
		switch (opc){
		case 0: break;
		case 1: realizarCompra(productos, cesta); system("PAUSE"); break;
		case 2: mostrarAgotados(productos); system("PAUSE"); break;
		default:
			break;
		}
		system("cls");
	}
}

int menu() {
	int opc = 0;

	cout << setw(20) << setfill('=') << "MENU" << setw(20) << "\n" << setfill(char(0));
	cout << "1.-Realizar la compra" << endl;
	cout << "2.-Ver productos agotados" << endl;
	cout << "0.-Salir" << endl;
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 2);

	return opc;
}

bool guardar(tListaProductos& productos) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("almacen.txt");
	if (!archivo.is_open()) {
		guardado = false;
	}
	else {
		for (int i = 0; i < productos.contador; i++){
			archivo << productos.producto[i].nombre << endl;
			archivo << productos.producto[i].peso << endl;
			archivo << productos.producto[i].precio << endl;
		}
		archivo << "XXX";
		guardado = true;
	}
	archivo.close();

	return guardado;
}

tListaProductos leerCesta(tListaProductos& productos) {
	tListaProductos cesta;
	cesta.contador = 0;
	string nombre;
	int pos = 0;

	while (cesta.contador < NPNecesitados) {
		do {
			cout << "Introduzca un produto: ";
			getline(cin, nombre);
			pos = buscarProducto(productos, nombre);
		} while (pos == -1);
		cesta.producto[cesta.contador].nombre = nombre;
		do {
			cout << "Introduzca cantidad (KG): ";
			cin >> cesta.producto[cesta.contador].peso;
		} while (cesta.producto[cesta.contador].peso > productos.producto[pos].peso);
		productos.producto[pos].peso -= cesta.producto[cesta.contador].peso;
		cesta.producto[cesta.contador].precio = cesta.producto[cesta.contador].peso * productos.producto[pos].precio;
		cesta.contador++;
	}

	return cesta;
}

//SCARLETT JONHANSON ESTUVO AQUÍ
//No, solo eres eva intentando gastar bromas
//NO NO NO NO NOOOOO, bueno si. Me hacia ilu jo :,(
//Eres idiota
//Teniendo en cunta que tu eres yo y que yo soy tu, te estas llamando idiota a ti misma. 
//-_-
//:3
//PONTE A ESTUDIAR O TE MATO!!
// AH! 0-0 si señora.


int buscarProducto(tListaProductos& productos, const string& nombre) {
	int pos = productos.contador;
	bool encontrado = false;

	while ((!encontrado) && (pos > -1)) {
		if (productos.producto[pos].nombre == nombre) {
			encontrado = true;
		}
		else {
			pos--;
		}
	}

	return pos;
}

void realizarCompra(tListaProductos& productos, tListaProductos& cesta) {

	cout << setw(15) << right << "NOMBRE"
		<< setw(15) << "CANTIDAD"
		<< setw(15) << "PRECIO" << endl;
	cout << setw(25) << setfill('=') << "ALMACEN" << setw(25) << "\n" << setfill(char(0));
	for (int i = 0; i < productos.contador; i++) {
		cout << setw(15) << right << productos.producto[i].nombre
			<< setw(15) << productos.producto[i].peso
			<< setw(15) << productos.producto[i].precio << endl;
	}
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));

	cesta = leerCesta(productos);

	cout << setw(15) << right << "NOMBRE"
		<< setw(15) << "CANTIDAD"
		<< setw(15) << "PRECIO" << endl;
	cout << setw(25) << setfill('=') << "CESTA" << setw(25) << "\n" << setfill(char(0));
	for (int i = 0; i < cesta.contador; i++){
		cout << setw(15) << right << cesta.producto[i].nombre
			<< setw(15) << cesta.producto[i].peso
			<< setw(15) << cesta.producto[i].precio << endl;
	}
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
}

void mostrarAgotados(tListaProductos& productos) {
	cout << setw(15) << right << "NOMBRE"
		<< setw(15) << "CANTIDAD"
		<< setw(15) << "PRECIO" << endl;
	cout << setw(25) << setfill('=') << "AGOTADOS" << setw(25) << "\n" << setfill(char(0));
	for (int i = 0; i < productos.contador; i++) {
		if (productos.producto[i].peso == 0) {
			cout << setw(15) << right << productos.producto[i].nombre
				<< setw(15) << productos.producto[i].peso
				<< setw(15) << productos.producto[i].precio << endl;
		}
	}
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
}