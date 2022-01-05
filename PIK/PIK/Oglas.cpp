#include "Oglas.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <fstream>

#include "Nekretnina.h"
#include "Tehnika.h"
#include "Vozilo.h"

Oglas::Oglas()
{
    this->id = 1;
    this->autor = "Sinan";
    this->naslov = "Passat";
    this->opis = "Najbolje auto na svijetu";
    this->stanje = dostupno;
    this->cijena = 1000;
    this->kategorija = vozilo;
}

void Oglas::setID()
{
    this->id = generisiRandomID();
}

void Oglas::setNaslov()
{
    std::cout << "Unesite naslov oglasa: ";
    getline(std::cin,this->naslov);
    for (int i=0;i<this->naslov.length(); i++)
    {
        if (this->naslov[i] == 32) this->naslov[i] = 95;
    }
}

void Oglas::setOpis()
{
    std::cout << "Unesite opis oglasa: ";
    getline(std::cin, this->opis);
    for (int i = 0; i < this->opis.length(); i++)
    {
        if (this->opis[i] == 32) this->opis[i] = 95;
    }
}

void Oglas::setCijena()
{
    std::cout << "Unesite cijenu: ";
    do {
        std::cin >> this->cijena;
        if (this->cijena < 0) std::cout << "Cijena mora biti veca od 0!\n";
    } while (this->cijena < 0);
    std::cin.ignore();
}

void Oglas::setStanje()
{
    std::shared_ptr<int> izbor = std::make_shared<int>();
    do
    {
        std::cout << "Stanje(nedostupno: 0, dostupno: 1): ";
        std::cin >> *izbor;
        if (*izbor < 0 || *izbor > 1) std::cout << "[GRESKA]: Stanje moze biti samo 0 ili 1.\n";
    } while (*izbor < 0 || *izbor > 1);
    this->stanje = static_cast<Stanje>(*izbor);
    std::cin.ignore();
}

void Oglas::setKategorija()
{
    std::shared_ptr<int> izbor = std::make_shared<int>();
    do
    {
        std::cout << "Unesite kategoriju oglasa (1. Vozilo 2. Nekretnina 3. Tehnika): ";
        std::cin >> *izbor;
        if (*izbor < 1 || *izbor >3) std::cout << "Neispravan unos, probajte ponovo!\n";
    } while (*izbor < 1 || *izbor > 3);
    this->kategorija = static_cast<Kategorija>(*izbor);
    std::cin.ignore();
}

int Oglas::getID()
{
    return this->id;
}

std::string Oglas::getAutor()
{
    return this->autor;
}

std::string Oglas::getNaslov()
{
    return this->naslov;
}

std::string Oglas::getOpis()
{
    return this->opis;
}

Kategorija Oglas::getKategorija()
{
    return this->kategorija;
}

float Oglas::getCijena()
{
    return this->cijena;
}

Stanje Oglas::getStanje()
{
    return this->stanje;
}

std::string Oglas::getStanjeString()
{
    switch (this->stanje) {
        case nedostupno:
            return "nedostupno";
        case dostupno:
            return "dostupno";
        default:
            return "Greska";
    }
}

std::string Oglas::getKategorijaString()
{
    switch (this->kategorija) {
    case vozilo:
        return "vozila";
    case nekretnina:
        return "nekretnina";
    case tehnika:
        return "tehnika";
    default:
        return "Greska";
    }
}

const int Oglas::getBrojAktivnihOglasa() const
{
    auto temp = std::make_shared<Oglas>();
    auto brojac = std::make_shared<int>(0);
    std::ifstream ulaz("oglasi.txt");
	try
	{
        if(ulaz.is_open())
        {
            int stanjeBr;
            int kategorijaBr;
	        while(ulaz >> temp->id >> temp->autor >> temp->naslov >> temp->opis >> temp->cijena >> stanjeBr >> kategorijaBr)
	        {
                if (stanjeBr == 1) *brojac = *brojac + 1;
	        }
            ulaz.close();
            return *brojac;
        }
        else
        {
	        throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
        }
		
	}
	catch (const char* greska)
	{
        std::cout << greska;
        exit(0);
	}
}

const int Oglas::getBrojNedostupnihOglasa() const
{
    auto temp = std::make_shared<Oglas>();
    auto brojac = std::make_shared<int>(0);
    std::ifstream ulaz("oglasi.txt");
    try
    {
        if (ulaz.is_open())
        {
            int stanjeBr;
            int kategorijaBr;
            while (ulaz >> temp->id >> temp->autor >> temp->naslov >> temp->opis >> temp->cijena >> stanjeBr >> kategorijaBr)
            {
                if (stanjeBr == 0) *brojac = *brojac + 1;
            }
            ulaz.close();
            return *brojac;
        }
        else
        {
            throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
        }

    }
    catch (const char* greska)
    {
        std::cout << greska;
        exit(0);
    }
}

