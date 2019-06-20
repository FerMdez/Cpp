//Examen Febrero 2015 - Grupos D, G y H
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


//Constantes:
const int NUM_PROD = 5;
const int NUM_PED = 3;

//Tipos:
typedef struct tProducto {
	string codigo;
	string descripcion;
	float precio;
	bool oferta;
};
typedef tProducto tProductos[NUM_PROD];
typedef struct tListaProductos {
	tProductos producto;
	int contador;
};

typedef struct tCesta {
	string nombre;
	int unidades;
	float precioProducto;
};
typedef tCesta tCestas[NUM_PED];
typedef struct tPedidos{
	tCestas cesta;
	int contador;
};


//Funciones:
void inicia(tListaProductos&, tPedidos&);
bool cargar(tListaProductos&);
void ejecutarMenu(tListaProductos&, tPedidos&);
int menu();
void muestraProductos(tListaProductos&);
string tBoolToString(tListaProductos&, const int&);
void crearCesta(tListaProductos&, tPedidos&);
bool buscarProducto(const tListaProductos&, const tPedidos&);
bool procesaCesta(tListaProductos&, tPedidos&);
float total(tListaProductos&, tPedidos&, const int&, float&);

int main() {
	tListaProductos productos;
	tPedidos pedidos;

	inicia(productos, pedidos);
	if (cargar(productos)) {
		ejecutarMenu(productos, pedidos);
	}

	return 0;
}

void inicia(tListaProductos& productos, tPedidos& pedidos) {
	productos.contador = 0;
	pedidos.contador = 0;
	for (int i = 0; i < NUM_PROD; i++){
		productos.producto[i].codigo = "";
		productos.producto[i].descripcion = "";
		productos.producto[i].precio = 0;
		productos.producto[i].oferta = false;
		if (i < NUM_PED) {
			pedidos.cesta[i].nombre = "";
			pedidos.cesta[i].unidades = 0;
			pedidos.cesta[i].precioProducto = 0;
		}
	}
}

bool cargar(tListaProductos& productos) {
	bool carga = false;
	ifstream archivo;

	archivo.open("productos.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar la lista de productos." << endl;
		carga = false;
	}
	else {
		archivo >> productos.producto[productos.contador].codigo;
		while ((productos.producto[productos.contador].codigo != "XXX") && (productos.contador < NUM_PROD)) {
			archivo >> productos.producto[productos.contador].precio;
			archivo >> productos.producto[productos.contador].oferta;
			getline(archivo, productos.producto[productos.contador].descripcion);
			productos.contador++;
			archivo >> productos.producto[productos.contador].codigo;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void ejecutarMenu(tListaProductos& productos, tPedidos& pedidos) {
	int opc = 1;

	while (opc != 0) {
		muestraProductos(productos);
		opc = menu();
		switch (opc){
		case 0: break;
		case 1: crearCesta(productos, pedidos); break;
		case 2: procesaCesta(productos, pedidos); break;
		default:
			break;
		}
		system("cls");
	}
}

int menu() {
	int opc = 0;

	cout << endl << setw(40) << setfill('=') << "\n" << setw(char(0));
	cout << "1.-Añadir productos a la cesta." << endl;
	cout << "2.-Confirmar pedido." << endl;
	cout << "0.-SALIR." << endl;
	cout << setw(40) << setfill('=') << "\n" << setw(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 2);

	return opc;
}
void muestraProductos(tListaProductos& productos) {
	cout << setw(5) << right << "CODIGO"
		<< setw(25) << "DESCRIPCION"
		<< setw(15) << "PRECIO"
		<< setw(15) << "OFERTA" << endl;
	cout << setw(70) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < productos.contador; i++){
		cout << setw(5) << right << productos.producto[i].codigo
			<< setw(25) << productos.producto[i].descripcion
			<< setw(15) << productos.producto[i].precio
			<< setw(15) << tBoolToString(productos, i) << endl;
	}
	cout << setw(70) << setfill('=') << "\n" << setfill(char(0));
}

string tBoolToString(tListaProductos& productos, const int& pos) {
	string oferta;
	switch (productos.producto[pos].oferta){
	case false: oferta = "NO"; break;
	case true: oferta = "SI"; break;
	}
	return oferta;
}

void crearCesta(tListaProductos& productos, tPedidos& pedidos) {
	int i = 0;

	while ((pedidos.contador < NUM_PED) && (pedidos.cesta[pedidos.contador].nombre != "XXX")) {
		cout << "Introduzca un codigo de producto: ";
		cin >> pedidos.cesta[pedidos.contador].nombre;
		while (!buscarProducto(productos, pedidos)) {
			cout << "Producto no encontrado. Introduzca otro codigo: ";
			cin >> pedidos.cesta[pedidos.contador].nombre;
		}
		if (pedidos.cesta[pedidos.contador].nombre != "XXX") {
			cout << "Introduzca un cantidad de productos: ";
			cin >> pedidos.cesta[pedidos.contador].unidades;
			pedidos.contador++;
		}
	}
	cout << "Cesta llena." << endl;
	system("PAUSE");
}

bool buscarProducto(const tListaProductos& productos, const tPedidos& pedidos) {
	bool encontrado = false;
	int i = 0;

	while ((!encontrado) && (i < productos.contador)) {
		if ((pedidos.cesta[pedidos.contador].nombre == productos.producto[i].codigo) || (pedidos.cesta[pedidos.contador].nombre == "XXX")) {
			encontrado = true;
		}
		else {
			i++;
		}
	}

	return encontrado;
}

bool procesaCesta(tListaProductos& productos, tPedidos& pedidos) {
	bool procesado = false;
	ofstream archivo;
	float totalPrecio = 0;

	archivo.open("ticket.txt");
	if (!archivo.is_open()) {
		cout << "Error al procesar el pedido." << endl;
		procesado = false;
	}
	else {
		for (int i = 0; i < pedidos.contador; i++){
			archivo << pedidos.cesta[i].nombre << " x "
				<< pedidos.cesta[i].unidades << " = ";
			totalPrecio = total(productos, pedidos, i, totalPrecio);
			archivo << pedidos.cesta[i].precioProducto << endl;
		}
		archivo << "Total compra: " << totalPrecio << endl;
		procesado = true;
	}
	archivo.close();

	if(procesado == true){
		cout << "Precio total: " << totalPrecio << endl;
	}
	else{
		cout << "Intentelo de nuevo." << endl;
	}
	
	system("PAUSE");
	return procesado;
}

float total(tListaProductos& productos, tPedidos& pedidos, const int& pos, float& total) {
	int j = 0;
	bool encontrado = false;
	float descuento = 0;

	while ((!encontrado) && (j < productos.contador)) {
		if (pedidos.cesta[pos].nombre == productos.producto[j].codigo) {
			if (productos.producto[j].oferta) {
				descuento = (productos.producto[j].precio * 0.15);
				total += (productos.producto[j].precio - descuento);
				pedidos.cesta[pos].precioProducto = (productos.producto[j].precio - descuento);
			}
			else {
				total += productos.producto[j].precio;
				pedidos.cesta[pos].precioProducto = productos.producto[j].precio;
			}
			encontrado = true;
		}
		else {
			j++;
		}
	}

	return total;
}