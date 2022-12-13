#ifndef _STEK_H_
#define _STEK_H_

#include <iostream>
#include <string>
#include "Cvor.h"

using namespace std;

class Stek {

public:

	Stek() = default;

	Stek(const Stek&);

	Stek(Stek&&);

	Stek& push(Cvor&);

	Cvor& pop();

	bool empty();

	~Stek();


private:

	struct Elem {
		Cvor* cvor;
		Elem* next = nullptr;
		Elem(Cvor& c) : cvor(&c), next(nullptr) {}
	};

	Elem* prvi = nullptr;

	void brisi();

	void premesti(Stek&);

	void kopiraj(const Stek&);

};


#endif