void Oglas::mojiOglasi(Korisnik& tempKorisnik)
{
    auto temp = std::make_shared<Oglas>();
    std::ifstream ulaz("oglasi.txt");
    auto tempBrojac = std::make_shared<int>();
    *tempBrojac = 0;
    try
    {
        if (ulaz.is_open())
        {
            int stanjeBr;
            int kategorijaBr;
            std::cout << "Oglasi korisnika " << tempKorisnik.getUsername() << ": \n\n";
            while (ulaz >> temp->id >> temp->autor >> temp->naslov >> temp->opis >> temp->cijena >> stanjeBr >> kategorijaBr)
            {
                temp->stanje = static_cast<Stanje>(stanjeBr);
                temp->kategorija = static_cast<Kategorija>(kategorijaBr);
                if(tempKorisnik.getUsername().compare(temp->autor) == 0)
                {
                    for (int i = 0; i < temp->naslov.length(); i++)
                    {
                        if (temp->naslov[i] == 95) temp->naslov[i] = 32;
                    }
                    for (int i = 0; i < temp->opis.length(); i++)
                    {
                        if (temp->opis[i] == 95) temp->opis[i] = 32;
                    }
                    std::cout << "Oglas ID: " << temp->getID() << "\n";
                    std::cout << "Autor oglasa: " << temp->getAutor() << "\n";
                    std::cout << "Naslov: " << temp->getNaslov() << "\n";
                    std::cout << "Opis: " << temp->getOpis() << "\n";
                    std::cout << "Cijena: " << temp->getCijena() << "\n";
                    std::cout << "Stanje: " << temp->getStanjeString() << "\n";
                    std::cout << "Kategorija: " << temp->getKategorijaString() << "\n\n";
                    *tempBrojac = *tempBrojac + 1;

                }
            }
            if(*tempBrojac == 0)
            {
                std::cout << "Ovaj korisnik nema oglasa!!!\n";
            } 
            ulaz.close();
        }
        else
        {
            throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
        }

    }
    catch (const char* greska)
    {
        std::cout << greska;
        exit(0);
    }

}

void Oglas::promijeniStanjeOglasa(Korisnik& tempKorisnik)
{
    std::vector<Oglas> oglasi;
    auto temp = std::make_shared<Oglas>();
    auto tempID = std::make_shared<int>();
    auto tempBrojac = std::make_shared<int>();
    std::ifstream ulaz("oglasi.txt");
	if (ulaz.is_open())
	{
		int stanjeBr;
		int kategorijaBr;
		while (ulaz >> temp->id >> temp->autor >> temp->naslov >> temp->opis >> temp->cijena >> stanjeBr >> kategorijaBr)
		{
			temp->stanje = static_cast<Stanje>(stanjeBr);
            temp->kategorija = static_cast<Kategorija>(kategorijaBr);
            if (tempKorisnik.getUsername().compare(temp->autor) == 0) *tempBrojac = *tempBrojac + 1;
			oglasi.push_back(*temp);
		}
		ulaz.close();

	}
	else
        {
            std::cout << "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
        }
    
    if(*tempBrojac == 0)
    {
        std::cout << "Vi nemate oglasa te ne mozete promijeniti stanje!\n";
    }
    else
    {
        this->mojiOglasi(tempKorisnik);
        std::cin.ignore();
        bool promijenjeno = false;
        do
        {
            std::cout << "Unesite ID oglasa kome zelite promijeniti stanje: ";
            std::cin >> *tempID;
            for (int i = 0; i < oglasi.size(); i++)
            {
                if (*tempID == oglasi[i].getID() && (tempKorisnik.getUsername().compare(oglasi[i].getAutor()) == 0))
                {
                    if (oglasi[i].stanje == dostupno) 
                    {
                    	oglasi[i].stanje = nedostupno;
                        std::cout << "Stanje oglasa uspojesno promijenjeno iz dostupno u nedostupno!\n";
                    }

                    else 
                    {
                        oglasi[i].stanje = dostupno;
                        std::cout << "Stanje oglasa uspojesno promijenjeno iz nedostupno u dostupno!\n";

                    }
                    promijenjeno = true;

                }
            }
            if(!promijenjeno)
            {
                std::cout << "Unijeli ste pogresan ID, pokusajte ponovo!\n";
            }
        } while (!promijenjeno);
        try {
            std::ofstream izlaz("pomocniOglasi.txt", std::ios::app);
            if (izlaz.is_open()) {
                for (int i = 0; i < oglasi.size(); i++)
                {
                    izlaz << oglasi[i].id << "\t";
                    izlaz << oglasi[i].autor << "\t";
                    izlaz << oglasi[i].naslov << "\t";
                    izlaz << oglasi[i].opis << "\t";
                    izlaz << oglasi[i].cijena << "\t";
                    izlaz << oglasi[i].stanje << "\t";
                    izlaz << oglasi[i].kategorija << "\n";
                }
                izlaz.close();
                remove("oglasi.txt"); //brise se originalna datoteka
                rename("pomocniOglasi.txt", "oglasi.txt"); //mijenja se ime pomocne datoteke u originalno ime datoteke
            }
            else {
                throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
            }
        }
        catch (const char* greska) {
            std::cout << greska;
            exit(0);
        }
    }
}

