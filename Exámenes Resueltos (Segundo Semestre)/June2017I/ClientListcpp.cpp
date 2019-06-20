#include "ClientList.h"
using namespace std;

void display(tClient& client) {
	cout << right << setw(10) << client.login
		<< setw(15) << client.registerDate
		<< setw(5) << client.age << " years"
		<< setw(10) << client.city << endl;
}

bool load(tClientList& list) {
	bool loaded = false;
	ifstream file;
	int numClients = 0;

	list.cont = 0;

	file.open("clients.txt");
	if (!file.is_open()) {
		cout << "Failed to load clients." << endl;
	}
	else {
		file >> numClients;
		while (!file.fail() && list.cont < numClients) {
			list.client[list.cont] = new tClient;
			file >> list.client[list.cont]->login;
			file >> list.client[list.cont]->registerDate;
			file >> list.client[list.cont]->age;
			file >> list.client[list.cont]->city;
			list.cont++;
		}
		loaded = true;
	}
	file.close();

	return loaded;
}

void show(tClientList list, int& i) {

	if (i < list.cont) {
		cout << i + 1 << ":";
		display(*list.client[i]);
		i++;
		show(list, i);
	}
}

void free(tClientList& list) {
	for (int i = 0; i < list.cont; i++){
		delete list.client[i];
	}
}