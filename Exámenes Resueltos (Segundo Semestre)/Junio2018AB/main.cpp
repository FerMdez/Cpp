#include "listaCoordenadas.h"
#include "listaJugadores.h"
#include "jardin.h"
#include <iostream>
#include <fstream>

using namespace std;


void mostrarMenu(); //menu principal
void mostrarMenu2(); //menu para mostrar: opcion 2
int leerOpcion(int ini, int fin); //entre los valores ini y fin
string leerNombreFichero(); 


void ejecutarJuego(tListaJugadores &js); //ejecutar opcion 1
void leerCoordenadas(const tJardin &j, tListaCoordenadas &cs); //leer las coordenadas de los aspersores
void regarJardin(tJardin & j, tListaCoordenadas &cs); //regar todo el jardin: consume la lista de coordenadas


void ejecutarMostrarJugadores(const tListaJugadores &js); //ejecutar opcion 2

void ejecutarPlantaCondenada(); //ejecutar opcion 3







int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	tListaJugadores js;
	ifstream ijugadores;
    //Cargar los jugadores
	ijugadores.open("jugadores.txt");
	if (ijugadores.is_open()){
		cargarJugadores(js, ijugadores);
	}
	else { cout << "No se ha podido cargar fichero.";}
	ijugadores.close();

	int op,op2;
	
	do{
	
	mostrarMenu();
	op = leerOpcion(0,3);
	switch (op){
	case 0: cout << "Adios."; system("pause"); break;
	case 1: ejecutarJuego(js); break;
	case 2:ejecutarMostrarJugadores(js); break;
	case 3: ejecutarPlantaCondenada(); break;	     
	default: break;
	}
	} while (op != 0);




	//Guardar los jugadores
	ofstream ofjugadores;
	ofjugadores.open("jugadores.txt");
	guardarJugadores(js, ofjugadores);
	ofjugadores.close();

	liberar(js);
}


void leerCoordenadas(const tJardin &j, tListaCoordenadas &cs){
	int fila, columna;
	tCoordenada c;

	cout << "Introduzca las coordenadas. Para terminar introduzca -1. \n";


	crearVacia(cs);

	cout << "Coordenada: ";
	cin >> fila;
	while (!cin.fail() && fila != -1)
	{
		cin >> columna;
		c = crearCoordenada(fila, columna);

		if (esLibre(j, c))
		{
			if (!insertar(cs, c)) {
				cout << "Repetida. \n";
			}
		}
		else { cout << "Esa parcela no está libre.\n"; }

		cout << "Coordenada: ";
		cin >> fila;

	}
}




void regarJardin(tJardin & j, tListaCoordenadas &cs)
{
	int puntos; tCoordenada c;
	while (sacar(cs,c))
	{
		regar(j, c);
	};

}

void mostrarMenu()
{
	system("cls");
	cout << "1. Jugar." << endl;
	cout << "2. Mostrar jugadores." << endl;
	cout << "3. Planta condenada?." << endl;
	cout << "0.Salir." << endl;
	cout << "Introduce una opcion: ";

}

void mostrarMenu2()
{
	system("cls");
	cout << "1. Mostrar jugadores ordenados por nombre." << endl;
	cout << "2. Mostrar jugadores ordenados por puntuacion." << endl;
	cout << "0.Volver." << endl;
	cout << "Introduce una opcion: ";

}

int leerOpcion(int ini, int fin)
{
	int i;
	cin >> i;
	while (cin.fail() || i<ini || i>fin)
	{
		cin.clear(); cin.sync();
		cout << "Opcion incorrecta. Introduce una opcion:";
		cin >> i;
	};
	cin.sync();
	return i;
}


string leerNombreFichero()
{
	string nfichero;
	cout << "Introduce el nombre del fichero: ";
	cin >> nfichero;
	return nfichero;

}




void ejecutarPlantaCondenada()
{

	tJardin j; tCoordenada c;
	string nfichero = leerNombreFichero();
	ifstream fjardin;
	fjardin.open(nfichero);
	if (fjardin.is_open())
	{
		cargarJardin(j, fjardin);
		if (plantaCondenada(j, c)) { cout << "Tiene al menos una planta condenada, en la coordenada: " << fila(c) << " " << columna(c) << endl; }
		else { cout << "No tiene plantas condenadas.\n"; }
	}
	else { cout << "No se ha podido abrir.\n"; }
	system("pause");
}


void ejecutarMostrarJugadores(const tListaJugadores &js)
{
	int op;
	mostrarMenu2();
	op = leerOpcion(0, 2);
	if (op == 1) {
		mostrarJugadores(js);
	}
	else if (op == 2) {
		mostrarPorPuntos(js);
	}
}


void ejecutarJuego(tListaJugadores &js)
{
	string nombre, njardin;
	ifstream fjardin;
	tJardin j;
	tListaCoordenadas cs;
	int puntos;

	cout << "Introduzca el nombre del jugador: ";
	cin >> nombre;
	njardin = leerNombreFichero();
	fjardin.open(njardin);
	if (fjardin.is_open())
	{
		cargarJardin(j, fjardin);
		mostrarJardin(j);
		leerCoordenadas(j, cs);
		regarJardin(j, cs);
		puntos = calcularPuntuacion(j);
		cout << nombre << ", has conseguido " << puntos << " puntos!.\n";
		system("pause");
		actualizarPuntuacion(js, nombre, puntos);
	}
	else { cout << "No se ha podido abrir."; }
	fjardin.close();
}

