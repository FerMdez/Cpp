//Juego de las 7 y media
//Fernando M�ndez

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//Constantes:
const int PERSONA = 1; //Constante global, representa al JUGADOR.
const int MAQUINA = 2; //Constante global, representa a la MAQUINA.
const int limiteInf = 3; //Constante glogal. L�mite inferior de cartas que se pueden sacar en los modos "A" y "B".
const int limiteSup = 5; //Constante glogal. L�mite superior de cartas que se pueden sacar en los modos "A" y "B".
const int TIPOCARTAS = 8; //Constante glogal. Representa el tipo de cartas que hay en la baraja espa�ola (figuras y del 1 al 7).
const int MAXCARTAS = 40; //Constante global. Representa el n�mero total de cartas que contiena la baraja espa�ola.
const int MAX_BARRAS = MAXCARTAS * 2 + 18; //IMPORTANTE: esta constante sirve s�lo para decorar los resultados extra que se muestran al activar el modo depurar. No es necesaria, se puede eliminar y no afecta a la correcta ejecuci�n del juego.
const bool DEPURAR = false; //Constante global booleana. Si es "TRUE" el modo depuraci�n estar� activado (en este caso, toda la informaci�n extra, apararecer� entre guiones). Si es "FALSE", el modo depuraci�n estar� desactivado.

//Tipos:
typedef int tCartas;
typedef tCartas tCartasPorAparecer[TIPOCARTAS];

typedef int tBaraja[MAXCARTAS];
typedef struct {
	tBaraja mazo;
	int contador;
} tConjuntoCartas;

//Funciones:
void version1(char op); //Permite jugar a los modos de juego "A" y "B".
void version2(); //Permite jugar al modo de juego "C".
void version3(int& numPartidas); //Permite jugar al modo de juego "D".

double modoA(ifstream& mazo, int numCartas); //Permite a cualquiera de los dos jugadores realizar su turno en el modo de juego A.
double modoB(ifstream& mazo, int numCartas, int turno, double puntosContrario); //Permite jugar al jugador del turno (Persona o Maquina) en el modo B.
double modoC(ifstream& mazo, tCartasPorAparecer cartas, int turno, double puntosContrario); //Permite�jugar�al�jugador�del�turno�(Persona�o�Maquina)�en�el� modo�C.
double modoD(tConjuntoCartas& mazo, tCartasPorAparecer cartas, int turno, double puntosContrario, tConjuntoCartas& cartasJugador); //Permite jugar al jugador del�turno�en�el�modo�D.

int determinaGanador(double puntosJugador, double puntosMaquina); //Recibe los�puntos�obtenidos�por�el�jugador�humano�y�por�la�m�quina,�y�devuelve�un�valor�que�indica�qui�n�gana�(utiliza�las�constantes�Hombre,�Maquina).
int determinaGanador(double puntosJugador, double puntosMaquina, const tConjuntoCartas& cartasJugador, const tConjuntoCartas& cartasMaquina); //Recibe�los�puntos�obtenidos�por�el�jugador�humano�y�por�la�m�quina, as� como las cartas sacadas por ambos.�Y�devuelve�un�valor�que�indica�qui�n�gana�(utiliza�las�constantes�Hombre,�Maquina).
bool abrirArchivo(ifstream & mazo); //Pide el nombre del archivo donde est� el mazo de cartas y si se puede abrir devuelve el mazo y true, y en otro caso false.
int menu(); //Muestra el men� del programa con las opciones posibles. Devuelve la opci�n elegida por el usuario.
void ejecutarMenu(); //Ejecuta la opci�n del men� que ha elegido el usuario en la funcion menu().
int generarAleatorio(); //Genera un n�mero aleatorio entre un l�mite inferior y un l�mite superior.

bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas); //Determina�si�la�probabilidad�que�tiene�la�m�quina�de�pasarse si�robara�una�carta�m�s�es�mayor�que�0,5.
int sacarCarta(ifstream& mazo, double& puntos); //Extrae una carta del mazo.
void restarCarta(tCartasPorAparecer cartas, const int carta); //Elimina del array la carta que acaba de salir.
void inicializa(tCartasPorAparecer& cartas); //Inicializa el array con los n�meros correspondientes a una baraja de cartas espa�ola.

