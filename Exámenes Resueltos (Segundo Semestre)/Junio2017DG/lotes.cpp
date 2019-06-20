#include "lotes.h"
#include "listaCompradores.h"
using namespace std; 

bool operator<(tLotes& loteIzq, tLotes& loteDer){
	return (loteIzq.tipo < loteDer.tipo);
}

bool operator==(tLotes& loteIzq, tLotes& loteDer){
	return (loteIzq.id == loteDer.id);
}

void mostrarLote(const tLotes& lote){
	cout << right << setw(15) << "Lote: " << lote.lote
		<< setw(25) << setprecision(2) << "Peso del lote: " << lote.peso << endl
		<< setw(15) << "Tipo: " << lote.tipo << setw(25) << "Precio de salida: " << lote.precio << endl << endl;
}

void mostrarPrecio(tLotes & lote, tComprador& comprador){
	cout << right << setw(15) << "Lote: " << lote.lote
		<< setw(25) << setprecision(2) << "Comprador: " << comprador.id << endl
		<< setw(15) << "Tipo: " << lote.tipo << setw(25) << "Precio de compra: " << comprador.importe << endl;
}

void modificarLote(tLotes & lote, long long int& id, float& precio){
	lote.id = id;
	lote.precio = precio;
}