void Oglas::izbrisiOglas(Korisnik& tempKorisnik)
{
    std::vector<Oglas> oglasi;
    std::vector<Oglas> noviOglasi;
    auto temp = std::make_shared<Oglas>();
    auto tempID = std::make_shared<int>();
    auto tempBrojac = std::make_shared<int>();
    auto indexElementaZaBrisanje = std::make_shared<int>();
    std::ifstream ulaz("oglasi.txt");
    if (ulaz.is_open())
    {
        int stanjeBr;
        int kategorijaBr;
        while (ulaz >> temp->id >> temp->autor >> temp->naslov >> temp->opis >> temp->cijena >> stanjeBr >> kategorijaBr)
        {
            temp->stanje = static_cast<Stanje>(stanjeBr);
            temp->kategorija = static_cast<Kategorija>(kategorijaBr);
            if (tempKorisnik.getUsername().compare(temp->autor) == 0) *tempBrojac = *tempBrojac + 1;
            oglasi.push_back(*temp);
        }
        ulaz.close();

    }
    else
    {
        std::cout << "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
    }

    if (*tempBrojac == 0)
    {
        std::cout << "Vi nemate oglasa!\n";
    }
    else
    {
        this->mojiOglasi(tempKorisnik);
        bool promijenjeno = false;
        do
        {
            std::cout << "Unesite ID oglasa koji zelite izbrisati: ";
            std::cin >> *tempID;
            std::cin.ignore();
            for (int i = 0; i < oglasi.size(); i++)
            {
                if (*tempID == oglasi[i].getID() && (tempKorisnik.getUsername().compare(oglasi[i].getAutor()) == 0))
                {
                    promijenjeno = true;
                    *indexElementaZaBrisanje = i;
                    
                }
                else
                {
                    noviOglasi.push_back(oglasi[i]);
                }
            }
            if (!promijenjeno)
            {
                std::cout << "Unijeli ste pogresan ID, pokusajte ponovo!\n";
            }
        } while (!promijenjeno);
    	std::ofstream izlaz("pomocniOglasi.txt", std::ios::app);
    	if (izlaz.is_open()) {
    		for (int i = 0; i < noviOglasi.size(); i++)
    		{
    			izlaz << noviOglasi[i].id << "\t";
    			izlaz << noviOglasi[i].autor << "\t";
    			izlaz << noviOglasi[i].naslov << "\t";
    			izlaz << noviOglasi[i].opis << "\t";
    			izlaz << noviOglasi[i].cijena << "\t";
    			izlaz << noviOglasi[i].stanje << "\t";
    			izlaz << noviOglasi[i].kategorija << "\n";
    		}
    		izlaz.close();
    		remove("oglasi.txt"); //brise se originalna datoteka
    		rename("pomocniOglasi.txt", "oglasi.txt"); //mijenja se ime pomocne datoteke u originalno ime datoteke
    	}
            else {
                std::cout<< "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";}
    }
    //brisanje u pojedinacnoj datoteci
    switch(oglasi[*indexElementaZaBrisanje].getKategorija())
    {
		case vozilo: {
            auto tempVozilo = std::make_shared<Vozilo>();
            std::vector<Vozilo> vozila = tempVozilo->getVozila();
            std::ofstream unos("novaVozila.txt");
			if(unos.is_open())
			{
                for (int i = 0; i < vozila.size(); i++)
                {
                    if (vozila[i].getID() != oglasi[*indexElementaZaBrisanje].getID())
                    {
                        unos << vozila[i].getID() << "\t";
                        unos << vozila[i].getGodiste() << "\t";
                        unos << vozila[i].getKilovati() << "\t";
                        unos << vozila[i].getBrBrzina() << "\t";
                        unos << vozila[i].getKilometraza() << "\t";
                        unos << vozila[i].getBoja() << "\t";
                        unos << vozila[i].getTip() << "\t";
                        unos << vozila[i].getVrstaGoriva() << "\n";
                    }
                    else {
                        continue;
                    }
                }
                unos.close();
                remove("vozila.txt"); //brise se originalna datoteka
                rename("novaVozila.txt", "vozila.txt"); //mijenja se ime pomocne datoteke u originalno ime datoteke
			}
            else
            {
                std::cout << "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
            }
			break;
		}
		case nekretnina: {
            auto tempNekretnina = std::make_shared<Nekretnina>();
            std::vector<Nekretnina> nekretnine = tempNekretnina->getNekretnine();
            std::ofstream unos("novaNekretnina.txt");
            if (unos.is_open())
            {
                for (int i = 0; i < nekretnine.size(); i++)
                {
                    if (nekretnine[i].getID() != oglasi[*indexElementaZaBrisanje].getID())
                    {
                        unos << nekretnine[i].getID() << "\t";
                        unos << nekretnine[i].getKvadrati() << "\t";
                        unos << nekretnine[i].getBrSoba() << "\t";
                        unos << nekretnine[i].getBrSpratova() << "\t";
                        unos << nekretnine[i].getGrad() << "\t";
                        unos << nekretnine[i].getUlica() << "\t";
                        unos << nekretnine[i].getVrstaNekretnineString() << "\n";
                    }
                    else {
                        continue;
                    }
                }
                unos.close();
                remove("nekretnine.txt"); //brise se originalna datoteka
                rename("novaNekretnina.txt", "nekretnine.txt"); //mijenja se ime pomocne datoteke u originalno ime datoteke
            }
            else
            {
                std::cout << "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
            }
            break;
		}
		case tehnika: {
            auto tempTehnika = std::make_shared<Tehnika>();
            std::vector<Tehnika> tehnika = tempTehnika->getTehnike();
            std::ofstream unos("novaTehnika.txt");
            if (unos.is_open())
            {
                for (int i = 0; i < tehnika.size(); i++)
                {
                    if (tehnika[i].getID() != oglasi[*indexElementaZaBrisanje].getID())
                    {
                        unos << tehnika[i].getID() << "\t";
                        unos << tehnika[i].getVrstaTehnikeString()  << "\t";
                        unos << tehnika[i].getRam() << "\t";
                        unos << tehnika[i].getPohrana() << "\t";
                        unos << tehnika[i].getProcesor() << "\t";
                        unos << tehnika[i].getProizvodjac() << "\t";
                        unos << tehnika[i].getOperativniSistem() << "\n";
                    }
                    else {
                        continue;
                    }
                }
                unos.close();
                remove("tehnika.txt"); 
                rename("novaTehnika.txt", "tehnika.txt"); 
            }
            else
            {
                std::cout << "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
            }
            break;
		}
		default: {
			std::cout << "Greska!";
		}
    }

}


