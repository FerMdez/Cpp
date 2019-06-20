//Exámen Febrero 2015 - Grupos C, E y F.
//Fernando Méndez Torrubiano

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


//Constantes:
const int MAX_VIAJES = 10;
const int NUM_PREFERENCIAS = 3;

//Tipos:
typedef enum tCategoria{Mochilero, Turista, Lujo};
typedef struct tViaje {
	string destino;
	int duracion;
	int plazas;
	tCategoria categoria;
};
typedef tViaje tViajes[MAX_VIAJES];
typedef struct tListaViajes {
	tViajes viaje;
	int contador;
};

typedef string tPreferencias[NUM_PREFERENCIAS];

//Funciones:
void inicializa(tListaViajes&);
bool cargarCatalogo(tListaViajes&);
void tIntToCategoria(tListaViajes&, const int&);
void mostrarViajesEnCategoria(tListaViajes&, const int&);
void convertirCat(const int&, tCategoria&);
bool guardarCatalogo(tListaViajes&);
void leerPreferencias(tPreferencias&);
int buscarDestino(tListaViajes&, tPreferencias&, const int&);
bool hacerReserva(tListaViajes&, const int&, tPreferencias&);

int main() {
	tListaViajes viajes;
	tPreferencias preferencia;
	int numCat;

	if (cargarCatalogo(viajes)) {
		cout << "Escriba una categoria (0 Mochilero, 1 Turista, 2 Lujo): ";
		cin >> numCat;
		mostrarViajesEnCategoria(viajes, numCat);
		leerPreferencias(preferencia);
		if (hacerReserva(viajes, numCat, preferencia)) {
			cout << "Gracias por su reserva." << endl;
			guardarCatalogo(viajes);
		}
		else {
			cout << "Vuelva a intentarlo." << endl;
		}
	}
	else {
		cout << "FIN DEL PROGRAMA." << endl;
	}

	system("PAUSE");
	return 0;
}

void inicializa(tListaViajes& viajes) {
	viajes.contador = 0;
	for (int i = 0; i < MAX_VIAJES; i++){
		viajes.viaje[i].destino = "";
		viajes.viaje[i].duracion = 0;
		viajes.viaje[i].plazas = 0;
		viajes.viaje[i].categoria = Mochilero;
	}
}

bool cargarCatalogo(tListaViajes& viajes) {
	bool carga = false;
	ifstream archivo;
	int aux = 0;

	inicializa(viajes);
	archivo.open("catalogoViajes.txt");
	if (!archivo.is_open()) {
		cout << "Error al cargar el archivo." << endl;
		carga = false;
	}
	else {
		archivo >> viajes.viaje[viajes.contador].destino;
		while ((viajes.viaje[viajes.contador].destino != "XXX") && (viajes.contador < MAX_VIAJES)) {
			archivo >> viajes.viaje[viajes.contador].duracion;
			archivo >> viajes.viaje[viajes.contador].plazas;
			archivo >> aux;
			tIntToCategoria(viajes, aux);
			viajes.contador++;
			archivo >> viajes.viaje[viajes.contador].destino;
		}
		carga = true;
	}
	archivo.close();

	return carga;
}

void tIntToCategoria(tListaViajes& viajes, const int& aux) {
	switch (aux) {
	case 0: viajes.viaje[viajes.contador].categoria = Mochilero; break;
	case 1: viajes.viaje[viajes.contador].categoria = Turista; break;
	case 2: viajes.viaje[viajes.contador].categoria = Lujo; break;
	}
}

void mostrarViajesEnCategoria(tListaViajes& viajes, const int& numCategoria) {
	tCategoria categoria;

	convertirCat(numCategoria, categoria);

	cout << setw(10) << right << "DESTINO"
		<< setw(15) << "DURACION"
		<< setw(15) << "PLAZAS" << endl;
	cout << setw(25) << setfill('=') << categoria << setw(25) << "\n" << setfill(char(0));
	for (int i = 0; i < viajes.contador; i++){
		if (viajes.viaje[i].categoria == categoria) {
			cout << setw(10) << right << viajes.viaje[i].destino
				<< setw(15) << viajes.viaje[i].duracion
				<< setw(15) << viajes.viaje[i].plazas << endl;
		}
	}
	cout << setw(50) << setfill('=') << "\n" << setfill(char(0));
}

void convertirCat(const int& numCategoria, tCategoria& categoria) {
	switch (numCategoria) {
	case 0: categoria = Mochilero; break;
	case 1: categoria = Turista; break;
	case 2: categoria = Lujo; break;
	}
}

bool guardarCatalogo(tListaViajes& viajes) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("catalogoViajes.txt");
	if (!archivo.is_open()) {
		cout << "Error al guardar el archivo." << endl;
		guardado = false;
	}
	else {
		for (int i = 0; i < viajes.contador; i++){
			archivo << viajes.viaje[i].destino << " "
				<< viajes.viaje[i].duracion << " "
				<< viajes.viaje[i].plazas << " "
				<< viajes.viaje[i].categoria << endl;
		}
		archivo << "XXX";
		guardado = true;
	}
	archivo.close();

	return guardado;
}

void leerPreferencias(tPreferencias& preferencia) {
	for (int i = 0; i < NUM_PREFERENCIAS; i++) {
		cout << "Escriba sus destinos preferentes (de mayor a menor): ";
		cin >> preferencia[i];
	}
}

int buscarDestino(tListaViajes& viajes, tPreferencias& preferencias, const int& numCategoria) {
	int i = 0, pos = viajes.contador - 1;
	tCategoria categoria;
	bool encontrado = false;

	convertirCat(numCategoria, categoria);

	while ((i < NUM_PREFERENCIAS) && (!encontrado)) {
		pos = viajes.contador - 1;
		while ((pos > -1) && (!encontrado)) {
			if ((viajes.viaje[pos].destino == preferencias[i]) && (viajes.viaje[pos].categoria == categoria) && (viajes.viaje[pos].plazas > 0)) {
				encontrado = true;
			}
			else {
				pos--;
			}
		}
		i++;
	}

	return pos;
}

bool hacerReserva(tListaViajes& viajes, const int& numCategoria, tPreferencias& preferencias) {
	bool reserva = false;
	int posReserva = buscarDestino(viajes, preferencias, numCategoria);

	if (posReserva != -1) {
		cout << "Reservado viaje a " << viajes.viaje[posReserva].destino << endl;
		viajes.viaje[posReserva].plazas--;
		reserva = true;
	}
	else {
		cout << "No hay disponibilidad para esas preferencias." << endl;
		reserva = false;
	}

	return reserva;
}