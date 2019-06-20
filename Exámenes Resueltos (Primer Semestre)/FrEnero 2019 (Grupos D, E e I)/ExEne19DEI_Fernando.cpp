//Examen Enero 2019 - Grupos D, E e I.
//Fernando Méndez Torrubiano


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Constantes:
const int MAX_MILI = 50;
const int MAX_SUB = 24;


//Tipos:
typedef struct tTiempo {
	int horas, minutos, segundos, milisegundos;
};
typedef struct tSubtitulo {
	tTiempo tiempoIni, tiempoFin;
	string subtitulo;
};
typedef tSubtitulo tSubtitulos[MAX_SUB];
typedef struct tListaSub {
	tSubtitulos subtitulo;
	int contador;
};


//Funciones:
void inicializa(tListaSub&);
bool cargar(tListaSub&);
int toMilisegundos(tTiempo&);
int desajuste(const string&, const int&);
void mostrar(tListaSub&);
void cambiarTexto(tListaSub&);
void buscar(tListaSub&);
bool buscarMili(tListaSub&, const int&, int&);
bool guardar(tListaSub&);
void ejecutarMenu(tListaSub&);
int menu();



int main() {
	tListaSub subtitulos;
	system("chcp 1252");
	system("cls");

	if (cargar(subtitulos)) {
		ejecutarMenu(subtitulos);
		if (guardar(subtitulos)) {
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

void inicializa(tListaSub& subtitulos) {
	subtitulos.contador = 0;
	for (int i = 0; i < MAX_SUB; i++){
		subtitulos.subtitulo[i].tiempoIni.horas = 0;
		subtitulos.subtitulo[i].tiempoIni.minutos = 0;
		subtitulos.subtitulo[i].tiempoIni.segundos = 0;
		subtitulos.subtitulo[i].tiempoIni.milisegundos = 0;
		subtitulos.subtitulo[i].tiempoFin.horas = 0;
		subtitulos.subtitulo[i].tiempoFin.minutos = 0;
		subtitulos.subtitulo[i].tiempoFin.segundos = 0;
		subtitulos.subtitulo[i].tiempoFin.milisegundos = 0;
		subtitulos.subtitulo[i].subtitulo = "";
	}
}

bool cargar(tListaSub& subtitulos) {
	bool cargado = false;
	ifstream archivo;

	inicializa(subtitulos);
	archivo.open("subtitulos.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar el archivo." << endl;
		cargado = false;
	}
	else {
		while ((!archivo.eof()) && (subtitulos.contador < MAX_SUB)) {
			archivo >> subtitulos.subtitulo[subtitulos.contador].tiempoIni.horas;
			archivo.ignore();
			archivo >> subtitulos.subtitulo[subtitulos.contador].tiempoIni.minutos;
			archivo.ignore();
			archivo >> subtitulos.subtitulo[subtitulos.contador].tiempoIni.segundos;
			archivo.ignore();
			archivo >> subtitulos.subtitulo[subtitulos.contador].tiempoIni.milisegundos;
			archivo.ignore();
			archivo >> subtitulos.subtitulo[subtitulos.contador].tiempoFin.horas;
			archivo.ignore();
			archivo >> subtitulos.subtitulo[subtitulos.contador].tiempoFin.minutos;
			archivo.ignore();
			archivo >> subtitulos.subtitulo[subtitulos.contador].tiempoFin.segundos;
			archivo.ignore();
			archivo >> subtitulos.subtitulo[subtitulos.contador].tiempoFin.milisegundos;
			archivo.ignore();
			getline(archivo, subtitulos.subtitulo[subtitulos.contador].subtitulo);
			subtitulos.contador++;
		}
		cargado = true;
	}
	archivo.close();

	return cargado;
}

int toMilisegundos(tTiempo& tiempo) {
	int tiempoMS = 0, tiempoSec = 0, tiempoMin = 0;

	tiempoMin = (tiempo.horas * 60) + tiempo.minutos;
	tiempoSec = (tiempoMin * 60) + tiempo.segundos;
	tiempoMS = (tiempoSec * 1000) + tiempo.milisegundos;

	return tiempoMS;
}

int desajuste(const string& subtitulo, const int& intervalo) {
	int desajuste = 0, tiempoSub = 0, diferencia = 0;

	if (intervalo > 0) {
	tiempoSub = subtitulo.length() * MAX_MILI;
	diferencia = tiempoSub - intervalo;
	desajuste = diferencia / MAX_MILI;
	}

	return desajuste;
}

void mostrar(tListaSub& subtitulos) {

	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));
	for (int i = 0; i < subtitulos.contador; i++){
		cout << "Intervalo: " << toMilisegundos(subtitulos.subtitulo[i].tiempoIni) << " --> " << toMilisegundos(subtitulos.subtitulo[i].tiempoFin) << endl
			<< "Texto: " << subtitulos.subtitulo[i].subtitulo << endl << endl;
	}
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));
}