void iniciar(tConjuntoCartas& cartas); //Inicializa�cartas�a�la�lista�vac�a.
void sacar(tConjuntoCartas& cartas, int& carta); //Elimina�la��ltima�carta�de la�lista�cartas (pop_back) y�la�devuelve�en�carta.
void incluir(tConjuntoCartas& cartas, int carta); //A�ade�una�carta�al final�de�la�lista�cartas�(push_back).
void crearMazo(tConjuntoCartas& mazo); //Rellena mazo con�40�cartas�dispuestas�de�forma�aleatoria.
void barajar(tConjuntoCartas& mazo); //Mezcla la baraja de forma aleatoria;
void sumarPuntos(double&puntos, int carta); //Suma los puntos correspondientes a la carta extraida.
bool cargarMazo(tConjuntoCartas& mazo); //Carga un mazo de cartas.
void guardarResultado(int& numPartidas, int ganador, double& puntosJugador, double& puntosMaquina, tConjuntoCartas& cartasJugador, tConjuntoCartas& cartasMaquina); //Guarda el resultado de la partida actual.
void depurar(tConjuntoCartas& mazo, const int turno, tConjuntoCartas& cartasJugador); //Muestra la baraja de cartas cargada desde un archivo de texto y las cartas extraidas por el jugador o por la m�quina, en cada caso.


int main() {
	if (DEPURAR == false) { srand(time(nullptr)); }
	else { srand(1); }

	ejecutarMenu();

	return 0;
}

int menu() {
	//Par�metros: no tiene.
	//Devuelve: la opci�n del men� elegida por el usuario.

	int opc = 1;

	cout << "<--------------Menu-------------->" << endl;
	cout << " 1-Jugar MODO A." << endl;
	cout << " 2-JUGAR MODO B." << endl;
	cout << " 3-JUGAR MODO C." << endl;
	cout << " 4-JUGAR MODO D." << endl;
	cout << " 0-Salir" << endl;
	cout << "<-------------------------------->" << endl;
	cout << endl;

	cout << "Seleccione una opcion del menu: ";
	cin >> opc;
	while (opc < 0 || opc > 4) {
		cout << "Seleccione una opcion del menu (entre 0 y 4): ";
		cin >> opc;
	}

	return opc;
}

void ejecutarMenu() {
	//Par�metros: no tiene.

	int opcion = 1; //Entero que representa la opci�n escogida por el jugador.
	int numPartidas = 0; //Entero que representa el n�mero de partidas jugadas al modo D, desde que se inicia el programa.

	system("cls");
	while (opcion != 0) {
		opcion = menu();
		switch (opcion) {
		case 1: version1(opcion); break;
		case 2: version1(opcion); break;
		case 3: version2(); break;
		case 4: version3(numPartidas); break;
		case 0: break;
		}
	}
}

bool abrirArchivo(ifstream& mazo) {
	bool carga = true; //Variable booleana que indica si el archivo ha cargado correctamente.
	string archivo; //Archivo a cargar. Se iguala al nombre del archivo, con extensi�n, introducido por el usuario.

	cout << "Introduzca el nombre del fichero: ";
	cin >> archivo;
	cout << endl;

	mazo.open(archivo);
	if (!mazo.is_open()) {
		cout << "No se ha encontrado el archivo." << endl;
		carga = false;
	}
	else {
		carga = true;
	}

	//mazo.close();

	return carga; //Devuelve true en caso de carga correcta del archivo, false en caso contrario.
}

