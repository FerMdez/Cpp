//Examen Enero 2019 - Grupos A, B, D y G.
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int MAX_PEDIDOS = 50;

//Tipos:
typedef struct tPedido {
	string numPedido, nombreCliente, direccion, codRepartidor;
	bool estado;
};
typedef tPedido tPedidos[MAX_PEDIDOS];
typedef struct tListaPedidos {
	tPedidos pedido;
	int contador;
};

//Funciones:
void inicializa(tListaPedidos&);
bool cargar(tListaPedidos&);
bool actualizarPedido(tListaPedidos&, const string&);
void mostrarPedidos(tListaPedidos&);
int posicionRepartidor(tListaPedidos&, const string&);
void mostrarPedidosRepartidor(tListaPedidos&, const string&);
bool guardarPedidos(tListaPedidos&);
void ejecutarMenu(tListaPedidos&);
int menu();


int main() {
	tListaPedidos pedidos;

	if (cargar(pedidos)) {
		ejecutarMenu(pedidos);
		if (guardarPedidos(pedidos)) {
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

void inicializa(tListaPedidos& pedidos) {
	pedidos.contador = 0;
	for (int i = 0; i < MAX_PEDIDOS; i++){
		pedidos.pedido[i].numPedido = "";
		pedidos.pedido[i].nombreCliente = "";
		pedidos.pedido[i].direccion = "";
		pedidos.pedido[i].codRepartidor = "";
		pedidos.pedido[i].estado = false;
	}
}

bool cargar(tListaPedidos& pedidos) {
	bool carga = false;
	ifstream archivo;

	inicializa(pedidos);
	archivo.open("pedidos.txt");
	if (!archivo.is_open()) {
		cout << "No se ha podido cargar el archivo." << endl;
		carga = false;
	}
	else {
		while ((!archivo.eof()) && (pedidos.contador < MAX_PEDIDOS)) {
			getline(archivo, pedidos.pedido[pedidos.contador].numPedido);
			getline(archivo, pedidos.pedido[pedidos.contador].nombreCliente);
			getline(archivo, pedidos.pedido[pedidos.contador].direccion);
			getline(archivo, pedidos.pedido[pedidos.contador].codRepartidor);
			pedidos.contador++;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

bool actualizarPedido(tListaPedidos& pedidos, const string& numPedido) {
	bool encontrado = false;
	int i = 0;

	while ((!encontrado) && (i < pedidos.contador)) {
		if (pedidos.pedido[i].numPedido == numPedido) {
			pedidos.pedido[i].estado = true;
			encontrado = true;
		}
		else {
			i++;
		}
	}

	return encontrado;
}

void mostrarPedidos(tListaPedidos& pedidos) {
	cout << setw(15) << right << "NUMERO PEDIDO"
		<< setw(25) << "CLIENTE"
		<< setw(40) << "DIRECCION"
		<< setw(15) << "REPARTIDOR"
		<< setw(15) << "ESTADO" << endl;
	cout << setw(115) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < pedidos.contador-1; i++) {
		cout << setw(15) << right << pedidos.pedido[i].numPedido
			<< setw(25) << pedidos.pedido[i].nombreCliente
			<< setw(40) << pedidos.pedido[i].direccion
			<< setw(15) << pedidos.pedido[i].codRepartidor;
		if (pedidos.pedido[i].estado == true) {
			cout << setw(15) << "ENTREGADO" << endl;
		}
		else {
			cout << setw(15) << "PENDIENTE" << endl;
		}
	}
	cout << setw(115) << setfill('=') << "\n" << setfill(char(0));
}

int posicionRepartidor(tListaPedidos& pedidos, const string& codRepartidor) {
	int pos = 0;
	bool encontrado = false;

	while ((!encontrado) && (pos <= pedidos.contador)) {
		if (pedidos.pedido[pos].codRepartidor == codRepartidor) {
			encontrado = true;
		}
		else {
			pos++;
		}
	}

	return pos;
}

void mostrarPedidosRepartidor(tListaPedidos& pedidos, const string& codRepartidor) {
	int pos = posicionRepartidor(pedidos, codRepartidor);

	if (pos < pedidos.contador) {
		cout << endl << "Pedidos pendientes del repartidor: " << codRepartidor << endl;
		cout << setw(70) << setfill('=') << "\n" << setfill(char(0));
		cout << "Numero de pedido: " << pedidos.pedido[pos].numPedido << endl;
		cout << "Cliente: " << pedidos.pedido[pos].nombreCliente << endl;
		cout << "Direccion de entrega: " << pedidos.pedido[pos].direccion << endl;
		cout << setw(70) << setfill('=') << "\n" << setfill(char(0));
	}
	else {
		cout << "Repartidor no encontrado." << endl;
	}

}

bool guardarPedidos(tListaPedidos& pedidos) {
	bool save = false;
	ofstream archivo;

	archivo.open("pendientes.txt");
	if (!archivo.is_open()) {
		save = false;
	}
	else {
		for (int i = 0; i < pedidos.contador; i++){
			if (pedidos.pedido[i].estado == false) {
				archivo << pedidos.pedido[i].numPedido << endl
					<< pedidos.pedido[i].nombreCliente << endl
					<< pedidos.pedido[i].direccion << endl
					<< pedidos.pedido[i].codRepartidor << endl;
			}
		}
		save = true;
	}
	archivo.close();

	return save;
}

void ejecutarMenu(tListaPedidos& pedidos) {
	int opc = 1;
	string codRepartidor, numPedido;

	while (opc != 0) {
		opc = menu();
		switch (opc) {
		case 0: break;
		case 1:  
			cout << "Codigo de repartidor: ";
			cin >> codRepartidor;
			mostrarPedidosRepartidor(pedidos, codRepartidor);
			system("PAUSE"); 
			break;
		case 2: mostrarPedidos(pedidos); system("PAUSE"); break;
		case 3: 
			cout << "Introduzca numero de pedido: ";
			cin >> numPedido;
			if (actualizarPedido(pedidos, numPedido)) {
				cout << "Pedido " << numPedido << " actualizado correctamente." << endl;
			}
			else {
				cout << "Pedido no encontrado." << endl;
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

	cout << setw(20) << setfill('=') << "MENU" << setw(20) << "\n" << setfill(char(0));
	cout << "1.-Mostrar todos los pedidos pendientes de un repartidor." << endl;
	cout << "2.-Mostrar todos los pedidos." << endl;
	cout << "3.-Registro pedido entregado." << endl;
	cout << "0.-Salir." << endl;
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 3);

	return opc;
}