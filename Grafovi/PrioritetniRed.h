#ifndef _PRIORITETNIRED_H_
#define _PRIORITETNIRED_H_

#include <iostream>
#include <string>
#include "Cvor.h"

using namespace std;

class PrioritetniRed {

public:

	PrioritetniRed() : prvi(nullptr) {}

	PrioritetniRed& insert(Cvor&, float);
	
	Cvor& del();

	bool empty();

	friend ostream& operator<<(ostream&, PrioritetniRed&);

private:

	struct Elem {
		Cvor* cvor = nullptr;
		float priority;
		Elem* next;
		Elem(Cvor& c, float p) : next(nullptr), priority(p), cvor(&c) {}
	};

	Elem* prvi;
};


#endif