void version1(char op) {
	ifstream mazo; //Archivo que carga el mazo.
	bool carga = abrirArchivo(mazo); //Variable booleana que se iguala a la funci�n arbrirArchivo(). Ser� true en caso de que el mazo se haya cargado, false en caso contrario.
	int numCartas = generarAleatorio(); //N�mero de cartas que puede robar el jugador en esa ronda, se genera de forma aleatoria.
	int ganador = 0; //Variable entera que determina el ganador de la partida.

	double puntosJugador = 0; //Puntos del jugador.
	double puntosMaquina = 0; //Puntos de la m�quina.
	int turno = 0; //Variable entera, determina si el turno es del JUGADOR o de la M�QUINA. (MODO B).


	if (carga == true) {

		cout << "Numero de cartas: " << numCartas << endl;

		cout << "--------------" << endl;
		cout << "TURNO JUGADOR" << endl;
		cout << "--------------" << endl;

		if (op == 1) {
			puntosJugador = modoA(mazo, numCartas);
			cout << "Puntos Jugador: " << puntosJugador << endl << endl;
		}

		if (op == 2) {
			turno = PERSONA;
			puntosJugador = modoB(mazo, numCartas, turno, puntosJugador);
			cout << "Puntos Jugador: " << puntosJugador << endl << endl;
		}

		if (puntosJugador <= 7.5) {
			cout << "--------------" << endl;
			cout << "TURNO MAQUINA" << endl;
			cout << "--------------" << endl;

			if (op == 1) {
				puntosMaquina = modoA(mazo, numCartas);
			}
			if (op == 2) {
				turno = MAQUINA;
				puntosMaquina = modoB(mazo, numCartas, turno, puntosJugador);
			}

			cout << "Puntos Maquina: " << puntosMaquina << endl << endl;
		}

		ganador = determinaGanador(puntosJugador, puntosMaquina);
		if (ganador == 1) {
			cout << "GANA JUGADOR" << endl << endl;
		}
		else {
			cout << "GANA MAQUINA" << endl << endl;
		}
	}

	mazo.close();
	system("pause");
	system("cls");
}

void version2() {
	tCartasPorAparecer cartas;
	ifstream mazo; //Archivo que carga el mazo.
	bool carga = abrirArchivo(mazo); //Variable booleana que se iguala a la funci�n arbrirArchivo(). Ser� true en caso de que el mazo se haya cargado, false en caso contrario.

	double puntosJugador = 0; //Puntos del jugador.
	double puntosMaquina = 0; //Puntos de la m�quina.
	int turno = 0; //Variable entera, determina si el turno es del JUGADOR o de la M�QUINA.
	int ganador = 0; //Variable entera que determina el ganador de la partida.

	inicializa(cartas); //Inicializa las cartas que quedan por aparecer.

	if (carga == true) {

		cout << "--------------" << endl;
		cout << "TURNO JUGADOR" << endl;
		cout << "--------------" << endl;

		turno = PERSONA;
		puntosJugador = modoC(mazo, cartas, turno, puntosJugador);
		cout << "Puntos Jugador: " << puntosJugador << endl << endl;

		if (puntosJugador <= 7.5) {
			cout << "--------------" << endl;
			cout << "TURNO MAQUINA" << endl;
			cout << "--------------" << endl;

			turno = MAQUINA;
			puntosMaquina = modoC(mazo, cartas, turno, puntosJugador);
			cout << "Puntos Maquina: " << puntosMaquina << endl << endl;
		}

		ganador = determinaGanador(puntosJugador, puntosMaquina);
		if (ganador == 1) {
			cout << "GANA JUGADOR" << endl << endl;
		}
		else {
			cout << "GANA MAQUINA" << endl << endl;
		}
	}

	mazo.close();
	system("pause");
	system("cls");
}

