#ifndef _PRIORITETNIRED_H_
#define _PRIORITETNIRED_H_

#include <iostream>
#include <string>

using namespace std;

class PrioritetniRed {

public:

	PrioritetniRed& push(string, float);
	

private:

	struct Elem {
		string sadrzaj;
		float prioritet;
		Elem* next;
		Elem() : sadrzaj(""), prioritet(0.00f), next(nullptr) {}
	};

	Elem* prvi;

};


#endif