#include "ListaPeliculas.h"
using namespace std;


bool cargar(tListaPeliculas & listaPelis){
	bool carga = false;
	ifstream archivo;
	int numPelis = 0;

	listaPelis.cont = 0;
	archivo.open("peliculas.txt");
	if (archivo.is_open()) {
		archivo >> numPelis;
		archivo.ignore();
		while ((!archivo.fail()) && (listaPelis.cont < numPelis)){
			listaPelis.pelicula[listaPelis.cont] = new tPelicula;
			carga = cargar(*listaPelis.pelicula[listaPelis.cont], archivo);
			listaPelis.cont++;
		}
	}

	return carga;
}

void filtrarPorActor(tListaPeliculas & listaPelis, std::string & nombre){
	tListaPeliculas listaAUX;
	listaAUX.cont = 0;

	for (int i = 0; i < listaPelis.cont; i++) {
		if (interviene(*listaPelis.pelicula[i], nombre)) {
			listaAUX.pelicula[listaAUX.cont] = listaPelis.pelicula[i];
			listaAUX.cont++;
		}
	}

	ordenarPorGenero(listaAUX);
	mostrar(listaAUX);
	
}

void mostrar(tListaPeliculas& listaPelis){
	for (int i = 0; i < listaPelis.cont; i++){
		mostrar(*listaPelis.pelicula[i]);
		cout << "---" << endl;
	}
}

void ordenarPorGenero(tListaPeliculas& listaPelis){
	tPelicula* AUX;
	int cont;

	for (int i = 0; i < listaPelis.cont; i++) {
		cont = i;
		while ((cont > 0) && (listaPelis.pelicula[cont]->genero <= listaPelis.pelicula[cont - 1]->genero)) { //
			if (listaPelis.pelicula[cont]->genero == listaPelis.pelicula[cont - 1]->genero) {
				ordenarPorValoracion(*listaPelis.pelicula[cont - 1], *listaPelis.pelicula[cont]);
			}
			else {
				AUX = listaPelis.pelicula[cont];
				listaPelis.pelicula[cont] = listaPelis.pelicula[cont - 1];
				listaPelis.pelicula[cont - 1] = AUX;
			}
			cont--;
		}
	}
}

void ordenarPorValoracion(tPelicula& pelIZQ, tPelicula& pelDER){
	tPelicula AUX;

	if (pelIZQ.valoracion < pelDER.valoracion) {
		AUX = pelIZQ;
		pelIZQ = pelDER;
		pelDER = AUX;
	}
}

void destruir(tListaPeliculas & listaPelis){
	for (int i = 0; i < listaPelis.cont; i++){
		delete listaPelis.pelicula[i];
	}
}
