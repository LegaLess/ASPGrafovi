#include <iostream>
#include <iomanip>
#include "Graf.h"
#include "PrioritetniRed.h"
#include "Stek.h"

using namespace std;

Graf::Graf(int brCvorova, int brGrana) : n(brCvorova), e(brGrana) {

	matricaTezina = alocirajMatricu(n);
	cvorovi = alocirajCvorove(n);
	dist = new float[n];
	for (int i = 0; i < n; i++) dist[i] = 0;
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
	bool ispis = true;

	Cvor* c1 = &(*this)[s1];
	Cvor* c2 = &(*this)[s2];

	Cvor* tek = c1;

	int k = c2->id;
	int j = 0;

	PrioritetniRed p;

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

	if (ispis) {
		if (j == 1) cout << "Ne moze se doci od cvora " << s1 << " do cvora " << s2;
		else {
			for (int i = j - 1; i > 0; i--) {
				if (i >= 0 && i < n) cout << put[i] << "(" << tezine[i - 1] << ")->";
			}

			cout << s2 << "(0)";
		}
	}

	//delete[] dist;
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

	DFS(s1, povezani1, false);
	DFS(s1, povezani2, true);

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

	if (k == 1) {
		cout << "Rec ne pripada SCC-u.";
		return;
	}

	cout << "Najjace povezani cvorovi sa cvorom " << s1 << " su: ";

	for (int i = 0; i < k; i++) {
		if (konacnoPovezani[i + 1] == "") {
			cout << konacnoPovezani[i];
			break;
		}
		else cout << konacnoPovezani[i] << ", ";
	}

	delete[] konacnoPovezani;
	delete[] povezani1;
	delete[] povezani2;

}

void Graf::kNajjacePovezanih(string s1, int k)
{

	bool postoji = false;

	for (int i = 0; i < n; i++) {
		if (s1 == cvorovi[i].sadrzaj) {
			postoji = true;
			break;
		}
	}

	if (!postoji) {
		cout << "Cvor ne postoji.";
		return;
	}

	string* povezani = new string[n];
	string tmp;
	float dist1, dist2;
	povezani = DFS(s1, povezani, false);

	for (int i = 0; i < n - 1; i++) {

		for (int j = 0; j < n - i - 1; j++) {
			Cvor* c1 = &(*this)[povezani[j]];
			Cvor* c2 = &(*this)[povezani[j + 1]];

			if (povezani[j] == "") break;

			najkracaPutanjaBezIspisa(s1, c1->sadrzaj);
			dist1 = dist[c1->id];
			najkracaPutanjaBezIspisa(s1, c2->sadrzaj);
			dist2 = dist[c2->id];

			if (dist1 < dist2) {
				tmp = povezani[j];
				povezani[j] = povezani[j + 1];
				povezani[j + 1] = tmp;
			}

		}

	}

	postoji = false;
	for (int i = 1; i < n; i++) {
		if (povezani[i] != "") {
			postoji = false;
			break;
		}
	}

	if (!postoji) {
		cout << "Cvor nema nikakve grane.";
		return;
	}

	cout << "k najjace povezanih reci sa recju " << s1 << " su: ";

	for (int i = 1; i < n; i++) {
		if (povezani[i + 1] == "" || i + 1 == k + 1) {
			cout << povezani[i];
			break;
		}
		else cout << povezani[i] << ", ";
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
	if (!matricaTezina[(*this)[s1].id][(*this)[s2].id]) {
		cout << "Grana ne postoji.";
		return *this;
	}

	matricaTezina[(*this)[s1].id][(*this)[s2].id] = 0.0;
	e--;
	trenutniBrGrana--;

	return *this;
}

Graf& Graf::brisiCvor(string s1)
{
	bool postoji = false;

	for (int i = 0; i < n; i++) {
		if (s1 == cvorovi[i].sadrzaj) {
			postoji = true;
			break;
		}
	}

	if (!postoji) {
		cout << "Cvor ne postoji.";
		return *this;
	}

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

float** Graf::alocirajMatricu(int n) {
	float** tmp = new float* [n];

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

void Graf::kopiraj(float** matricaTezina1, float** matricaTezina2) {

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

string* Graf::DFS(string s, string* povezani, bool trans)
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
			if (trans) {
				if (matricaTezina[i][tek->id] && !poseceni[i]) {
					stack.push(cvorovi[i]);
				}
			}
			else {
				if (matricaTezina[tek->id][i] && !poseceni[i]) {
					stack.push(cvorovi[i]);
				}

			}
		}

	}

	return povezani;
}

void Graf::najkracaPutanjaBezIspisa(string s1, string s2)
{
	bool ispis = false;

	Cvor* c1 = &(*this)[s1];
	Cvor* c2 = &(*this)[s2];

	Cvor* tek = c1;

	int k = c2->id;
	int j = 0;

	PrioritetniRed p;

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

	if (ispis) {
		if (j == 1) cout << "Ne moze se doci od cvora " << s1 << " do cvora " << s2;
		else {
			for (int i = j - 1; i > 0; i--) {
				if (i >= 0 && i < n) cout << put[i] << "(" << tezine[i - 1] << ")->";
			}

			cout << s2 << "(0)";
		}
	}

	//delete[] dist;
	delete[] put;
	delete[] tezine;
	delete[] prethodnici;
}

ostream& operator<<(ostream& it, const Graf& g)
{
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			if (j == g.n - 1) it << g.matricaTezina[i][j];
			else it << setprecision(2) << fixed << g.matricaTezina[i][j] << " - ";
		}

		it << endl;
		if (i != g.n - 1) {
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
