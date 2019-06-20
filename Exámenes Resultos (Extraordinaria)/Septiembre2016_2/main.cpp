//Examen Septiembre 2016 - FP
//Grupo: _2
//Fernando Méndez Torrubiano


#include "GruposChat.h"
#include "checkML.h"
using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detecta posibles fugas de memoria.
	system("chcp 1252");
	system("cls");

	tListaContactos contactos;
	tGrupoChat grupoA, grupoB, grupoC;
	tElemento elemento;

	srand(1);

	if (cargar(contactos)) {
		cout << "Introduzca nombre de grupo: ";
		cin >> grupoA.nombreGrupo;
		cout << "Introduca número de contactos: ";
		cin >> grupoA.capacidad;
		nuevo(grupoA);

		for (int i = 0; i < grupoA.capacidad; i++) {
			if (i < contactos.cont) {
				elemento.puntero= contactos.contacto[0 + rand() % contactos.cont];
				elemento.numMensajes = 0 + rand() % MAX_CONTACTOS;
				insertar(grupoA, elemento);
			}
		}

		cout << "Introduzca nombre de grupo: ";
		cin >> grupoB.nombreGrupo;
		cout << "Introduca número de contactos: ";
		cin >> grupoB.capacidad;
		nuevo(grupoB);

		for (int i = 0; i < grupoB.capacidad; i++) {
			if (i < contactos.cont) {
				elemento.puntero = contactos.contacto[0 + rand() % contactos.cont];
				elemento.numMensajes = 0 + rand() % MAX_CONTACTOS;
				insertar(grupoB, elemento);
			}
		}

		mostrar(grupoA);
		mostrar(grupoB);
		combinar(grupoA, grupoB, grupoC);
		mostrar(grupoC);
	}
	else {
		cout << "FIN DEL PROGRAMA." << endl;
	}

	system("PAUSE");

	destruir(contactos);
	destruir(grupoA);
	destruir(grupoB);
	destruir(grupoC);

	return 0;
}