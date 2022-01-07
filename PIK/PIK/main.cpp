#include <iostream>
#include "Korisnik.h"
#include "Admin.h"
#include "Oglas.h"
#include "Vozilo.h"

int main()
{
	
	Korisnik k;
	k.prijava();

	k.dodajOglas();

	Oglas o;

	//o.mojiOglasi(k);
	
	//o.promijeniStanjeOglasa(k);
	
	//o.izbrisiOglas(k);
	return 0;

}
