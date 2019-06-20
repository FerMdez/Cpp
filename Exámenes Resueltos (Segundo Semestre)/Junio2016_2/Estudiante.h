#ifndef _ESTUDIANTE
#define _ESTUDIANTE

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Constantes:


//Tipos:
typedef struct tEstudiante {
	std::string nombre, NIF, fechaMatricula;
	int nota;
};

//Funciones:
bool cargar(tEstudiante& estudiante, std::ifstream& archivo);
void mostrar(tEstudiante& estudiante);


#endif // !_ESTUDIANTE
