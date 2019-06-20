#ifndef _ENVIO
#define _ENVIO

#include "ItemPedido.h"

//Constantes:


//Tipos:
typedef struct tEnvio {
	tItem *item;	//NO ORDENADA.
	std::string destinatario, ciudad;
	int cont;
};

//Funciones:
bool cargar(tEnvio& envio, std::ifstream& archivo);
void mostrar(tEnvio& envio);
void destruir(tEnvio& envio);
int cantidad(tEnvio& envio, std::string id, int& ini, int&fin, int& pos); //Recursiva.


#endif // !_ENVIO