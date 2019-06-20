#include "GruposChat.h"
using namespace std;

void nuevo(tGrupoChat& grupo) {
	grupo.cont = 0;
	grupo.elemento = new tElemento[grupo.capacidad];
}

void insertar(tGrupoChat& grupo, tElemento& element) {
	int ini = 0, fin = grupo.cont - 1, pos = 0;

	if ((grupo.cont < grupo.capacidad) && (!buscar(grupo, element.puntero->id, ini, fin, pos))) {
		for (int i = grupo.cont; i > pos; i--){
			grupo.elemento[i] = grupo.elemento[i - 1];
		}
		grupo.elemento[pos] = element;
		grupo.cont++;
	}
}

bool buscar(tGrupoChat& grupo, std::string& id, int& ini, int& fin, int& pos) {
	bool encontrado = false;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (id < grupo.elemento[pos].puntero->id) {
			fin = pos - 1;
			encontrado = buscar(grupo, id, ini, fin, pos);
		}
		else if (grupo.elemento[pos].puntero->id < id) {
			ini = pos + 1;
			encontrado = buscar(grupo, id, ini, fin, pos);
		}
		else {
			encontrado = true;
		}
	}

	return encontrado;
}

void mostrar(tGrupoChat& grupo) {
	int totalMensajes = 0;

	cout << setfill(char('-')) << setw(50) << "\n" << setfill(char(0));
	cout << "Grupo de chat: " << grupo.nombreGrupo << endl;
	cout << setfill(char('-')) << setw(50) << "\n" << setfill(char(0));
	for (int i = 0; i < grupo.cont; i++) {
		mostrar(*grupo.elemento[i].puntero);
		cout << right << setw(20) << "Número de mensajes: " << grupo.elemento[i].numMensajes << endl;
		totalMensajes += grupo.elemento[i].numMensajes;
	}
	cout << endl << "TOTAL MENSAJES: " << totalMensajes << endl;
}

void combinar(tGrupoChat& grupoA, tGrupoChat& grupoB, tGrupoChat& grupoC) {
	int contAUX = grupoA.cont + grupoB.cont;

	grupoC.capacidad = grupoA.capacidad + grupoB.capacidad;
	grupoC.nombreGrupo = grupoA.nombreGrupo + " y " + grupoB.nombreGrupo;
	nuevo(grupoC);
	for (int i = 0; i < contAUX; i++){
		if (i < grupoA.capacidad) {
			insertar(grupoC, grupoA.elemento[i]);
		}
		if (i < grupoB.cont) {
			insertar(grupoC, grupoB.elemento[i]);
		}
	}

}

void destruir(tGrupoChat& grupo) {

	delete[] grupo.elemento;
}