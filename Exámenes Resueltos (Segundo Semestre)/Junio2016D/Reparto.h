#ifndef H_REPARTO_H
#define H_REPARTO_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Constantes:
const int MAX_ACTORES = 10;

//Tipos:
typedef struct tReparto {
	std::string nombre;
};

//typedef tReparto tListaReparto[MAX_ACTORES];

//Funciones:
bool cargar(tReparto& reparto, std::ifstream&); //Carga la lista del reparto.
bool aparece(tReparto reparto, std::string& nombre, int& pos); //True si encuentra el nombre en la lista, false en caso contrario. Implementar de forma recursiva.

#endif // !H_REPARTO_H

