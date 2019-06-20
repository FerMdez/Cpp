#ifndef _DATELIST
#define _DATELIST

#include "ClientList.h"

//Constant:



//Types:
typedef struct tDate {
	tClient *client1, *client2;
	std::string place;
	int ratting;
};

typedef struct tDateList {
	tDate *date; //Sorted by rating.
	int cont, capacity;
};


//Functions:
void newList(tDateList& list);
void insert(tDateList& list, tDate& date); //If there are no more free slots add 10 more slots.
void display(tDateList& list);
void free(tDateList& list);


#endif // !_DATELIST
