#ifndef _coordenada
#define _coordenada

using namespace std;

typedef struct { int _fila; int _columna; } tCoordenada;


//Dada una fila y una columna construye una coordenada con ellas
tCoordenada crearCoordenada(int f, int c);

//Consulta la componente fila de una coordenada
int fila(const tCoordenada &c);

//Consulta la componente columna de una coordenada
int columna(const tCoordenada &c);


//Dada una coordenada y una dirección(entre 0 y 7 inclusive), 
//calcula una nueva coordenada en la dirección indicada, segun el siguiente dibujo
// 0 1 2
// 7   3
// 6 5 4
//Esta funcion no comprueba si la nueva coordenada esta dentro de los limites del jardin.
void calcularCoordenada(const tCoordenada & c, int dir, tCoordenada & nc);

//Funciones para comprobar la igualdad o desigualdad de dos coordenadas
bool operator== (const tCoordenada &c1, const tCoordenada &c2);
bool operator!= (const tCoordenada &c1, const tCoordenada &c2);


#endif