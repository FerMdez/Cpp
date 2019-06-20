#include "DateList.h"
using namespace std;

//Auxiliary functions:
void expand(tDateList& list, int& newCapacity);

void newList(tDateList& list) {
	list.capacity = 10;
	list.cont = 0;
	list.date = new tDate[list.capacity];
}

void insert(tDateList& list, tDate& date) {
	if (list.cont == list.capacity) {
		expand(list, list.capacity);
	}
	list.date[list.cont] = date;
	list.cont++;
}

//
void expand(tDateList& list, int& newCapacity) {
	list.capacity += newCapacity;
	tDate *aux = new tDate[list.capacity];

	for (int i = 0; i < list.cont; i++){
		aux[i] = list.date[i];
	}

	delete[] list.date;
	list.date = aux;

}
//

void display(tDateList& list) {
	cout << setfill(char('-')) << setw(50) << "\n" << setfill(char(0));
	for (int i = 0; i < list.cont; i++){
		display(*list.date[i].client1);
		display(*list.date[i].client2);
		cout << "Date in: " <<  list.date[i].place << ". Rating: " << list.date[i].ratting << endl;
		cout << setfill(char('-')) << setw(50) << "\n" << setfill(char(0));
	}
}

void free(tDateList& list) {
	delete[] list.date;
}