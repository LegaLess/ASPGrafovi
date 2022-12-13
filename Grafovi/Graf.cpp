#include <iostream>
#include <iomanip>
#include "Graf.h"
#include "PrioritetniRed.h"
#include "Stek.h"

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

void Graf::najkracaPutanja(string s1, string s2)
{
	Cvor* c1 = &(*this)[s1];
	Cvor* c2 = &(*this)[s2];

	Cvor* tek = c1;

	int k = c2->id;
	int j = 0;

	PrioritetniRed p;

	float* dist = new float[n];
	int* prethodnici = new int[n];
	string* put = new string[n];
	float* tezine = new float[n];

	for (int i = 0; i < n; i++) {
		dist[i] = 0;
		put[i] = "";
		prethodnici[i] = -1;
		tezine[i] = 0;
	}

	dist[c1->id] = 1;

	p.insert(*c1, 1);

	Cvor* v = nullptr;
	float cena = 0;

	while (!p.empty()) {
		tek = &p.del();

		if (tek == c2) break;
		for (int i = 0; i < n; i++) {
			if (i == tek->id) continue;
			if (matricaTezina[tek->id][i]) {
				v = &cvorovi[i];
				cena = matricaTezina[tek->id][i];
				if (dist[v->id] < dist[tek->id] * cena) {
					dist[v->id] = dist[tek->id] * cena;
					prethodnici[v->id] = tek->id;
					p.insert(*v, cena);
				}
			}
		}
	}

	while (k != -1) {
		if (j >= 0 && j < n) {
			put[j] = cvorovi[k].sadrzaj;
			tezine[j] = prethodnici[k] != -1 ? matricaTezina[prethodnici[k]][k] : 0;
			j++;
		}
		k = prethodnici[k];
	}
	if (j == 1) cout << "Ne moze se doci od cvora " << s1 << " do cvora " << s2;
	else {
		for (int i = j-1; i > 0; i--) {
			if(i >= 0 && i < n) cout << put[i] << "(" << tezine[i-1] << ")->";
		}

		cout << s2 << "(0)";
	}


	delete[] dist;
	delete[] put;
	delete[] tezine;
	delete[] prethodnici;
}

void Graf::najjacePovezani(string s1)
{
	string* povezani1 = new string[n];
	string* povezani2 = new string[n];

	string* konacnoPovezani = new string[n];
	
	int k = 0;

	DFS(s1, povezani1);
	this->transpose(matricaTezina);
	//cout << *this;
	DFS(s1, povezani2);
	this->transpose(matricaTezina);
	//cout << *this;


	//for (int i = 0; i < n; i++) cout << povezani1[i] << " ";
	//cout << endl;
	//for (int i = 0; i < n; i++) cout << povezani2[i] << " ";
	//cout << endl;

	for (int i = 0; i < n; i++) {
		bool postoji = false;
		for (int j = 0; j < n; j++) {
			if (povezani1[i] == povezani2[j]) {
				postoji = true;
				break;
			}
		}
		if (postoji) {
			if (k >= 0 && k < n) {
				konacnoPovezani[k] = povezani1[i];
				k++;
			}
		}
	}

	cout << "Najjace povezani cvorovi sa cvorom " << s1 << " su: ";

	for (int i = 0; i < n; i++) {
		if (i == n - 1) cout << konacnoPovezani[i];
		else cout << konacnoPovezani[i] << ", ";
	}

}



void Graf::brisiGraf()
{
	brisi();
	cvorovi = alocirajCvorove(0);
	matricaTezina = alocirajMatricu(0);
	n = 0;
	e = 0;
	trenutniBrGrana = 0;
	Cvor::staticID = 0;
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
	e--;
	trenutniBrGrana--;

	return *this;
}

Graf& Graf::brisiCvor(string s1)
{
	int i = (*this)[s1].id, k = 0;
	

	for (int j = 0; j < n; j++) {
		if (matricaTezina[i][j] || matricaTezina[j][i]) k++;
	}

	while (i < n - 1) {

		cvorovi[i + 1].id--;
		cvorovi[i] = cvorovi[i + 1];

		for (int j = 0; j < n; j++) {
			matricaTezina[j][i] = matricaTezina[j][i + 1];
		}

		for (int j = 0; j < n; j++) {
			matricaTezina[i][j] = matricaTezina[i + 1][j];
		}

		i++;
	}

	delete[] matricaTezina[n - 1];

	n--;
	Cvor::staticID--;

	e -= k;
	trenutniBrGrana -= k;

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
	n = g.n;
	e = g.e;
	trenutniBrGrana = g.trenutniBrGrana;

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

	delete[] matricaTezina;

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

string* Graf::DFS(string s, string* povezani)
{
	Cvor* pocetak = &(*this)[s];
	bool* poseceni = new bool[n];
	Stek stack;
	for (int i = 0; i < n; i++) poseceni[i] = false;
	stack.push(*pocetak);

	Cvor* tek = nullptr;
	Cvor* v = nullptr;

	int k = 0;

	while (!stack.empty()) {
		tek = &stack.pop();
		if (!poseceni[tek->id]) {
			if (k >= 0 && k < n) {
				povezani[k] = tek->sadrzaj;
				k++;
			}
			poseceni[tek->id] = true;
		}

		for (int i = 0; i < n; i++) {
			if (matricaTezina[tek->id][i] && !poseceni[i]) {
				stack.push(cvorovi[i]);
			}
		}

	}

	return povezani;
}

float** Graf::transpose(float** matrica)
{
	float tmp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmp = matrica[i][j];
			matrica[i][j] = matrica[j][i];
			matrica[j][i] = tmp;
		}
	}

	return matrica;
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

istream& operator>>(istream& ut, Graf& g)
{
	string podatak1;
	string podatak2;
	float tezina;

	for (int i = 0; i < g.n; i++) {
		ut >> g.cvorovi[i];
	}

	for (int i = 0; i < g.e; i++) {
		ut >> podatak1 >> podatak2 >> tezina;
		g.dodajGranu(podatak1, podatak2, tezina);
	}

	return ut;
}
