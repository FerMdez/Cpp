#ifndef  _CONTACTO
#define _CONTACTO

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Constantes:


//Tipos:
typedef struct tContacto {
	std::string id, nombre, email, tlf;
};

//Funciones:
bool cargar(tContacto& contacto, std::ifstream& archivo);
void mostrar(tContacto& contacto);



#endif // ! _CONTACTO
