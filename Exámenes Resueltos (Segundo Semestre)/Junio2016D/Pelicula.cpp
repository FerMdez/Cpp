#include "Pelicula.h"
using namespace std;

bool cargar(tPelicula& pelicula, ifstream& archivo){
	bool cargado = false;
	pelicula.contReparto = 0;

	getline(archivo, pelicula.titulo);
	getline(archivo, pelicula.director);
	getline(archivo, pelicula.genero);
	getline(archivo, pelicula.valoracion);
	archivo >> pelicula.contReparto;
	archivo.ignore();
	for (int i = 0; i < pelicula.contReparto; i++){
		cargado = cargar(pelicula.listaReparto[i], archivo);
	}

	return cargado;
}

bool interviene(tPelicula& pelicula, std::string& nombre){
	bool encontrado = false;
	int j = 0;

	while(!encontrado && j < pelicula.contReparto){
		if (pelicula.listaReparto[j].nombre == nombre) {
			encontrado = true;
		}
		else {
			j++;
		}
	}

	return encontrado;
}

void mostrar(tPelicula& pelicula){
	cout << "Titulo:" << setw(5) << pelicula.titulo << endl
		<< "Director: " << setw(5) << pelicula.director << endl
		<< "Género:" << setw(5) << pelicula.genero << endl
		<< "Valoracion:" << setw(5) << pelicula.valoracion << endl;
}
