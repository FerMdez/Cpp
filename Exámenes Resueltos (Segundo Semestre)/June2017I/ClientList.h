#ifndef _CLIENTLIST
#define _CLIENTLIST

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Constant:
const int MAX_CLIENTS = 50;


//Types:
typedef struct tClient {
	std::string login, registerDate, city;
	int age;
};

typedef struct tClientList {
	tClient *client[MAX_CLIENTS];
	int cont;
};

//Functions:
void display(tClient& client);
bool load(tClientList& list);
void show(tClientList list, int&); //Implement using recursion.
void free(tClientList& list);


#endif // !_CLIENTLIST
