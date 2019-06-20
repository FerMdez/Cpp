//Sudoku - Fernando Méndez Torrubiano
#include "RegistroSudoku.h"
using namespace std;

bool cargar(tRegSudoku& sudoku, istream& infile) {

	infile >> sudoku.nomTablero;
	infile >> sudoku.puntos;

	return !infile.fail() ? true : false;
}
void mostrar(const tRegSudoku& sudoku) {

	cout << right << setw(7) << "SUDOKU: " << sudoku.nomTablero
		<< setw(11) << "NIVEL: " << sudoku.puntos << endl;

}

////

void iniciar(tRegSudoku& registro, string file, int puntos) {
	registro.nomTablero = file;
	registro.puntos = puntos;
}

bool guardar(const tRegSudoku& registro, ostream& outfile) {

	outfile << registro.nomTablero << " ";
	outfile << registro.puntos << endl;

	return !outfile.fail() ? true : false;
}

bool operator<(const tRegSudoku& regIzq, const tRegSudoku& regDer) {
	return((regIzq.puntos < regDer.puntos) || ((regIzq.puntos == regDer.puntos) && (regIzq.nomTablero < regDer.nomTablero))) ? true : false;
}