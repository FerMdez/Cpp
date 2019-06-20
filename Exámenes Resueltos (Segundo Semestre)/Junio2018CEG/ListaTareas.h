#ifndef H_LISTATAREAS_H
#define H_LISTATAREAS_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Constantes:
const int MAX_TAREAS = 15;
const int MAX_TIPOS = 7;
const int ANIOS = 5;

//Tipos:
typedef int tPrioridades[ANIOS][MAX_TIPOS];

typedef struct tTarea {
	int codigo;
	std::string descripcion;
	int tiempo;
};

typedef struct tListaTareas {
	tTarea tarea[MAX_TAREAS];
	int cont;
};

//Funciones:
bool cargarPrioridades(tPrioridades& prioridad);
bool cargarTareas(tListaTareas& lista, tPrioridades&, std::ifstream&);
int calcularTiempo(tListaTareas& lista, tPrioridades&);
void mostrarTareas(tListaTareas& lista);

#endif // !H_LISTATAREAS_H
