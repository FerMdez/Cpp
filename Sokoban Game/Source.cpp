//Fernando Méndez //Sokoban Game

#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;

//Constantes:
const int MAX = 50;
const int MAXH = 12;
const int MAXE = 100;

//Tipos:
typedef enum tCasilla{ Libre, Muro, DestinoL, DestinoC, DestinoJ, Jugador, Caja };
typedef tCasilla tTablero[MAX][MAX];
typedef struct{
	tTablero tablero;
	int nfilas;
	int ncolumnas;
	int fila;
	int columna;
	int numCajas;
	int numCajasColocadas;
}tSokoban;
typedef struct{
	tSokoban tableros[MAXH];
	int cont;
}tHistoria;
typedef struct{
	tSokoban estado;
	int numMovimientos;
	string nFichero;
	int nivel;
	tHistoria historial;
}tJuego;
typedef enum tTecla{ Arriba, Abajo, Derecha, Izquierda, Salir, Nada, Deshacer };
typedef struct{
	string nombreFichero;
	int nivel;
	int contadorMovimientos;
}tPartida;
typedef tPartida tExitos[MAXE];
typedef struct{
	string nombre;
	tExitos exitos;
	int contadorGanadas;
}tInfo;

//Funciones:
void ejecutarMenu(tJuego &juego, tInfo &informacion); //Ejecuta la opcion del menú que ha elegido el usuario en la funcion menu().
int menu(); //Muestra el menú del programa con las opciones posibles. Devuelve la opción elegida por el usuario.
void jugar(tJuego &Juego, tInfo &informacion); //Una vez cargado el tablero, ejecuta el juego hasta que el jugador gane o pulse ESC. 
void colorFondo(int color); //Función para implementar los colores de las distintas casillas.
void dibujaCasilla(tCasilla casilla); //Muestra	una	casilla	del	tablero.
void dibujar(const tJuego &juego); //Muestra el  tablero del juego, el nombre del fichero desde que se ha cargado, su nivel y el número de movimientos realizados.
void inicializa(tJuego &juego); //Inicializa el tablero vacio y el numMovimientos a 0.
bool cargarJuego(tJuego &juego); //Solicita al usuario el nombre del archivo y el nivel que quiere jugar y carga ambos.
bool cargarNivel(ifstream &fichero, tJuego &juego, int nivel); //Busca el nivel en el fichero y ducuelve un booleano (true si lo ha encontrado, false en caso contrario).
void cargar(ifstream &fichero, tJuego &juego); //Una vez encontrado el nivel en el fichero, trasforma cada carácter de cada línea del nivel en un tipo tCasilla.
tTecla leerTecla(); //Devuelve el valor tTecla que el jugador ha introducido por teclado pulsando una de las fechas de dirección para moverse, ESC para salir o no devuelve nada si se ha pulsado otra tecla.
void hacerMovimiento(tJuego &juego, tTecla tecla); //Dado el movimiento del jugador, realiza ese movimiento o no hace nada si no se puede realizar dicho movimiento.
void movimientoArriba(tJuego &juego); //Realiza un movimiento hacia arriba.
void movimientoAbajo(tJuego &juego); //Realiza un movimiento hacia abajo.
void movimientoDerecha(tJuego &juego); //Realiza un movimiento hacia la derecha.
void movimientoIzquierda(tJuego &juego); //Realiza un movimiento hacia la izquierda.
void guardarHistorial(tJuego &juego); //Guarda en un array el tablero de cada movimiento anteriormente realizado.
bool bloqueado(const tJuego &juego); //Devuelve true si alguna de las cajas ha quedado atrapada en una esquina, false, mientras ninguna caja esté atrapada.
bool deshacerMovimiento(tJuego &juego); //Deshace el movimiento anterior, hasta un máximo de MAXH. Devuelve true si el movimiento se ha deshecho correctamente, false en caso contrario.
void cargarRanking(tInfo &informacion); //Dado un nombre de un jugador, carga el archivo con la información de sus anteriores partidas. En caso de no existir, creará un archivo nuevo.
void ordenar(tInfo &informacion); //Ordena la información de las partidas de un usuario, teniendo en cuenta el nombre de los archivos de las partidas y el nivel jugado. Además si un nivel ya se había jugado, sólo guarda la información en caso de haberlo superado en menos movimientos.
void mostar(tInfo &informacion); //Muesta las partidas jugadas por un usuario, clasificandolas en tres campos, nombre del fichero del tablero, nivel que se ha jugado y número de movimientos en los que se ha resuelto el tablero.
void guardar(tInfo &informacion); //Guarda en el archivo del jugador la información actualizada de las partidas jugadas una vez ganada una partida.
void nuevaPartida(tJuego &juego, tInfo &informacion); //Si el usuario gana una partida, esta función guarda en el array tInfo la información de la partida, para más tarde (y mediante las funciones ordenar y guardar) compararla, ordenarla y guardarla en el fichero del jugador.

int main(){
	tJuego juego;
	tInfo informacion;

	cargarRanking(informacion);
	ejecutarMenu(juego, informacion);

	return 0;
}

void ejecutarMenu(tJuego &juego, tInfo &informacion){
	int opcion = 1; //Entero que representa la opción escogida por el jugador.
	bool carga = false; //Booleano que se iguala a la función cargarJuego(juego) para comprobar si se ha cargado el fichero del nivel (true) o no (false).

	system("cls");
	while (opcion != 0){
		opcion = menu();
		switch (opcion){
		case 1: inicializa(juego); carga = cargarJuego(juego); if (carga == true){ jugar(juego, informacion); } break;
		case 2: mostar(informacion); break;
		case 0: guardar(informacion); break;
		}
	}
}