void version3(int& numPartidas) {
	tCartasPorAparecer cartas;
	tConjuntoCartas mazo;
	tConjuntoCartas cartasJugador;
	tConjuntoCartas cartasMaquina;

	double puntosJugador = 0; //Puntos del jugador.
	double puntosMaquina = 0; //Puntos de la m�quina.
	int turno = 0; //Variable entera, determina si el turno es del JUGADOR o de la M�QUINA.
	int ganador = 0; //Variable entera que determina el ganador de la partida.
	bool carga = false; //Variable booleana que ser� "true" si el mazo ha cargado correctamente, false en caso contrario.


	inicializa(cartas); //Inicializa las cartas que quedan por aparecer.
	iniciar(mazo); iniciar(cartasJugador); iniciar(cartasMaquina); //Inicializa a "0" todos los arrays de cartas.

	if (DEPURAR == false) {
		crearMazo(mazo); //Crea un mazo de cartas de la baraja espa�ola.
		barajar(mazo);	//Mezcla de forma aleatoria el mazo anteriormente creado.
	}
	else {
		carga = cargarMazo(mazo); //Carga un mazo de cartas desde un archivo de texto.
		if (carga == true) {
			depurar(mazo, turno, cartasJugador); //Muestra la baraja de cartas cargada desde un archivo de texto.
		}
	}

	if (((!DEPURAR) && (!carga)) || ((DEPURAR) && (carga))) {
		cout << "--------------" << endl;
		cout << "TURNO JUGADOR" << endl;
		cout << "--------------" << endl;

		turno = PERSONA;
		puntosJugador = modoD(mazo, cartas, turno, puntosJugador, cartasJugador);
		cout << "Puntos Jugador: " << puntosJugador << endl << endl;

		if (puntosJugador <= 7.5) {
			cout << "--------------" << endl;
			cout << "TURNO MAQUINA" << endl;
			cout << "--------------" << endl;

			turno = MAQUINA;
			puntosMaquina = modoD(mazo, cartas, turno, puntosJugador, cartasMaquina);
			cout << "Puntos Maquina: " << puntosMaquina << endl << endl;
		}

		ganador = determinaGanador(puntosJugador, puntosMaquina, cartasJugador, cartasMaquina);
		if (ganador == 1) {
			cout << "GANA JUGADOR" << endl << endl;
		}
		else {
			cout << "GANA MAQUINA" << endl << endl;
		}
		numPartidas++;
		guardarResultado(numPartidas, ganador, puntosJugador, puntosMaquina, cartasJugador, cartasMaquina); //Guarda el resultado de la partida en un archivo de texto.
	}

	system("pause");
	system("cls");
}

double modoA(ifstream &mazo, int numCartas) {
	double puntos = 0; //Variable que representa los puntos que suman actualmente las cartas.
	int carta; //Variable entera que se igualar� a la siguiente carta del mazo.

	int i = 0;
	while (i < numCartas && puntos < 7.5) {
		mazo >> carta;

		if ((carta != 10) && (carta != 11) && (carta != 12)) {
			puntos += carta;
		}
		else {
			puntos += 0.5;
		}
		cout << "Carta: " << carta << setw(20) << setfill(char(0)) << "Puntos: " << puntos << endl;

		i++;
	}

	return puntos; //Devuelve los�puntos�obtenidos�tras�robar�ese n�mero�de�cartas,�obtener�7,5�o�pasarse.� 
}

double modoB(ifstream & mazo, int numCartas, int turno, double puntosContrario) {
	double puntos = 0; //Variable que representa los puntos que suman actualmente las cartas.
	int carta; //Variable entera que se igualar� a la siguiente carta del mazo.
	char continuar = 'y'; //Variable de tipo car�cter. Si se iguala a "Y/y", el JUGADOR seguir� robando carta. Si se iguala a "N/n", no seguir� robando. (MODO B).
	int i = 0;

	while (((continuar == 'y') || (continuar == 'Y')) && (i < numCartas)) {
		if (((turno == MAQUINA) && (puntos <= puntosContrario)) || ((turno == PERSONA) && (puntos < 7.5))) {
			mazo >> carta;

			if ((carta != 10) && (carta != 11) && (carta != 12)) {
				puntos += carta;
			}
			else {
				puntos += 0.5;
			}

			cout << "Carta: " << carta << setw(20) << setfill(char(0)) << "Puntos: " << puntos << endl;

			if ((turno == PERSONA) && (i < numCartas - 1) && (puntos < 7.5)) {
				cout << "Quiere continuar robando (Y/N): ";
				cin >> continuar;
			}
		}
		i++;
	}

	return puntos; //Devuelve�los�puntos�obtenidos�tras�robar�numCartas,�obtener�7,5,�pasarse�o�plantarse.� 
}