int Oglas::generisiRandomID()
{
    srand(time(NULL));
    rand();
    int a;
    do {
        a = rand()%999+1;
    } while (provjeriID(a));
    return a;
}

bool Oglas::provjeriID(int a)
{
    std::shared_ptr<Oglas> temp = std::make_shared<Oglas>();
    bool postoji = false;
    int broj;
    std::ifstream ispis("oglasi.txt");
    if (ispis.is_open()) {
        int stanjeBr;
        int kategorijaBr;
        while (ispis >> temp->id >> temp->autor >> temp->naslov >> temp->opis >> temp->cijena >> stanjeBr >> kategorijaBr) {
            broj = temp->id;
            temp->stanje = static_cast<Stanje>(stanjeBr);
            temp->kategorija = static_cast<Kategorija>(kategorijaBr);
            if (a == broj) postoji = true;
        }
        ispis.close();
    }
    else {
        std::cout << "[GRESKA] Ne postoji datoteka!\n";
    }
    return postoji;
}

void Oglas::unosOglasa()
{
  
}

std::istream& operator>>(std::istream& unos, Oglas& o)
{
    std::cout << "UNOS OGLASA\n";
    o.setID();
    o.setNaslov();
    o.setOpis();
    o.setCijena();
    o.setStanje();

    try {
        std::ofstream izlaz("oglasi.txt", std::ios::app);
        if (izlaz.is_open()) {
            izlaz << o.id << "\t";
            izlaz << o.autor << "\t";
            izlaz << o.naslov << "\t";
            izlaz << o.opis << "\t";
            izlaz << o.cijena << "\t";
            izlaz << o.stanje << "\t";
            izlaz << o.kategorija << "\n";
            izlaz.close();
        }
        else {
            throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
        }
    }
    catch (const char* greska) {
        std::cout << greska;
        exit(0);
    }

    return unos;
}


