#include "coordenada.h"

tCoordenada crearCoordenada(int f, int c)
{
	tCoordenada coordenada;
	coordenada._fila = f; coordenada._columna = c;
	return coordenada;
}


bool operator== (const tCoordenada &c1, const tCoordenada &c2)
{
	return c1._fila == c2._fila && c1._columna == c2._columna;
}

bool operator!= (const tCoordenada &c1, const tCoordenada &c2)
{
	return !(c1 == c2);
}

int fila(const tCoordenada &c){
	return c._fila;
}
int columna(const tCoordenada &c)
{
	return c._columna;
}

void calcularCoordenada(const tCoordenada & c, int dir, tCoordenada & nc)
{
	if ((0 <= dir) && (dir <= 2)) { nc._fila = c._fila - 1; }
	else if ((dir == 3) || (dir == 7)) { nc._fila = c._fila; }
	else { nc._fila = c._fila + 1; }
	switch (dir)
	{
	case 0:
	case 6:
	case 7:
		nc._columna = c._columna - 1; break;
	case 1:
	case 5: nc._columna = c._columna; break;
	default: nc._columna = c._columna + 1;
		break;
	}

}