double modoC(ifstream& mazo, tCartasPorAparecer cartas, int turno, double puntosContrario) {
	double puntos = 0; //Variable que representa los puntos que suman actualmente las cartas.
	int carta = 0; //Variable entera que se igualar� a la siguiente carta del mazo.
	char continuar = 'y'; //Variable de tipo car�cter. Si se iguala a "Y/y", el JUGADOR seguir� robando carta. Si se iguala a "N/n", no seguir� robando.
	bool probabilidadPasarse = false; //Variable booleana que se iguala a la funci�n "esProbablePasarse()" para determinar si la m�quina roba o no otra carta.


	do {
		if ((turno == PERSONA) || ((turno == MAQUINA) && (puntos <= puntosContrario))) {
			carta = sacarCarta(mazo, puntos); //Saca la siguiente carta del archivo que contiene el mazo.
			restarCarta(cartas, carta); //Resta la carta de la lista de cartas restantes.

			if ((turno == MAQUINA) && (puntos == puntosContrario)) {
				probabilidadPasarse = esProbablePasarse(puntos, cartas); //Calcula la probabilidad que tiene la MAQUINA de pasarse si contin�a sandao cartas (devuelve true si es mayor del 50%).
			}
			else {
				if ((turno == MAQUINA) && (puntos > puntosContrario)) {
					probabilidadPasarse = true;
				}
			}
		}

		cout << "Carta: " << carta << setw(20) << setfill(char(0)) << "Puntos: " << puntos << endl;

		if ((turno == PERSONA) && (puntos < 7.5)) {
			cout << "Quiere continuar robando (Y/N): ";
			cin >> continuar;
		}
	} while (((continuar == 'y') || (continuar == 'Y')) && ((puntos < 7.5) && (probabilidadPasarse != true)));

	return puntos; //Devuelve los�puntos�obtenidos�y�actualiza�cartas�de�acuerdo�con�las�cartas�que�haya�robado�el jugador.�
}

double modoD(tConjuntoCartas& mazo, tCartasPorAparecer cartas, int turno, double puntosContrario, tConjuntoCartas& cartasJugador) {
	double puntos = 0; //Variable que representa los puntos que suman actualmente las cartas.
	int carta = 0; //Variable entera que se igualar� a la siguiente carta del mazo.
	char continuar = 'y'; //Variable de tipo car�cter. Si se iguala a "Y/y", el JUGADOR seguir� robando carta. Si se iguala a "N/n", no seguir� robando.
	bool probabilidadPasarse = false; //Variable booleana que se iguala a la funci�n "esProbablePasarse()" para determinar si la m�quina roba o no otra carta.


	do {
		if ((turno == PERSONA) || ((turno == MAQUINA) && (puntos <= puntosContrario))) {
			sacar(mazo, carta); //Extrae la siguiente carta del mazo.
			sumarPuntos(puntos, carta); //Suma los puntos de la carta extraida.
			incluir(cartasJugador, carta); //Incluye la carta sacada en el array correspondiente.
			restarCarta(cartas, carta); //Resta la carta de la lista de cartas restantes.

			if ((turno == MAQUINA) && (puntos == puntosContrario)) {
				probabilidadPasarse = esProbablePasarse(puntos, cartas); //Calcula la probabilidad que tiene la MAQUINA de pasarse si contin�a sandao cartas (devuelve true si es mayor del 50%).
			}
			else {
				if ((turno == MAQUINA) && (puntos > puntosContrario)) {
					probabilidadPasarse = true;
				}
			}
		}

		cout << "Carta: " << carta << setw(20) << setfill(char(0)) << "Puntos: " << puntos << endl;

		if (DEPURAR == true) {
			depurar(mazo, turno, cartasJugador);
		}

		if ((turno == PERSONA) && (puntos < 7.5)) {
			cout << "Quiere continuar robando (Y/N): ";
			cin >> continuar;
		}

	} while (((continuar == 'y') || (continuar == 'Y')) && ((puntos < 7.5) && (probabilidadPasarse != true)));

	return puntos; //Devuelve los�puntos�obtenidos�y�actualiza�cartas�de�acuerdo�con�las�cartas�que�haya�robado�el jugador.
}

int determinaGanador(double puntosJugador, double puntosMaquina) {
	int ganador = 0; //Variable entera que tomar� el valor del ganador.

	if ((puntosJugador == puntosMaquina)) {
		ganador = PERSONA + rand() % (MAQUINA);
	}
	else {
		if ((puntosMaquina > puntosJugador) && (puntosMaquina <= 7.5)) {
			ganador = MAQUINA;
		}
		else {
			if (puntosJugador > 7.5) {
				ganador = MAQUINA;
			}
			else {
				ganador = PERSONA;
			}
		}
	}

	return ganador; //Devuelve 1 en caso de que gane el Jugador, 2 en caso de que gane la m�quina.
}

