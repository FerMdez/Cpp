//Exam June 2017 - FP
//Groups: I
//Fernando Méndez Torrubiano

#include "DateList.h"
#include "checkML.h"
using namespace std;

//Auxiliary functions:
int menu();

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Shows memory leaks.

	tClientList clients;
	tDateList dates;
	tDate date;
	int c1, c2;
	int opc = -1, i = 0;

	if (load(clients)) {
		newList(dates);
		while (opc != 0) {
			opc = menu();
			switch (opc){
			case 1: 
				show(clients, i); 
				break;
			case 2: 
				show(clients, i);
				cout << "Clients: ";
				cin >> c1;
				cin >> c2;
				date.client1 = clients.client[c1 - 1];
				date.client2 = clients.client[c2 - 1];
				cout << "Date´s place: ";
				cin >> date.place;
				do {
					cout << "Date´s rating [0-5]: ";
					cin >> date.ratting;
				} while (date.ratting < 0 || date.ratting > 5);
				insert(dates, date);
				break;
			case 3: 
				cout << "Date list: " << endl; 
				display(dates);
				break;
			default:
				break;
			}
			i = 0;
		}
	}
	else {
		cout << "End of program." << endl;
	}

	free(clients);
	free(dates);

	return 0;
}

int menu() {
	int opc = 0;
	
	cout << setfill(char('-')) << setw(50) << "\n" << setfill(char(0));
	cout << "1.-Display client list." << endl;
	cout << "2.-New date." << endl;
	cout << "3.-Display dates." << endl;
	cout << "0.-EXIT." << endl;
	cout << setfill(char('-')) << setw(50) << "\n" << setfill(char(0));

	do {
		cout << "Choose an option: ";
		cin >> opc;
	} while (opc < 0 || opc > 3);

	return opc;
}