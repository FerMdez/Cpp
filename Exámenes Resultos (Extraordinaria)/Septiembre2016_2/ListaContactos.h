#ifndef _LISTACONTACTOS
#define _LISTACONTACTOS

#include "Contacto.h"

//Constantes:
const int MAX_CONTACTOS = 50;

//Tipos:
typedef struct tListaContactos {
	tContacto *contacto[MAX_CONTACTOS];
	int cont;
};

//Funciones:
bool cargar(tListaContactos& lista);
void destruir(tListaContactos& lista);


#endif // !_LISTACONTACTOS