int determinaGanador(double puntosJugador, double puntosMaquina, const tConjuntoCartas& cartasJugador, const tConjuntoCartas& cartasMaquina) {
	int ganador = 0; //Variable entera que tomar� el valor del ganador.

	if ((puntosJugador == puntosMaquina) && (cartasJugador.contador != cartasMaquina.contador)) {
		if (cartasJugador.contador > cartasMaquina.contador) {
			ganador = PERSONA;
		}
		if (cartasJugador.contador < cartasMaquina.contador) {
			ganador = MAQUINA;
		}
	}
	else {
		ganador = determinaGanador(puntosJugador, puntosMaquina);
	}

	return ganador; //Devuelve 1 en caso de que gane el Jugador, 2 en caso de que gane la m�quina.
}

int generarAleatorio() {

	int aleatorio = limiteInf + rand() % (limiteSup - limiteInf);

	return aleatorio; //Devuelve un n�mero aleatorio entre el rango [3-5].
}

bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas) {
	double probabilidad = 0; //Variable que almacena la probabilidad de pasarse.
	double cartasRestantes = 0; //Variable que almacena el n�mero de cartas restantes en el mazo.
	int cartasAptas = 7.5 - puntosMaquina + 1; //Variable que almacena hasta qu� valor de carta podr�a robar la m�quina sin pasarse.
	double cartasMayores = 0; //Variable que almacena el n�mero de cartas que quedan con valores que har�an que al robarlas, la m�quina se pasara.

	for (int i = 0; i < TIPOCARTAS; i++) {
		cartasRestantes += cartas[i];
		if (i >= cartasAptas) {
			cartasMayores += cartas[i];
		}
	}

	probabilidad = cartasMayores / cartasRestantes;

	return (probabilidad > 0.5) ? true : false; //Devuelve true si la probabilidad de pasarse es mayor que 0.5, false en caso contrario.
}

int sacarCarta(ifstream& mazo, double& puntos) {
	int carta = 0; //Variable entera que representa el valor de una carta.

	mazo >> carta;

	if ((carta != 10) && (carta != 11) && (carta != 12)) {
		puntos += carta;
	}
	else {
		puntos += 0.5;
	}

	return carta; //Devuelve la carta obtenida del mazo.
}

void restarCarta(tCartasPorAparecer cartas, const int carta) {

	if ((carta > 9) && (cartas[0] != 0)) {
		cartas[0] -= 1;
	}
	else {
		if (cartas[carta] != 0) {
			cartas[carta] -= 1;
		}
	}

}

void inicializa(tCartasPorAparecer& cartas) {

	cartas[0] = 12;
	for (int i = 1; i < TIPOCARTAS; i++) {
		cartas[i] = 4;
	}

}

void iniciar(tConjuntoCartas& cartas) {

	for (int i = 0; i < MAXCARTAS; i++){
		cartas.mazo[i] = 0;
	}
	cartas.contador = MAXCARTAS-1;

}

void sacar(tConjuntoCartas& cartas, int& carta) {
	carta = cartas.mazo[cartas.contador];	//Saca la siguiente carta.
	cartas.contador--;
}

void incluir(tConjuntoCartas& cartas, int carta) {
	cartas.mazo[cartas.contador] = carta;
	cartas.contador--;
}

void crearMazo(tConjuntoCartas& mazo) {
	int n = 1; //Variable entera que va representando en n�mero de la carta que se va a�adiendo a cada posici�n del array.

	int i = 0;
	while (i < MAXCARTAS) {
		if (n == 8) { n = 10; }	//Se salta los 8�s y 9�s, porque no existen en la baraja espa�ola.
		mazo.mazo[i] = n;
		mazo.mazo[i + 1] = n;
		mazo.mazo[i + 2] = n;
		mazo.mazo[i + 3] = n;
		n++;
		i = i + 4;
	}
	mazo.contador = MAXCARTAS - 1;
}

void barajar(tConjuntoCartas& mazo) {
	int indice1 = 0, indice2 = 0; //Variable entera que determina una posici�n de la baraja.
	int auxiliar = 0; //Variable entera auxiliar que servir� para no perder el contenido de diferentes posiciones del array.

	for (int i = 0; i < MAXCARTAS; i++) {
		indice1 = (rand() % MAXCARTAS); //Genera una posici�n aleatoria de la baraja.
		indice2 = (rand() % MAXCARTAS); //Genera otra posici�n aleatoria de la baraja.
		auxiliar = mazo.mazo[indice1]; //Guarda el contenido de la primera posici�n aleatoria en un auxiliar;
		mazo.mazo[indice1] = mazo.mazo[indice2]; //Mueve el contenido de la segunda posici�n del mazo generada aleatoriamente, a la primera posici�n generada aleatoriamente.
		mazo.mazo[indice2] = auxiliar; //Guarda lo que hab�a en la primera posici�n (ahora guardado en la variable auxiliar), en la segunda posici�n del mazo aleatoria.
	}
}

