#include <iostream>
#include <fstream>
#include <string>
#include "Graf.h"
#include "PrioritetniRed.h"

using namespace std;


int main() {

	int n, e, op = 0, k;
	float t;
	string s1, s2;

	string line;

	ifstream reader("graf2.txt");

	reader >> n >> e;

	Graf graf(n, e);

	reader >> graf;

	while (op != -1) {
		cout << "1. k najslicnijih reci zadatoj reci." << endl;
		cout << "2. Najkraca putanja izmedju 2 reci." << endl;
		cout << "3. Nalazenje svih jako povezanih reci sa datom recju." << endl;
		cout << "4. Dodavanje cvora." << endl;
		cout << "5. Brisanje cvora." << endl;
		cout << "6. Dodavanje grane." << endl;
		cout << "7. Brisanje grane." << endl;
		cout << "8. Ispis grafa." << endl;
		cout << "9. Brisanje grafa." << endl;

		cout << "Unesite koju operaciju zelite da uradite (-1 ako zelite da izadjete): ";
		cin >> op;
		switch (op)
		{
		case 1: cout << "Unesite rec i broj k odvojeni razmakom (ETF 3): ";
			cin >> s1 >> k;
			if (s1 == " " || k <= 0 || s1 == "") {
				cout << "Pogresan unos." << endl;
				break;
			}
			graf.kNajjacePovezanih(s1, k);
			cout << endl;
			break;

		case 2: cout << "Unesite 2 reci odvojene razmakom (ETF ucenje): ";
			cin >> s1 >> s2;
			if (s1 == " " || s2 == " " || s1 == "" || s2 == "") {
				cout << "Pogresan unos." << endl;
				break;
			}
			graf.najkracaPutanja(s1, s2);
			cout << endl;
			break;

		case 3: cout << "Unesite rec: ";
			cin >> s1;
			if (s1 == " " || s1 == "") {
				cout << "Pogresan unos." << endl;
				break;
			}
			graf.najjacePovezani(s1);
			cout << endl;
			break;

		case 4: cout << "Unesite naziv cvora za dodavanje: ";
			cin >> s1;
			if (s1 == " " || s1 == "") {
				cout << "Pogresan unos." << endl;
				break;
			}
			graf.dodajCvor(s1);
			cout << "Cvor je dodat";
			cout << endl;
			break;

		case 5: cout << "Unesite naziv cvora za brisanje: ";
			cin >> s1;
			if (s1 == " " || s1 == "") {
				cout << "Pogresan unos." << endl;
				break;
			}
			graf.brisiCvor(s1);
			cout << "Cvor je izbrisan";
			cout << endl;
			break;

		case 6: cout << "Unesite 2 reci i tezinu grane odvojene razmakom, tezina ne sme biti negativna (ETF ucenje 0.62): ";
			cin >> s1 >> s2 >> t;
			if (s1 == " " || s2 == " " || s1 == "" || s2 == "" || t <= 0) {
				cout << "Pogresan unos." << endl;
				break;
			}
			graf.dodajGranu(s1, s2, t);
			cout << "Grana je dodata";
			cout << endl;
			break;

		case 7: cout << "Unesite 2 reci odvojene razmakom (ETF ucenje): ";
			cin >> s1 >> s2;
			if (s1 == " " || s2 == " " || s1 == "" || s2 == "") {
				cout << "Pogresan unos." << endl;
				break;
			}
			graf.brisiGranu(s1, s2);
			cout << "Grana je obrisana";
			cout << endl;
			break;

		case 8: cout << graf; break; cout << endl;

		case 9: cout << "Graf je izbrisan." << endl; graf.brisiGraf(); break;

		default: break;
		}
	}

	reader.close();

	return 0;
}
