#include <iostream>
#include <string>
#include "PrioritetniRed.h"
#include "Cvor.h"

using namespace std;

PrioritetniRed& PrioritetniRed::insert(Cvor& c, float p)
{
	Elem* novi = new Elem(c, p);
	

	if (!prvi || prvi->priority >= p) {
		novi->next = prvi;
		prvi = novi;
	}
	else {
		Elem* tek = prvi;

		while (tek->next && tek->next->priority < novi->priority) {
			tek = tek->next;
		}

		novi->next = tek->next;
		tek->next = novi;

	}

	return *this;

}

Cvor& PrioritetniRed::del()
{
	Elem* tek = prvi;
	Elem* prev = nullptr;

	while (tek->next) {
		prev = tek;
		tek = tek->next;
	}

	if (prev) {
		prev->next = nullptr;
	}
	else {
		prvi = nullptr;
	}
	
	return *tek->cvor;
}

bool PrioritetniRed::empty()
{
	if (prvi) {
		return false;
	}
	else {
		return true;
	}
}

ostream& operator<<(ostream& it, PrioritetniRed& p)
{
	PrioritetniRed::Elem* tek = p.prvi;

	while (tek) {
		it << "[" << *tek->cvor << ", " << tek->priority << "]" << endl;
		tek = tek->next;
	}

	return it;
}
