#include <iostream>
#include <fstream>
#include <string>
#include "Graf.h"

using namespace std;


int main() {

	int n, e, k;

	string line;

	ifstream reader("graf1.txt");

	reader >> n >> e;

	Graf graf(n, e);

	reader >> graf;

	cout << graf;
	
	graf.brisiCvor("podaci");

	cout << graf;

	graf.dodajCvor("test");
	graf.dodajGranu("test", "algoritam", 0.69f);

	cout << graf;

	reader.close();

	return 0;
}
