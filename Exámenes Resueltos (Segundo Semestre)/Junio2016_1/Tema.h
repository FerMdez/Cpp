#ifndef _TEMA
#define _TEMA

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Constantes:


//Tipos:
typedef struct tTema {
	std::string titulo, interprete;
	int segundos;
};

//Funciones:
bool cargar(tTema& tema, std::ifstream&);
void mostrar(tTema& tema);


#endif // !_TEMA
