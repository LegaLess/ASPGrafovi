#include <iostream>
#include "Graf.h"

using namespace std;


int main() {

	Graf graf(5);

	cout << graf;

	graf.dodajGranu(4, 2).dodajGranu(1, 3);

	cout << graf;

	graf.dodajCvor().dodajCvor();

	graf.dodajGranu(7, 7).dodajGranu(5, 2);

	cout << graf;

	return 0;
}
