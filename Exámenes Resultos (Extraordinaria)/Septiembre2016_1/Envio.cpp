#include "Envio.h"
using namespace std;

bool cargar(tEnvio& envio, std::ifstream& archivo) {
	bool carga = false;
	int numItems = 0;

	envio.cont = 0;

	archivo.ignore();
	getline(archivo, envio.destinatario);
	getline(archivo, envio.ciudad);
	archivo >> numItems;
	envio.item = new tItem[numItems];
	for (int i = 0; i < numItems; i++){
		cargar(envio.item[i], archivo);
		envio.cont++;
	}
	if (!archivo.fail()) { carga = true; }

	return carga;
}

void mostrar(tEnvio& envio) {
	cout << "A " << envio.destinatario << " de " << envio.ciudad << ":" << endl;
	for (int i = 0; i < envio.cont; i++){
		mostrar(envio.item[i]);
	}
}

void destruir(tEnvio& envio) {
	delete[] envio.item;
}

int cantidad(tEnvio& envio, std::string id, int& ini, int&fin, int& pos) {
	int cant = 0;

	if (ini <= fin) {
		pos = (ini + fin) / 2;
		if (id < envio.item[pos].id) {
			fin = pos - 1;
			cant = cantidad(envio, id, ini, fin, pos);
		}
		else if (envio.item[pos].id < id) {
			ini = pos + 1;
			cant = cantidad(envio, id, ini, fin, pos);
		}
		else {
			cant = envio.item[pos].cantidad;
		}
	}

	return cant;
}