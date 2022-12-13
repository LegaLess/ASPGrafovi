#include <iostream>
#include <fstream>
#include <string>
#include "Graf.h"
#include "PrioritetniRed.h"

using namespace std;


int main() {

	int n, e;

	string line;

	ifstream reader("graf2.txt");

	reader >> n >> e;

	Graf graf(n, e);

	reader >> graf;

	graf.najjacePovezani("preduzece");

	/*
	graf.najkracaPutanja("proizvod", "kapital");

	cout << graf;
	
	graf.brisiCvor("podaci");

	cout << graf;

	graf.dodajCvor("test");
	graf.dodajGranu("test", "algoritam", 0.69f);

	cout << graf;

	graf.brisiGraf();

	cout << graf;

	*/

	reader.close();

	return 0;
}
