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

	cin >> k;



	/*
	cout << graf;

	graf.dodajCvor("kenjanje");
	graf.dodajGranu("kenjanje", "student", 0.99f);
	graf.dodajGranu("knjiga", "proizvod", 0.69f);

	graf.brisiGranu("knjiga", "proizvod");

	cout << endl;

	cout << graf;
	*/
	reader.close();

	return 0;
}
