#ifndef _GRUPOS
#define _GRUPOS

#include "listaMatriculas.h"

//Constantes:
const int MAX_ALUMNOS = 10;

//Tipos:
typedef struct tAlumno {
	tMatricula *puntero;
	std::string correo;
};

typedef struct tGrupo {
	tAlumno *alumnos;
	std::string id;
	int aula;
	int cont;
};

//Funciones:
void nuevo(tGrupo& grupo, std::string& id, int& aula);
void leer(tListaMatriculas& listaMatriculas, tGrupo& grupo);
void mostrarAlumno(tAlumno& alumno);
void insertarAlumno(tGrupo& grupo, tMatricula* matricula, std::string& correo);
bool buscarAlumno(tGrupo& grupo, std::string& nif, int& pos);
void eliminarAlumno(tGrupo& grupo, std::string& nif);
void mostrarGrupo(tGrupo& grupo);
void liberar(tGrupo& grupo);

#endif // !_GRUPOS

