#ifndef _PRIORITETNIRED_H_
#define _PRIORITETNIRED_H_

#include <iostream>
#include <string>
#include "Cvor.h"

using namespace std;

class PrioritetniRed {

public:

	PrioritetniRed() {}

	PrioritetniRed(const PrioritetniRed&);

	PrioritetniRed(PrioritetniRed&&);

	PrioritetniRed& insert(Cvor&, float);
	
	Cvor& del();

	bool empty();

	friend ostream& operator<<(ostream&, PrioritetniRed&);

	~PrioritetniRed();

private:

	struct Elem {
		Cvor* cvor = nullptr;
		float priority;
		Elem* next;
		Elem(Cvor& c, float p) : next(nullptr), priority(p), cvor(&c) {}
	};

	Elem* prvi = nullptr;

	void brisi();

	void kopiraj(const PrioritetniRed&);

	void premesti(PrioritetniRed&);

};


#endif