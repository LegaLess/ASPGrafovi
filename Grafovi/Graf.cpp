#include <iostream>
#include <iomanip>
#include "Graf.h"

using namespace std;

Graf::Graf(int brCvorova, int brGrana) : n(brCvorova), e(brGrana){

	matricaTezina = alocirajMatricu(n);
	cvorovi = alocirajCvorove(n);
}

Graf::Graf(const Graf& g)
{
	if (this != &g) {
		kopiraj(g);
	}
}

Graf::Graf(Graf&& g)
{
	premesti(g);
	brisi();
}

Cvor& Graf::operator[](string s) const
{
	int k = 0;

	for (int i = 0; i < n; i++) {
		if (cvorovi[i].sadrzaj == s) {
			k = i;
			break;
		}
	}

	return cvorovi[k];
}

Graf& Graf::dodajGranu(string podatak1, string podatak2, float tezina)
{
	if (trenutniBrGrana < e) {
		matricaTezina[(*this)[podatak1].id][(*this)[podatak2].id] = tezina;
		trenutniBrGrana++;
	}
	else {
		matricaTezina[(*this)[podatak1].id][(*this)[podatak2].id] = tezina;
		e++;
		trenutniBrGrana++;
	}

	return *this;
}

Graf& Graf::dodajCvor(string podatak)
{
	float** tmp = nullptr;
	Cvor* tmpCvorovi = nullptr;

	tmp = alocirajMatricu(n + 1);
	kopiraj(tmp, matricaTezina);

	tmpCvorovi = alocirajCvorove(n + 1);
	kopiraj(tmpCvorovi, cvorovi);


	n++;

	matricaTezina = alocirajMatricu(n);
	kopiraj(matricaTezina, tmp);

	cvorovi = alocirajCvorove(n);
	kopiraj(cvorovi, tmpCvorovi);
	cvorovi[n - 1].sadrzaj = podatak;

	return *this;
}

Graf& Graf::brisiGranu(string s1, string s2)
{
	matricaTezina[(*this)[s1].id][(*this)[s2].id] = 0.0;

	return *this;
}

Graf& Graf::brisiCvor(string, string)
{
	return *this;
}

Graf::~Graf()
{
	brisi();
}

float** Graf::alocirajMatricu(int n){
	float** tmp = new float*[n];

	for (int i = 0; i < n; i++) {
		tmp[i] = new float[n];
		for (int j = 0; j < n; j++) {
			tmp[i][j] = false;
		}
	}

	return tmp;
}

void Graf::kopiraj(const Graf& g)
{
	matricaTezina = alocirajMatricu(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matricaTezina[i][j] = g.matricaTezina[i][j];
		}
	}

	cvorovi = alocirajCvorove(n);

	for (int i = 0; i < n; i++) {
		cvorovi[i] = g.cvorovi[i];
	}
}

void Graf::premesti(Graf& g)
{
	matricaTezina = g.matricaTezina;
	cvorovi = g.cvorovi;
}

void Graf::brisi()
{
	for (int i = 0; i < n; i++) {
		delete[] matricaTezina[i];
	}

	delete[] cvorovi;
}

void Graf::kopiraj(float** matricaTezina1, float** matricaTezina2){

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matricaTezina1[i][j] = matricaTezina2[i][j];
		}
	}

}

Cvor* Graf::alocirajCvorove(int n)
{
	Cvor::staticID = 0;

	return new Cvor[n];
}

void Graf::kopiraj(Cvor* c1, Cvor* c2)
{
	for (int i = 0; i < n; i++) {
		c1[i].sadrzaj = c2[i].sadrzaj;
	}
}

ostream& operator<<(ostream& it, const Graf& g)
{
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			if(j == g.n-1) it << g.matricaTezina[i][j];
			else it << setprecision(2) << fixed <<  g.matricaTezina[i][j] << " - ";
		}

		it << endl;
		if (i != g.n-1) {
			for (int j = 0; j < g.n; j++) {
				if (j != g.n) it << "  |    ";
			}
		}
		it << endl;
	}

	for (int i = 0; i < g.n; i++) {
		it << g.cvorovi[i] << " ";
	}

	it << endl;

	return it;
}

istream& operator>>(istream& is, Graf& g)
{
	string podatak1;
	string podatak2;
	float tezina;

	for (int i = 0; i < g.n; i++) {
		is >> g.cvorovi[i];
	}

	for (int i = 0; i < g.e; i++) {
		is >> podatak1 >> podatak2 >> tezina;
		g.dodajGranu(podatak1, podatak2, tezina);
	}

	return is;
}
