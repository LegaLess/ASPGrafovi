#include <iostream>
#include <fstream>
#include <string>
#include "Graf.h"
#include "PrioritetniRed.h"

using namespace std;


int main() {

	int n, e, k;

	string line;

	ifstream reader("graf1.txt");

	reader >> n >> e;

	Graf graf(n, e);

	reader >> graf;

	graf.najkracaPutanja("ucenje", "racunar");

	/*
	cout << graf;
	
	graf.brisiCvor("podaci");

	cout << graf;

	graf.dodajCvor("test");
	graf.dodajGranu("test", "algoritam", 0.69f);

	cout << graf;

	graf.brisiGraf();
	graf.dodajCvor("kenjanje");
	graf.dodajCvor("WC");
	graf.dodajGranu("kenjanje", "WC", 0.56f);

	cout << graf;

	reader.close();

	*/

	return 0;
}
