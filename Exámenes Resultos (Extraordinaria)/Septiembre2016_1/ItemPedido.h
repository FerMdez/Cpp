#ifndef _ITEMPEDIDO
#define _ITEMPEDIDO

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Constantes:


//Tipos:
typedef struct tItem {
	std::string id, nombre;
	int cantidad;
};

//Funciones:
bool cargar(tItem& item, std::ifstream& archivo);
void mostrar(tItem& item);


#endif // !_ITEMPEDIDO

