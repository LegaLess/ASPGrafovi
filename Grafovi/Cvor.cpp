#include <iostream>
#include <string>
#include "Cvor.h"

using namespace std;

int Cvor::staticID = 0;

istream& operator>>(istream& is, Cvor& c)
{
	is >> c.sadrzaj;

	return is;
}

ostream& operator<<(ostream& it, const Cvor& c)
{
	it << c.sadrzaj << "|" << c.id;

	return it;
}
