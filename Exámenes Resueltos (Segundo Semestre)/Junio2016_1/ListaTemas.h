#ifndef _LISTATEMAS
#define _LISTATEMAS

#include "Tema.h"

//Constantes:
const int MAX_TEMAS = 50;

//Tipos:
typedef struct tListaTemas {
	tTema *tema[MAX_TEMAS];
	int cont;	
};

//Funciones:
bool cargar(tListaTemas& lista);
void destruir(tListaTemas& lista);


#endif // !_LISTATEMAS
