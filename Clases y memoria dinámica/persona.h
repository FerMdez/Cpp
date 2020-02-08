#ifndef _Persona
#define _Persona

#include <iostream>
#include <string>
#include <iomanip>

class Persona{
public:
	//Constructoras:
	Persona();
	Persona(std::string, std::string, std::string, std::string);

	//Métodos públicos:
	void mostrar(); //Muestra los atributos de una persona.

private:
	//Atributos:
	std::string _nombre, _apellidos, _NIF, _edad;

	//Métodos privados:
};

#endif // !_Persona
