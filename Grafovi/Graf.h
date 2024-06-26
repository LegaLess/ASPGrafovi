#ifndef _GRAF_H_
#define _GRAF_H_

#include <iostream>
#include "Cvor.h"

using namespace std;

class Graf {

public:

	Graf(int, int);

	Graf(const Graf&);

	Graf(Graf&&);

	friend ostream& operator<<(ostream&, const Graf&);

	friend istream& operator>>(istream&, Graf&);

	Cvor& operator[](string) const;

	void najkracaPutanja(string, string);

	void najjacePovezani(string);

	void kNajjacePovezanih(string, int);

	void brisiGraf();

	Graf& dodajGranu(string, string, float);

	Graf& dodajCvor(string);

	Graf& brisiGranu(string, string);

	Graf& brisiCvor(string);

	~Graf();

private:

	int n = 0, e = 0;

	int trenutniBrGrana = 0;

	float** matricaTezina = nullptr;

	float* dist;

	Cvor* cvorovi = nullptr;

	float** alocirajMatricu(int);

	void kopiraj(const Graf&);

	void premesti(Graf&);

	void brisi();

	void kopiraj(float**, float**);

	Cvor* alocirajCvorove(int);

	void kopiraj(Cvor*, Cvor*);

	string* DFS(string, string*, bool);

	void najkracaPutanjaBezIspisa(string, string);

};



#endif