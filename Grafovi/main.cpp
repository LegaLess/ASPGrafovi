#include <iostream>
#include <fstream>
#include <string>
#include "Graf.h"

using namespace std;


int main() {

	int n, e;

	string line;

	ifstream reader("graf1.txt");

	reader >> n >> e;

	Graf graf(n, e);

	reader >> graf;

	cout << graf;

	graf.dodajCvor("kenjanje");
	graf.dodajGranu("kenjanje", "student", 0.99f);
	graf.dodajGranu("knjiga", "proizvod", 0.69f);

	cout << endl;

	cout << graf;

	reader.close();

	return 0;
}
