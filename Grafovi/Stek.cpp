#include <iostream>
#include <string>
#include "Stek.h"
#include "Cvor.h"

using namespace std;


Stek::Stek(const Stek& s)
{
	if(this != &s) kopiraj(s);
}

Stek::Stek(Stek&& s)
{
	premesti(s);
}

Stek& Stek::push(Cvor& c)
{
	Elem* novi = new Elem(c);

	if (prvi) {
		novi->next = prvi;
		prvi = novi;
	}
	else {
		prvi = novi;
	}

	return *this;
}

Cvor& Stek::pop() {

	Elem* pom = prvi;

	prvi = prvi->next;
	return *pom->cvor;
}

bool Stek::empty() {

	if (prvi) {
		return false;
	}
	else {
		return true;
	}

}

Stek::~Stek()
{
	brisi();
}

void Stek::brisi()
{
	Elem* tmp;
	while (tmp = prvi) {
		prvi = prvi->next;
		delete tmp;
	}
}

void Stek::premesti(Stek& s)
{
	prvi = s.prvi;
	s.brisi();
}

void Stek::kopiraj(const Stek& s)
{
	Elem* tek = s.prvi;
	while (tek) {
		this->push(*tek->cvor);
		tek = tek->next;
	}
}

