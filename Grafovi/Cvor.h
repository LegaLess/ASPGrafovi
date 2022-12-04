#ifndef _CVOR_H_
#define _CVOR_H_

#include <iostream>
#include <string>

using namespace std;

class Cvor {

public:


private:

	Cvor() : sadrzaj("") {}

	friend ostream& operator<<(ostream&, const Cvor&);

	friend istream& operator>>(istream&, Cvor&);

	static int staticID;
	int id = staticID++;

	string sadrzaj;

	friend class Graf;
};


#endif