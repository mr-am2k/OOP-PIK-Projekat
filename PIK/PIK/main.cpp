#include <iostream>
#include "Korisnik.h"
#include "Admin.h"
#include "Oglas.h"
#include "Vozilo.h"

int main()
{
	
	Korisnik k;
	/*std::cin >> k;
	std::system("cls");
	k.dodajOglas();*/
	k.prijava();
	
	std::system("cls");

	Oglas o;
	o.izbrisiOglas(k);
	return 0;

}