int menu(){
	//Parámetros: no tiene.
	//Devuelve: la opción del menú elegida por el usuario.

	int opc = 1;

	cout << "<--------------Menu-------------->" << endl;
	cout << " 1-Jugar partida." << endl;
	cout << " 2-Mostrar partidas ganadas." << endl;
	cout << " 0-Salir" << endl;
	cout << "<-------------------------------->" << endl;
	cout << endl;

	cout << "Seleccione una opcion del menu: ";
	cin >> opc;
	while (opc < 0 || opc > 2){
		cout << "Seleccione una opcion del menu (entre 0 y 2): ";
		cin >> opc;
	}
	return opc;
}

void jugar(tJuego &juego, tInfo &informacion){
	bool ganado = false; //Variable booleana que se iguala a true en caso de que el jugador haya completado un tablero para salir del bucle del juego y volver al menú.
	tTecla tecla = Nada; //Tecla pulsada por el jugador que se lee mediante la función leerTecla().
	bool estaBloqueado = false; //Variable booleana que se iguala a la funció bloqueado(juego) para que en caso de que haya una caja bloqueada se ponga a true y avise al jugador.

	while ((tecla != Salir) && (ganado == false)){
		if (juego.estado.numCajasColocadas != juego.estado.numCajas){
			estaBloqueado = bloqueado(juego);
			if (estaBloqueado == true){
				dibujar(juego);
				cout << "Te has quedado bloqueado. Pulsa D/d para deshacer movimiento." << endl;
				tecla = leerTecla();
				hacerMovimiento(juego, tecla);
			}
			else{
				dibujar(juego);
				tecla = leerTecla();
				hacerMovimiento(juego, tecla);
			}
		}
		if (juego.estado.numCajasColocadas == juego.estado.numCajas){
			dibujar(juego);
			cout << "Enhorabuena, has ganado." << endl;
			nuevaPartida(juego, informacion);
			ordenar(informacion);
			ganado = true;
			system("PAUSE");
		}
	}
	system("cls");
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void dibujaCasilla(tCasilla casilla){
	int color = 0; //Variable entera que representa el color de fondo correspondiente a cada casilla.

	switch (casilla){
	case Libre: color = 1; break;
	case Muro: color = 2; break;
	case DestinoL: color = 12; break;
	case DestinoC: color = 4; break;
	case DestinoJ: color = 4; break;
	case Jugador: color = 6; break;
	case Caja: color = 8; break;
	default: color = 0;
	}

	colorFondo(color);
}

void dibujar(const tJuego &juego){

	system("cls");
	cout << "Fichero: " << juego.nFichero << "  Nivel: " << juego.nivel << endl;
	
	for (int i = 0; i < juego.estado.nfilas; i++){
		cout << endl;
		for (int j = 0; j <= juego.estado.ncolumnas; j++){
			dibujaCasilla(juego.estado.tablero[i][j]);
			if (juego.estado.tablero[i][j] == Libre){
				cout << char(0) << char(0);
			}
			if (juego.estado.tablero[i][j] == Muro){
				cout << char(176) << char(176);
			}
			if (juego.estado.tablero[i][j] == DestinoL){
				cout << char(46) << char(46);
			}
			if (juego.estado.tablero[i][j] == DestinoC){
				cout << char(91) << char(93);
			}
			if (juego.estado.tablero[i][j] == DestinoJ){
				cout << char(48) << char(48);
			}
			if (juego.estado.tablero[i][j] == Jugador){
				cout << char(48) << char(48);
			}
			if (juego.estado.tablero[i][j] == Caja){
				cout << char(40) << char(41);
			}
		}
	}
	cout << endl << endl;
	colorFondo(0);

	cout << "Numero de movimientos: " << juego.numMovimientos << endl;
}

void inicializa(tJuego &juego){
	juego.numMovimientos = 0;
	juego.nivel = 0;
	juego.estado.nfilas = 0;
	juego.estado.ncolumnas = 0;
	juego.estado.numCajas = 0;
	juego.estado.numCajasColocadas = 0;
	juego.estado.fila = 0;
	juego.estado.columna = 0;
	juego.historial.cont = 0;

	for (int i = 0; i < MAX; i++){
		for (int j = 0; j < MAX; j++){
			juego.estado.tablero[i][j] = Libre;
		}
	}
	
}

bool cargarJuego(tJuego &juego){
	bool carga = true; //Variable booleana que se iguala a la función cargarNivel(fichero, juego, nivel), para ponerse a true en caso de que de que el fichero se haya cargado correctamente. En caso de que no se haya encontrado el archivo, se iguala directamente a false.
	string archivo; //Archivo a cargar. Se iguala al nombre del archivo, con extensión, introducido por el usuario.
	int nivel = 0; //Nivel a cargar del archivo, seleccionado por el jugador.
	
	cout << "Introduzca el nombre del fichero: ";
	cin >> juego.nFichero;
	archivo = juego.nFichero;

	ifstream fichero;
	fichero.open(archivo);
	if (!fichero.is_open()){
		cout << "No se ha encontrado el archivo." << endl;
		system("PAUSE");
		system("cls");
		carga = false;
	}
	else{
		cout << "Introduzca el nivel que quiere jugar: ";
		cin >> juego.nivel;
		nivel = juego.nivel;
		carga = cargarNivel(fichero, juego, nivel);
		if (carga == false){
			cout << "Error, no se ha encontrado el nivel." << endl;
			system("PAUSE");
			system("cls");
		}
	}
	fichero.close();

	return carga; //Devuelve true en caso de carga correcta del archivo, false en caso contrario.
}

bool cargarNivel(ifstream &fichero, tJuego &juego, int nivel){
	string linea; //Cadena de caracteres que se carga al leer cada una de las líneas del nivel a cargar.
	string miNivel = "Level " + to_string(nivel); // Cadena de caracteres que sirve para leer y encontrar el nivel seleccionado por el jugador. Se compone de la palabra "Level" + el nivl elegido por el usuario.
	bool cargarNivel = false; //Variable booleana que devuelve la función.


	getline(fichero, linea);
	while ((linea != miNivel) && (!fichero.eof())){
		getline(fichero, linea);
	}
	if (fichero.eof()){
		cargarNivel = false;
	}
	else{
		cargar(fichero, juego);
		cargarNivel = true;
	}

	return cargarNivel; //Devuelve true en caso de que se haya encontrado el nivel, false en caso de que haya llegado al final del archivo sin encontrarlo.
}

void cargar(ifstream &fichero, tJuego &juego){
	tCasilla casilla = Caja; //Representa cada uno de las posibles casillas del tablero.
	int contadorC = 0; //Contador de las columnas del nivel cargado.
	int contadorF = 0; //Contador de las filas del nivel cargado.
	char tipo; //Cada uno de los caracteres que se lee del archivo y luego se iguala a su correspondiente casilla.
	string linea; //Cadena de caracteres que se lee del archivo.

	getline(fichero, linea);
	while ((!fichero.eof()) && (linea != "")){
		for (int i = 0; i < linea.length(); i++){
			tipo = linea[i];
			switch (tipo){
			case '#': juego.estado.tablero[contadorF][i] = Muro; break;
			case '.': juego.estado.tablero[contadorF][i] = DestinoL; break;
			case '*': juego.estado.tablero[contadorF][i] = DestinoC; juego.estado.numCajas++; juego.estado.numCajasColocadas++; break;
			case '+': juego.estado.tablero[contadorF][i] = DestinoJ; juego.estado.fila = contadorF; juego.estado.columna = i; break;
			case '@': juego.estado.tablero[contadorF][i] = Jugador; juego.estado.fila = contadorF; juego.estado.columna = i; break;
			case '$': juego.estado.tablero[contadorF][i] = Caja; juego.estado.numCajas++; break;
			case ' ': juego.estado.tablero[contadorF][i] = Libre; break;
			default: juego.estado.tablero[contadorF][i] = Libre;
			}
			if (i > contadorC){
				contadorC = i;
			}
		}
			contadorF++;
			getline(fichero, linea);
	}

	juego.estado.nfilas = contadorF;
	juego.estado.ncolumnas = contadorC;
}

tTecla leerTecla(){
	tTecla tecla = Nada; //Tecla pulsada por el usuario.
	int dir = 27; //Variable entera que representa el número de la tecla pulsada por el jugador.

	cin.sync();
	dir = _getch();
	if (dir == 0xe0){
		dir = _getch();
		switch (dir){
		case 72: tecla = Arriba; break;
		case 80: tecla = Abajo; break;
		case 77: tecla = Derecha; break;
		case 75: tecla = Izquierda; break;
		}
	} 
	else{
		switch (dir){
		case 27: tecla = Salir; break;
		case 68: tecla = Deshacer; break;
		case 100: tecla = Deshacer; break;
		}
	}

	return tecla; //Devuelve el tipo tTecla con la tecla pulsada.
}

void hacerMovimiento(tJuego &juego, tTecla tecla){

	switch (tecla){
	case Arriba: movimientoArriba(juego); break;
	case Abajo: movimientoAbajo(juego); break;
	case Derecha: movimientoDerecha(juego); break;
	case Izquierda: movimientoIzquierda(juego); break;
	case Salir: break;
	case Nada: break;
	case Deshacer: deshacerMovimiento(juego); break;
	}
	guardarHistorial(juego);
}

void guardarHistorial(tJuego &juego){
	int contador = juego.historial.cont; //Contador del número de tableros guardados hasta el momento.

	if (contador < MAXH){
		juego.historial.tableros[contador].fila = juego.estado.fila;
		juego.historial.tableros[contador].columna = juego.estado.columna;
		juego.historial.tableros[contador].nfilas = juego.estado.nfilas;
		juego.historial.tableros[contador].ncolumnas = juego.estado.ncolumnas;
		juego.historial.tableros[contador].numCajas = juego.estado.numCajas;
		juego.historial.tableros[contador].numCajasColocadas = juego.estado.numCajasColocadas;

		for (int i = 0; i <= juego.historial.tableros[contador].nfilas; i++){
			for (int j = 0; j <= juego.historial.tableros[contador].ncolumnas; j++){
				juego.historial.tableros[contador].tablero[i][j] = juego.estado.tablero[i][j];
			}
		}
	}
	else{
		contador = MAXH - 1;

		juego.historial.tableros[contador].fila = juego.estado.fila;
		juego.historial.tableros[contador].columna = juego.estado.columna;
		juego.historial.tableros[contador].nfilas = juego.estado.nfilas;
		juego.historial.tableros[contador].ncolumnas = juego.estado.ncolumnas;
		juego.historial.tableros[contador].numCajas = juego.estado.numCajas;
		juego.historial.tableros[contador].numCajasColocadas = juego.estado.numCajasColocadas;

		for (int i = 0; i <= juego.historial.tableros[contador].nfilas; i++){
			for (int j = 0; j <= juego.historial.tableros[contador].ncolumnas; j++){
				juego.historial.tableros[contador].tablero[i][j] = juego.estado.tablero[i][j];
			}
		}

		for (int x = 0; x < contador; x++){
			juego.historial.tableros[x].fila = juego.historial.tableros[x + 1].fila;
			juego.historial.tableros[x].columna = juego.historial.tableros[x + 1].columna;
			juego.historial.tableros[x].nfilas = juego.historial.tableros[x + 1].nfilas;
			juego.historial.tableros[x].ncolumnas = juego.historial.tableros[x + 1].ncolumnas;
			juego.historial.tableros[x].numCajas = juego.historial.tableros[x + 1].numCajas;
			juego.historial.tableros[x].numCajasColocadas = juego.historial.tableros[x + 1].numCajasColocadas;

			for (int i = 0; i <= juego.historial.tableros[contador].nfilas; i++){
				for (int j = 0; j <= juego.historial.tableros[contador].ncolumnas; j++){
					juego.historial.tableros[x].tablero[i][j] = juego.historial.tableros[x + 1].tablero[i][j];
				}
			}
		}
	
		juego.historial.cont = contador;
	}
}

bool bloqueado(const tJuego &juego){
	bool estaBloqueada = false; //Variable booleana que representa si una caja está bloqueada entre dos muros.

		for (int i = 0; i < juego.estado.nfilas; i++){
			for (int j = 0; j <= juego.estado.ncolumnas; j++){
				if (juego.estado.tablero[i][j] == Caja){
					if ((juego.estado.tablero[i + 1][j] == Muro && juego.estado.tablero[i][j + 1] == Muro) || (juego.estado.tablero[i - 1][j] == Muro && juego.estado.tablero[i][j + 1] == Muro) || (juego.estado.tablero[i - 1][j] == Muro && juego.estado.tablero[i][j - 1] == Muro) || (juego.estado.tablero[i + 1][j] == Muro && juego.estado.tablero[i][j - 1] == Muro)){
						estaBloqueada = true;
					}
				}
			}
		}

	return estaBloqueada; //Devuelve true si una caja está bloqueada, false en caso contrario.
}

bool deshacerMovimiento(tJuego &juego){
	bool desMov = false; //Variable booleana que representa si un movimiento se ha deshecho correctamente.
	int contador = juego.historial.cont - 1; //Entero que representa el número de tableros guardados hasta el momento.
	
	if (contador > 0){
		juego.estado.fila = juego.historial.tableros[contador].fila;
		juego.estado.columna = juego.historial.tableros[contador].columna;
		juego.estado.nfilas = juego.historial.tableros[contador].nfilas;
		juego.estado.ncolumnas = juego.historial.tableros[contador].ncolumnas;
		juego.estado.numCajas = juego.historial.tableros[contador].numCajas;
		juego.estado.numCajasColocadas = juego.historial.tableros[contador].numCajasColocadas;
		juego.numMovimientos--;

		for (int i = 0; i <= juego.estado.nfilas; i++){
			for (int j = 0; j <= juego.estado.ncolumnas; j++){
				juego.estado.tablero[i][j] = juego.historial.tableros[contador].tablero[i][j];
			}
		}

		desMov = true;
		juego.historial.cont--;
	}
	else{
		desMov = false;
	}

	return desMov; //Devuelve true si el movimiento se ha deshecho correctamente, false en caso contrario.
}

void cargarRanking(tInfo &informacion){
	string nombre; //Nombre el usuario,
	string nomFichero; //Nombre del fichero que se le asigna al usuario en base a su nombre.
	int lvl; //Entero que se lee del archivo y representa el o los niveles que ha superado el usuario con anterioridad.
	int movimientos; //Entero que se lee del archivo representa el número de movimientos que ha empleado el usuario en resolver un nivel. 
	int contador = 0; //Contador que va aumentado según el número de tableros que haya resuelto el usuario anteriormente.

	cout << "Introduzca su nombre: ";
	cin >> nombre;
	informacion.nombre = nombre;
	string miArchivo = nombre + ".txt";

	ifstream archivo;
	archivo.open(miArchivo);
	if (!archivo.is_open()){
		ofstream fichero;
		fichero.open(miArchivo);
		nomFichero = "XXX";
		fichero << nomFichero;
		cout << "No se encuentra la informacion del jugador. Se ha creado una nueva." << endl;
		system("PAUSE");
		fichero.close();
	}
	else{
		while ((contador < MAXE) && (nomFichero != "XXX")){
			archivo >> nomFichero;
			informacion.exitos[contador].nombreFichero = nomFichero;
			archivo >> lvl;
			informacion.exitos[contador].nivel = lvl;
			archivo >> movimientos;
			informacion.exitos[contador].contadorMovimientos = movimientos;

			contador++;
		}

		informacion.contadorGanadas = contador - 1;
		cout << "Bienvenido " << informacion.nombre << endl;
		system("PAUSE");
	}
	archivo.close();
}

void ordenar(tInfo &informacion){
	int pos = informacion.contadorGanadas - 1; //Entero que representa la posición en la que se encuentra la información de un tablero resuelto cargado del archivo con respecto a los demás tableros resueltos.
	int tmp; //Entero auxiliar.
	string aux; //Cadena de caracteres auxiliar.

	while (pos > 0){
		if ((informacion.exitos[pos].nombreFichero == informacion.exitos[pos - 1].nombreFichero) && (informacion.exitos[pos].nivel == informacion.exitos[pos - 1].nivel)){
			if (informacion.exitos[pos].contadorMovimientos < informacion.exitos[pos - 1].contadorMovimientos){
				informacion.exitos[pos - 1].nombreFichero = informacion.exitos[pos].nombreFichero;
				informacion.exitos[pos - 1].nivel = informacion.exitos[pos].nivel;
				informacion.exitos[pos - 1].contadorMovimientos = informacion.exitos[pos].contadorMovimientos;
			}
				for (int i = pos; i < informacion.contadorGanadas - 1; i++){
					informacion.exitos[i].nombreFichero = informacion.exitos[i + 1].nombreFichero;
					informacion.exitos[i].nivel = informacion.exitos[i + 1].nivel;
					informacion.exitos[i].contadorMovimientos = informacion.exitos[i + 1].contadorMovimientos;
				}
				informacion.contadorGanadas--;
		}

		if ((informacion.exitos[pos].nombreFichero < informacion.exitos[pos - 1].nombreFichero) || ((informacion.exitos[pos].nombreFichero == informacion.exitos[pos - 1].nombreFichero) && (informacion.exitos[pos].nivel < informacion.exitos[pos - 1].nivel))){
			aux = informacion.exitos[pos].nombreFichero;
			informacion.exitos[pos].nombreFichero = informacion.exitos[pos - 1].nombreFichero;
			informacion.exitos[pos - 1].nombreFichero = aux;

			tmp = informacion.exitos[pos].nivel;
			informacion.exitos[pos].nivel = informacion.exitos[pos - 1].nivel;
			informacion.exitos[pos - 1].nivel = tmp;

			tmp = informacion.exitos[pos].contadorMovimientos;
			informacion.exitos[pos].contadorMovimientos = informacion.exitos[pos - 1].contadorMovimientos;
			informacion.exitos[pos - 1].contadorMovimientos = tmp;
		}
		pos--;
	}
}

void mostar(tInfo &informacion){
	int i = 0; //Variable entera que lleva la cuenta del número de tableros resueltos mostrados, no puede ser mayor que la variable 'contador'.
	int contador = informacion.contadorGanadas; //Variable entera que representa el número de tableros resueltos que se han leido del archivo personal del usuario.

	system("cls");
	cout << "Tableros resueltos por " << informacion.nombre << endl << endl;
	cout << "NOMBRE FICHERO" << setw(10) << "NIVEL" << setw(20) << "MOVIMIENTOS" << endl;
	cout << "--------------------------------------------------" << endl;
	while (i < contador){
		cout << informacion.exitos[i].nombreFichero << setw(10) << informacion.exitos[i].nivel << setw(18) << informacion.exitos[i].contadorMovimientos << endl;
		i++;
	}
	cout << "--------------------------------------------------" << endl << endl;
	system("PAUSE");
	system("cls");
}

void guardar(tInfo &informacion){
	int contador = informacion.contadorGanadas; //Variable entera que representa el número de tableros resueltos que se han leido del archivo personal del usuario.
	string nomFichero; //Nombre del fichero del jugador.
	int lvl; //Entero que se lee del archivo y representa el o los niveles que ha superado el usuario con anterioridad.
	int numMov; //Entero que se lee del archivo representa el número de movimientos que ha empleado el usuario en resolver un nivel. 
	string miArchivo = informacion.nombre + ".txt"; //Nombre del jugador más extensión que representa el archivo del usuario que ha iniciado sesión.

	ofstream archivo;
	archivo.open(miArchivo);
	if (archivo.is_open()){
		for (int i = 0; i < contador; i++){
			nomFichero = informacion.exitos[i].nombreFichero;
			archivo << nomFichero << " ";

			lvl = informacion.exitos[i].nivel;
			archivo << lvl << " ";

			numMov = informacion.exitos[i].contadorMovimientos;
			archivo << numMov << endl;
		}
		archivo << "XXX";
	}
	archivo.close();
}

void nuevaPartida(tJuego &juego, tInfo &informacion){
	int contador = informacion.contadorGanadas; //Variable entera que representa el número de tableros resueltos que se han leido del archivo personal del usuario.
	
	informacion.exitos[contador].nombreFichero = juego.nFichero;
	informacion.exitos[contador].nivel = juego.nivel;
	informacion.exitos[contador].contadorMovimientos = juego.numMovimientos;

	informacion.contadorGanadas++;

}

//Las funciones de los movimientos son provisionales, no sólo se pueden optimizar, si no que se pueden juntar en una función.

void movimientoArriba(tJuego &juego){
	int f = juego.estado.fila; //Fila en la que se encuentra el jugador.
	int c = juego.estado.columna; //Columna en la que se encuentra el jugador.

	if (juego.estado.tablero[f][c] == DestinoJ){
		if (juego.estado.tablero[f - 1][c] == Libre){
			juego.estado.tablero[f - 1][c] = Jugador;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.fila = juego.estado.fila - 1;
		}
		if ((juego.estado.tablero[f - 1][c] == Caja) && (juego.estado.tablero[f - 2][c] == DestinoL)){
			juego.estado.tablero[f - 2][c] = DestinoC;
			juego.estado.tablero[f - 1][c] = Jugador;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.fila = juego.estado.fila - 1;
			juego.estado.numCajasColocadas++;
		}
		if ((juego.estado.tablero[f - 1][c] == Caja) && (juego.estado.tablero[f - 2][c] != Muro)){
			if (juego.estado.tablero[f - 2][c] == DestinoL){
				juego.estado.tablero[f - 2][c] = DestinoC;
				juego.estado.tablero[f - 1][c] = Jugador;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.fila = juego.estado.fila - 1;
				juego.estado.numCajasColocadas++;
			}
			if (juego.estado.tablero[f - 2][c] == Libre){
				juego.estado.tablero[f - 2][c] = Caja;
				juego.estado.tablero[f - 1][c] = Jugador;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.fila = juego.estado.fila - 1;
			}
		}
		if (juego.estado.tablero[f - 1][c] == DestinoL){
			juego.estado.tablero[f - 1][c] = DestinoJ;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.fila = juego.estado.fila - 1;
		}
		if ((juego.estado.tablero[f - 1][c] == DestinoC) && (juego.estado.tablero[f - 2][c] != Muro) && (juego.estado.tablero[f - 2][c] != Caja)){
			if (juego.estado.tablero[f - 2][c] == DestinoL){
				juego.estado.tablero[f - 2][c] = DestinoC;
				juego.estado.tablero[f - 1][c] = DestinoJ;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.fila = juego.estado.fila - 1;
			}
			if (juego.estado.tablero[f - 2][c] == Libre){
				juego.estado.tablero[f - 2][c] = Caja;
				juego.estado.tablero[f - 1][c] = DestinoJ;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.fila = juego.estado.fila - 1;
				juego.estado.numCajasColocadas--;
			}
		}
		juego.numMovimientos++;
		juego.historial.cont++;
	}

	if (juego.estado.tablero[f][c] == Jugador){
		if (juego.estado.tablero[f - 1][c] == Libre){
			juego.estado.tablero[f - 1][c] = Jugador;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.fila = juego.estado.fila - 1;
		}
		if ((juego.estado.tablero[f - 1][c] == Caja) && (juego.estado.tablero[f - 2][c] == DestinoL)){
			juego.estado.tablero[f - 2][c] = DestinoC;
			juego.estado.tablero[f - 1][c] = Jugador;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.fila = juego.estado.fila - 1;
			juego.estado.numCajasColocadas++;
		}
		if ((juego.estado.tablero[f - 1][c] == Caja) && (juego.estado.tablero[f - 2][c] != Muro)){
			if (juego.estado.tablero[f - 2][c] == DestinoL){
				juego.estado.tablero[f - 2][c] = DestinoC;
				juego.estado.tablero[f - 1][c] = Jugador;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.fila = juego.estado.fila - 1;
				juego.estado.numCajasColocadas++;
			}
			if (juego.estado.tablero[f - 2][c] == Libre){
				juego.estado.tablero[f - 2][c] = Caja;
				juego.estado.tablero[f - 1][c] = Jugador;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.fila = juego.estado.fila - 1;
			}
		}
		if (juego.estado.tablero[f - 1][c] == DestinoL){
			juego.estado.tablero[f - 1][c] = DestinoJ;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.fila = juego.estado.fila - 1;
		}
		if ((juego.estado.tablero[f - 1][c] == DestinoC) && (juego.estado.tablero[f - 2][c] != Muro) && (juego.estado.tablero[f - 2][c] != Caja)){
			if (juego.estado.tablero[f - 2][c] == DestinoL){
				juego.estado.tablero[f - 2][c] = DestinoC;
				juego.estado.tablero[f - 1][c] = DestinoJ;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.fila = juego.estado.fila - 1;
			}
			if (juego.estado.tablero[f - 2][c] == Libre){
				juego.estado.tablero[f - 2][c] = Caja;
				juego.estado.tablero[f - 1][c] = DestinoJ;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.fila = juego.estado.fila - 1;
				juego.estado.numCajasColocadas--;
			}
		}
		juego.numMovimientos++;
		juego.historial.cont++;
	}
}

void  movimientoAbajo(tJuego &juego){
	int f = juego.estado.fila; //Fila en la que se encuentra el jugador.
	int c = juego.estado.columna; //columna en la que se encuentra el jugador.

	if (juego.estado.tablero[f][c] == DestinoJ){
		if (juego.estado.tablero[f + 1][c] == Libre){
			juego.estado.tablero[f + 1][c] = Jugador;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.fila = juego.estado.fila + 1;
		}
		if ((juego.estado.tablero[f + 1][c] == Caja) && (juego.estado.tablero[f + 2][c] != Muro)){
			if (juego.estado.tablero[f + 2][c] == DestinoL){
				juego.estado.tablero[f + 2][c] = DestinoC;
				juego.estado.tablero[f + 1][c] = Jugador;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.fila = juego.estado.fila + 1;
				juego.estado.numCajasColocadas++;
			}
			if (juego.estado.tablero[f + 2][c] == Libre){
				juego.estado.tablero[f + 2][c] = Caja;
				juego.estado.tablero[f + 1][c] = Jugador;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.fila = juego.estado.fila + 1;
			}
		}
		if (juego.estado.tablero[f + 1][c] == DestinoL){
			juego.estado.tablero[f + 1][c] = DestinoJ;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.fila = juego.estado.fila + 1;
		}
		if ((juego.estado.tablero[f + 1][c] == DestinoC) && (juego.estado.tablero[f + 2][c] != Muro) && (juego.estado.tablero[f + 2][c] != Caja)){
			if (juego.estado.tablero[f + 2][c] == DestinoL){
				juego.estado.tablero[f + 2][c] = DestinoC;
				juego.estado.tablero[f + 1][c] = DestinoJ;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.fila = juego.estado.fila + 1;
			}
			if (juego.estado.tablero[f + 2][c] == Libre){
				juego.estado.tablero[f + 2][c] = Caja;
				juego.estado.tablero[f + 1][c] = DestinoJ;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.fila = juego.estado.fila + 1;
				juego.estado.numCajasColocadas--;
			}
		}
		juego.numMovimientos++;
		juego.historial.cont++;
	}

	if (juego.estado.tablero[f][c] == Jugador){
		if (juego.estado.tablero[f + 1][c] == Libre){
			juego.estado.tablero[f + 1][c] = Jugador;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.fila = juego.estado.fila + 1;
		}
		if ((juego.estado.tablero[f + 1][c] == Caja) && (juego.estado.tablero[f + 2][c] != Muro)){
			if (juego.estado.tablero[f + 2][c] == DestinoL){
				juego.estado.tablero[f + 2][c] = DestinoC;
				juego.estado.tablero[f + 1][c] = Jugador;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.fila = juego.estado.fila + 1;
				juego.estado.numCajasColocadas++;
			}
			if (juego.estado.tablero[f + 2][c] == Libre){
				juego.estado.tablero[f + 2][c] = Caja;
				juego.estado.tablero[f + 1][c] = Jugador;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.fila = juego.estado.fila + 1;
			}
		}
		if (juego.estado.tablero[f + 1][c] == DestinoL){
			juego.estado.tablero[f + 1][c] = DestinoJ;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.fila = juego.estado.fila + 1;
		}
		if ((juego.estado.tablero[f + 1][c] == DestinoC) && (juego.estado.tablero[f + 2][c] != Muro) && (juego.estado.tablero[f + 2][c] != Caja)){
			if (juego.estado.tablero[f + 2][c] == DestinoL){
				juego.estado.tablero[f + 2][c] = DestinoC;
				juego.estado.tablero[f + 1][c] = DestinoJ;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.fila = juego.estado.fila + 1;
			}
			if (juego.estado.tablero[f + 2][c] == Libre){
				juego.estado.tablero[f + 2][c] = Caja;
				juego.estado.tablero[f + 1][c] = DestinoJ;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.fila = juego.estado.fila + 1;
				juego.estado.numCajasColocadas--;
			}
		}
		juego.numMovimientos++;
		juego.historial.cont++;
	}
}

void movimientoDerecha(tJuego &juego){
	int f = juego.estado.fila; //Fila en la que se encuentra el jugador.
	int c = juego.estado.columna; //Columna en la que se encuentra el jugador.

	if (juego.estado.tablero[f][c] == DestinoJ){
		if (juego.estado.tablero[f][c + 1] == Libre){
			juego.estado.tablero[f][c + 1] = Jugador;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.columna = juego.estado.columna + 1;
		}
		if ((juego.estado.tablero[f][c + 1] == Caja) && (juego.estado.tablero[f][c + 2] != Muro)){
			if (juego.estado.tablero[f][c + 2] == DestinoL){
				juego.estado.tablero[f][c + 2] = DestinoC;
				juego.estado.tablero[f][c + 1] = Jugador;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.columna = juego.estado.columna + 1;
				juego.estado.numCajasColocadas++;
			}
			if (juego.estado.tablero[f][c + 2] == Libre){
				juego.estado.tablero[f][c + 2] = Caja;
				juego.estado.tablero[f][c + 1] = Jugador;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.columna = juego.estado.columna + 1;
			}
		}
		if (juego.estado.tablero[f][c + 1] == DestinoL){
			juego.estado.tablero[f][c + 1] = DestinoJ;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.columna = juego.estado.columna + 1;
		}
		if ((juego.estado.tablero[f][c + 1] == DestinoC) && (juego.estado.tablero[f][c + 2] != Muro) && (juego.estado.tablero[f][c + 2] != Caja)){
			if (juego.estado.tablero[f][c + 2] == DestinoL){
				juego.estado.tablero[f][c + 2] = DestinoC;
				juego.estado.tablero[f][c + 1] = DestinoJ;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.columna = juego.estado.columna + 1;
			}
			if (juego.estado.tablero[f][c + 2] == Libre){
				juego.estado.tablero[f][c + 2] = Caja;
				juego.estado.tablero[f][c + 1] = DestinoJ;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.columna = juego.estado.columna + 1;
				juego.estado.numCajasColocadas--;
			}
		}
		juego.numMovimientos++;
		juego.historial.cont++;
	}

	if (juego.estado.tablero[f][c] == Jugador){
		if (juego.estado.tablero[f][c + 1] == Libre){
			juego.estado.tablero[f][c + 1] = Jugador;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.columna = juego.estado.columna + 1;
		}
		if ((juego.estado.tablero[f][c + 1] == Caja) && (juego.estado.tablero[f][c + 2] != Muro)){
			if (juego.estado.tablero[f][c + 2] == DestinoL){
				juego.estado.tablero[f][c + 2] = DestinoC;
				juego.estado.tablero[f][c + 1] = Jugador;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.columna = juego.estado.columna + 1;
				juego.estado.numCajasColocadas++;
			}
			if (juego.estado.tablero[f][c + 2] == Libre){
				juego.estado.tablero[f][c + 2] = Caja;
				juego.estado.tablero[f][c + 1] = Jugador;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.columna = juego.estado.columna + 1;
			}
		}
		if (juego.estado.tablero[f][c + 1] == DestinoL){
			juego.estado.tablero[f][c + 1] = DestinoJ;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.columna = juego.estado.columna + 1;
		}
		if ((juego.estado.tablero[f][c + 1] == DestinoC) && (juego.estado.tablero[f][c + 2] != Muro) && (juego.estado.tablero[f][c + 2] != Caja)){
			if (juego.estado.tablero[f][c + 2] == DestinoL){
				juego.estado.tablero[f][c + 2] = DestinoC;
				juego.estado.tablero[f][c + 1] = DestinoJ;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.columna = juego.estado.columna + 1;
			}
			if (juego.estado.tablero[f][c + 2] == Libre){
				juego.estado.tablero[f][c + 2] = Caja;
				juego.estado.tablero[f][c + 1] = DestinoJ;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.columna = juego.estado.columna + 1;
				juego.estado.numCajasColocadas--;
			}
		}
		juego.numMovimientos++;
		juego.historial.cont++;
	}
}

void movimientoIzquierda(tJuego &juego){
	int f = juego.estado.fila; //Fila en la que se encuentra el jugador.
	int c = juego.estado.columna; //Columnaa en la que se encuentra el jugador.

	if (juego.estado.tablero[f][c] == DestinoJ){
		if (juego.estado.tablero[f][c - 1] == Libre){
			juego.estado.tablero[f][c - 1] = Jugador;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.columna = juego.estado.columna - 1;
		}
		if ((juego.estado.tablero[f][c - 1] == Caja) && (juego.estado.tablero[f][c - 2] != Muro)){
			if (juego.estado.tablero[f][c - 2] == DestinoL){
				juego.estado.tablero[f][c - 2] = DestinoC;
				juego.estado.tablero[f][c - 1] = Jugador;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.columna = juego.estado.columna - 1;
				juego.estado.numCajasColocadas++;
			}
			if (juego.estado.tablero[f][c - 2] == Libre){
				juego.estado.tablero[f][c - 2] = Caja;
				juego.estado.tablero[f][c - 1] = Jugador;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.columna = juego.estado.columna - 1;
			}
		}
		if (juego.estado.tablero[f][c - 1] == DestinoL){
			juego.estado.tablero[f][c - 1] = DestinoJ;
			juego.estado.tablero[f][c] = DestinoL;
			juego.estado.columna = juego.estado.columna - 1;
		}
		if ((juego.estado.tablero[f][c - 1] == DestinoC) && (juego.estado.tablero[f][c - 2] != Muro) && (juego.estado.tablero[f][c - 2] != Caja)){
			if (juego.estado.tablero[f][c - 2] == DestinoL){
				juego.estado.tablero[f][c - 2] = DestinoC;
				juego.estado.tablero[f][c - 1] = DestinoJ;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.columna = juego.estado.columna - 1;
			}
			if (juego.estado.tablero[f][c - 2] == Libre){
				juego.estado.tablero[f][c - 2] = Caja;
				juego.estado.tablero[f][c - 1] = DestinoJ;
				juego.estado.tablero[f][c] = DestinoL;
				juego.estado.columna = juego.estado.columna - 1;
				juego.estado.numCajasColocadas--;
			}
		}
		juego.numMovimientos++;
		juego.historial.cont++;
	}

	if (juego.estado.tablero[f][c] == Jugador){
		if (juego.estado.tablero[f][c - 1] == Libre){
			juego.estado.tablero[f][c - 1] = Jugador;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.columna = juego.estado.columna - 1;
		}
		if ((juego.estado.tablero[f][c - 1] == Caja) && (juego.estado.tablero[f][c - 2] != Muro)){
			if (juego.estado.tablero[f][c - 2] == DestinoL){
				juego.estado.tablero[f][c - 2] = DestinoC;
				juego.estado.tablero[f][c - 1] = Jugador;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.columna = juego.estado.columna - 1;
				juego.estado.numCajasColocadas++;
			}
			if (juego.estado.tablero[f][c - 2] == Libre){
				juego.estado.tablero[f][c - 2] = Caja;
				juego.estado.tablero[f][c - 1] = Jugador;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.columna = juego.estado.columna - 1;
			}
		}
		if (juego.estado.tablero[f][c - 1] == DestinoL){
			juego.estado.tablero[f][c - 1] = DestinoJ;
			juego.estado.tablero[f][c] = Libre;
			juego.estado.columna = juego.estado.columna - 1;
		}
		if ((juego.estado.tablero[f][c - 1] == DestinoC) && (juego.estado.tablero[f][c - 2] != Muro) && (juego.estado.tablero[f][c - 2] != Caja)){
			if (juego.estado.tablero[f][c - 2] == DestinoL){
				juego.estado.tablero[f][c - 2] = DestinoC;
				juego.estado.tablero[f][c - 1] = DestinoJ;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.columna = juego.estado.columna - 1;
			}
			if (juego.estado.tablero[f][c - 2] == Libre){
				juego.estado.tablero[f][c - 2] = Caja;
				juego.estado.tablero[f][c - 1] = DestinoJ;
				juego.estado.tablero[f][c] = Libre;
				juego.estado.columna = juego.estado.columna - 1;
				juego.estado.numCajasColocadas--;
			}
		}
		juego.numMovimientos++;
		juego.historial.cont++;
	}
}