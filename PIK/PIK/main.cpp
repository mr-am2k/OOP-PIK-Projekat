#include <iostream>
#include "Korisnik.h"
#include "Admin.h"
#include "Oglas.h"
int main()
{
	Korisnik k;
	if (k.prijava()) {
		k.dodajOglas();
	}

	return 0;

}