void sumarPuntos(double& puntos, int carta) {
	if ((carta != 10) && (carta != 11) && (carta != 12)) {
		puntos += carta;
	}
	else {
		puntos += 0.5;
	}
}

bool cargarMazo(tConjuntoCartas& mazo) {
	ifstream baraja; //Archivo que carga el mazo.
	bool carga = true; //Variable booleana que indica si el archivo ha cargado correctamente.
	string archivo; //Archivo a cargar. Se iguala al nombre del archivo, con extensi�n, introducido por el usuario.
	int auxiliar = 0; //Variable auxiliar que almacena temporalmente la carta que se va a incluir en la posici�n "i" del mazo.

	cout << "Introduzca el nombre del fichero: ";
	cin >> archivo;

	baraja.open(archivo);
	if (!baraja.is_open()) {
		cout << "No se ha encontrado el archivo." << endl;
		carga = false;
	}
	else {
		carga = true;
		for (int i = 0; i < MAXCARTAS; i++) {
			baraja >> mazo.mazo[i];
		}
		mazo.contador = MAXCARTAS - 1;
	}
	baraja.close();

	return carga; //Devuelve true en caso de carga correcta del archivo, false en caso contrario.
}

void guardarResultado(int& numPartidas, int ganador, double& puntosJugador, double& puntosMaquina, tConjuntoCartas& cartasJugador, tConjuntoCartas& cartasMaquina) {
	ofstream archivo; //Archivo que guarda el resultado.
	string nombreArchivo = "partida" + to_string(numPartidas) + ".txt"; //Nombre del archivo compuesto por "partida" + el n�mero de la partida.
	string winner;	//Cadena de caracteres que representa al ganador de la partida.
	int auxiliar = 0; //Variable entera auxiliar.
	int i = MAXCARTAS - 1;

	archivo.open(nombreArchivo);
	if (!archivo.is_open()) {
		cout << "Error al guardar resultados." << endl;
	}
	else {
		archivo << "Numero de partida: " << numPartidas << endl;
		if (ganador == 1) {
			winner = "HUMANO";
		}
		else {
			winner = "MAQUINA";
		}
		archivo << "GANADOR: " << winner << endl;
		archivo << "Humano. Puntuaci�n: " << puntosJugador << endl;
		archivo << "Cartas: ";
		do {
			auxiliar = cartasJugador.mazo[i];
			archivo << auxiliar << ", ";
			i--;
		} while (i > cartasJugador.contador);
		archivo  << endl << "Maquina. Puntuaci�n: " << puntosMaquina << endl;
		archivo << "Cartas: ";
		i = MAXCARTAS - 1;
		do {
			auxiliar = cartasMaquina.mazo[i];
			archivo << auxiliar << ", ";
			i--;
		} while (i > cartasMaquina.contador);
	}

	archivo.close();
}

void depurar(tConjuntoCartas& mazo, const int turno, tConjuntoCartas& cartasJugador) {
	string turn; //Variable. Cadena de caracteres que representa en turno.

	switch(turno){
		case 1: turn = "JUGADOR"; break;
		case 2: turn = "MAQUINA"; break;
		default: turn = ""; break;
	}

	cout << "\n" << setw(MAX_BARRAS) << setfill(char(205)) << "\n" << "Mazo: ";
	for (int i = 0; i <= mazo.contador; i++) {
		cout << mazo.mazo[i] << char(0);
	}
	if (turno != 0) {
		cout << endl << "Cartas extraidas " << turn << ": ";
		for (int i = cartasJugador.contador + 1; i < MAXCARTAS; i++) {
			cout << cartasJugador.mazo[i] << char(0);
		}
	}
	cout << "\n" << setw(MAX_BARRAS) << setfill(char(205)) << "\n";

}