#include "ListaCitas.h"
using namespace std;

//Funciones auxiliares:
void ampliar(tListaCitas& listaCitas, int); //Amplia la lista de citas en caso de que se haya llegado al límite de su capacidad.
bool buscar(tListaCitas& listaCitas, const tCita& cita, int& ini, int& fin, int& pos); //Búsqueda binaria y recursiva.

void nuevaLista(tListaCitas& listaCitas) {
	listaCitas.capacidad = 5;
	listaCitas.cont = 0;
	listaCitas.lista = new tCita[listaCitas.capacidad];
}

bool inserta(tListaCitas& listaCitas, const tCita& cita) {
	bool insertado = false;
	int ini = 0, fin = listaCitas.cont - 1, pos = 0;

	if (listaCitas.cont == listaCitas.capacidad) {
		ampliar(listaCitas, listaCitas.capacidad*2);
	}
	else {
		if (!buscar(listaCitas, cita, ini, fin, pos)) {
			for (int i = listaCitas.cont; i > pos; i--){
				listaCitas.lista[i] = listaCitas.lista[i - 1];
			}
			listaCitas.lista[pos] = cita;
			listaCitas.cont++;
			insertado = true;
		}
		else {
			listaCitas.lista[pos] = cita;
		}
	}

	return insertado;
}

//
bool buscar(tListaCitas& listaCitas, const tCita& cita, int& ini, int& fin, int& pos){
	bool encontrado = false;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (cita.valoracion < listaCitas.lista[pos].valoracion) {
			fin = pos - 1;
			encontrado = buscar(listaCitas, cita, ini, fin, pos);
		}
		else if(listaCitas.lista[pos].valoracion < cita.valoracion){
			ini = pos + 1;
			encontrado = buscar(listaCitas, cita, ini, fin, pos);
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}
//

void muestra(const tListaCitas& listaCitas) {
	cout << "Lista de citas: " << endl;
	for (int i = listaCitas.cont - 1; i >= 0; i--){
		cout << setfill(char('-')) << setw(40) << "\n" << setfill(char(0));
		mostrar(*listaCitas.lista[i].puntero1);
		mostrar(*listaCitas.lista[i].puntero2);
		cout << "Cita en: " << setw(10) << listaCitas.lista[i].lugar << setw(20) << "Valoración: " << listaCitas.lista[i].valoracion << endl;
		cout << setfill(char('-')) << setw(40) << "\n" << setfill(char(0));
	}
}

//
void ampliar(tListaCitas& listaCitas, int ampliacion) {
	listaCitas.capacidad = ampliacion;

	tCita* aux;
	aux = new tCita[listaCitas.capacidad];

	for (int i = 0; i < listaCitas.cont; i++){
		aux[i] = listaCitas.lista[i];
	}
	
	delete[] listaCitas.lista;
	listaCitas.lista = aux;

}
//

void libera(tListaCitas& listaCitas) {
	delete[] listaCitas.lista;
}