void cambiarTexto(tListaSub& subtitulos) {
	int pos = 0;

	cout << endl;
	do {
		cout << "Posicion en la lista: ";
		cin >> pos;
	} while (pos < 0 || pos >= subtitulos.contador);

	cout << "Texto: ";
	cin.ignore();
	getline(cin, subtitulos.subtitulo[pos].subtitulo);
}

void buscar(tListaSub& subtitulos) {
	int mili = 0, pos = 0, intervalo = 0;

	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));
	cout << "Milisegundos: ";
	cin >> mili;

	if (buscarMili(subtitulos, mili, pos)) {
		cout << "Encontrado en la posicion: " << pos << endl
			<< "Intervalo: " << toMilisegundos(subtitulos.subtitulo[pos].tiempoIni) << " --> " << toMilisegundos(subtitulos.subtitulo[pos].tiempoFin) << endl
			<< "Texto: " << subtitulos.subtitulo[pos].subtitulo << endl;
		intervalo = toMilisegundos(subtitulos.subtitulo[pos].tiempoFin) - toMilisegundos(subtitulos.subtitulo[pos].tiempoIni);
		cout << "Desajuste: " << desajuste(subtitulos.subtitulo[pos].subtitulo, intervalo) << endl;
	}
	else {
		cout << "No encontrado." << endl;
	}
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));
}

bool buscarMili(tListaSub& subtitulos, const int& mili, int& i) {
	bool encontrado = false;

	while ((!encontrado) && (i < subtitulos.contador)) {
		if ((mili > toMilisegundos(subtitulos.subtitulo[i].tiempoIni)) && (mili < toMilisegundos(subtitulos.subtitulo[i].tiempoFin))) {
			encontrado = true;
		}
		else { 
			i++; 
		}
	}

	return encontrado;
}

bool guardar(tListaSub& subtitulos) {
	bool save = false;
	ofstream archivo;

	archivo.open("subtitulosEX.txt");
	if (!archivo.is_open()) {
		save = false;
	}
	else {
		for (int i = 0; i < subtitulos.contador; i++){
			archivo << toMilisegundos(subtitulos.subtitulo[i].tiempoIni) << " "
				<< toMilisegundos(subtitulos.subtitulo[i].tiempoFin) << " "
				<< subtitulos.subtitulo[i].subtitulo << endl;
		}
		save = true;
	}
	archivo.close();

	return save;
}

void ejecutarMenu(tListaSub& subtitulos) {
	int opc = 1;

	while (opc != 0) {
		opc = menu();
		switch (opc){
		case 0: break;
		case 1: mostrar(subtitulos); system("PAUSE"); break;
		case 2: cambiarTexto(subtitulos); system("PAUSE"); break;
		case 3: buscar(subtitulos); system("PAUSE"); break;
		default:
			break;
		}
		system("cls");
	}

}

int menu() {
	int opc = 0;

	cout << setw(20) << setfill('=') << "MENU" << setw(20) << "\n" << setfill(char(0));
	cout << "1.-Mostrar lista." << endl;
	cout << "2.-Cambiar texto." << endl;
	cout << "3.-Buscar subtitulo." << endl;
	cout << "0.-Salir." << endl;
	cout << setw(40) << setfill('=') << "\n" << setfill(char(0));

	do {
		cout << "Introduzca una opcion: ";
		cin >> opc;
	} while (opc < 0 || opc > 3);

	return opc;
}

