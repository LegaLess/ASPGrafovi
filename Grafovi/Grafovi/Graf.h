#ifndef _GRAF_H_
#define _GRAF_H_

#include <iostream>

using namespace std;

class Graf {

public:

	Graf(int);

	friend ostream& operator<<(ostream&, Graf&);

	Graf& dodajGranu(int, int);

	Graf& dodajCvor();


private:

	int n;

	bool** matrica;

	bool** alocirajMatricu(int);

	void kopiraj(bool**, bool**);

};



#endif