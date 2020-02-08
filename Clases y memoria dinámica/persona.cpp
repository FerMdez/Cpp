#include "persona.h"
using namespace std;

Persona::Persona() {
	_nombre = "Empty";
	_apellidos = "NULL NULL";
	_NIF = "NULL";
	_edad = "0";
}

Persona::Persona(std::string nombre, std::string apellidos, std::string NIF, std::string edad){
	_nombre = nombre;
	_apellidos = apellidos;
	_NIF = NIF;
	_edad = edad;
}


void Persona::mostrar() {
	cout << setw(10) << right
		<< this->_nombre << setw(20)
		<< this->_apellidos << setw(20)
		<< this->_NIF << setw(15)
		<< this->_edad;
}