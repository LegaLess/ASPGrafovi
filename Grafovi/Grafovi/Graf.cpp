#include <iostream>
#include "Graf.h"

using namespace std;

Graf::Graf(int br) : n(br){

	matrica = alocirajMatricu(n);

}

Graf& Graf::dodajGranu(int i, int j)
{
	matrica[i-1][j-1] = true;
	
	return *this;
}

Graf& Graf::dodajCvor()
{
	bool** tmp = nullptr;

	tmp = alocirajMatricu(n + 1);
	kopiraj(tmp, matrica);

	matrica = alocirajMatricu(++n);
	kopiraj(matrica, tmp);

	return *this;
}

bool** Graf::alocirajMatricu(int n){
	bool** tmp = new bool*[n];

	for (int i = 0; i < n; i++) {
		tmp[i] = new bool[n];
		for (int j = 0; j < n; j++) {
			tmp[i][j] = false;
		}
	}

	return tmp;
}

void Graf::kopiraj(bool** matrica1, bool** matrica2){

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrica1[i][j] = matrica2[i][j];
		}
	}

}

ostream& operator<<(ostream& it, Graf& g)
{
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			if(j == g.n-1) it << g.matrica[i][j];
			else it << g.matrica[i][j] << " - ";
		}

		it << endl;
		if (i != g.n-1) {
			for (int j = 0; j < g.n; j++) {
				if (j != g.n) it << "|   ";
			}
		}
		it << endl;
	}

	return it;
}
