#ifndef _LISTAENVIOS
#define _LISTAENVIOS

#include "Envio.h"

//Constantes:
const int MAX_ENVIOS = 50;

//Tipos:
typedef struct tListaEnvios {
	tEnvio *envio[MAX_ENVIOS];
	int cont;
};

//Funciones:
bool cargar(tListaEnvios& lista);
void mostrar(tListaEnvios& lista);
void ordenarPorCliente(tListaEnvios& lista); //Ordenada por destinatario, de menor a mayor.
void ordenarPorCiudad(tListaEnvios& lista); //Ordena por dirección de envio de mayor a menor.
void destruir(tListaEnvios& lista);

#endif // !_LISTAENVIOS
