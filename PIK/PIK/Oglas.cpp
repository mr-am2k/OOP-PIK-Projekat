#include "Oglas.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>

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
    do {
        std::cout << "Unesite naslov oglasa: ";
        getline(std::cin, this->naslov);
        if (this->naslov.size() > 31) std::cout << "Naslov moze sadrzavati maksimalno 32 karaktera!\n";
    } while (this->naslov.size() > 31 || this->naslov.empty());
    for (int i=0;i<this->naslov.length(); i++)
    {
        if (this->naslov[i] == 32) this->naslov[i] = 95;
    }
}

void Oglas::setOpis()
{
    do {
        std::cout << "Unesite opis oglasa: ";
        getline(std::cin, this->opis);
        if (this->opis.size() > 31) std::cout << "Opis moze sadrzavati maksimalno 32 karaktera!\n";
    } while (this->opis.size() > 31 || this->opis.empty());
    for (int i = 0; i < this->opis.length(); i++)
    {
        if (this->opis[i] == 32) this->opis[i] = 95;
    }
}

void Oglas::setCijena()
{
    do {
        std::cout << "Unesite cijenu: ";
        std::cin >> this->cijena;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->cijena < 1) std::cout << "[GRESKA] Uneseni parametar mora biti pozitivan broj!\n";
    } while (this->cijena < 1);
    std::cin.ignore();
}

void Oglas::setStanje()
{
    std::shared_ptr<int> izbor = std::make_shared<int>();
    do
    {
        std::cout << "Stanje(nedostupno: 1, dostupno: 2): ";
        std::cin >> *izbor;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (*izbor < 1 || *izbor > 2) std::cout << "Neispravan unos, probajte ponovo!\n";
    } while (*izbor < 1 || *izbor > 2);
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
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
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
            std::string linijaInfo;
            getline(ulaz, linijaInfo);
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
            std::string linijaInfo;
            getline(ulaz, linijaInfo);
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

const std::vector<Oglas> Oglas::getOglasi() const
{
    std::vector<Oglas> oglasi;
    auto tempOglas = std::make_shared<Oglas>();
    try {
        std::ifstream ulaz("oglasi.txt", std::ios::app);
        if (ulaz.is_open()) {
            int stanje;
            int kategorija;
            std::string linijaInfo;
            getline(ulaz, linijaInfo);
            while (ulaz >> tempOglas->id >> tempOglas->autor >> tempOglas->naslov >> tempOglas->opis >> tempOglas->cijena >> stanje >> kategorija)
            {
                for (int i = 0; i < tempOglas->naslov.length(); i++)
                {
                    if (tempOglas->naslov[i] == 95) tempOglas->naslov[i] = 32;
                }
                for (int i = 0; i < tempOglas->opis.length(); i++)
                {
                    if (tempOglas->opis[i] == 95) tempOglas->opis[i] = 32;
                }
                tempOglas->kategorija = static_cast<Kategorija>(kategorija);
                tempOglas->stanje = static_cast<Stanje>(stanje);
                oglasi.push_back(*tempOglas);
            }
        }
        else {
            throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
        }
        ulaz.close();
    }
    catch (const char* greska) {
        std::cout << greska;
        exit(0);
    }

    return oglasi;
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
            std::string linijaInfo;
            getline(ulaz, linijaInfo);
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
        std::string linijaInfo;
        getline(ulaz, linijaInfo);
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
                        std::cout << "Stanje oglasa uspjesno promijenjeno iz dostupno u nedostupno!\n";
                    }

                    else 
                    {
                        oglasi[i].stanje = dostupno;
                        std::cout << "Stanje oglasa uspjesno promijenjeno iz nedostupno u dostupno!\n";

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
                izlaz << "ID\tUsername\tNaslov\t\t\t\tOpis\t\t\t\tCijena\t\tStanje\t\tKategorija\n";
                for (int i = 0; i < oglasi.size(); i++)
                {
                    izlaz << oglasi[i].id << "\t";
                    if (oglasi[i].autor.size() >= 8) izlaz << oglasi[i].autor << "\t";
                    else izlaz << oglasi[i].autor << "\t\t";
                    if (oglasi[i].naslov.size() >= 24) izlaz << oglasi[i].naslov << "\t";
                    else if (oglasi[i].naslov.size() >= 16 && oglasi[i].naslov.size() < 24) izlaz << oglasi[i].naslov << "\t\t";
                    else if (oglasi[i].naslov.size() >= 8 && oglasi[i].naslov.size() < 16) izlaz << oglasi[i].naslov << "\t\t\t";
                    else izlaz << oglasi[i].naslov << "\t\t\t\t";
                    if (oglasi[i].opis.size() >= 24) izlaz << oglasi[i].opis << "\t";
                    else if (oglasi[i].opis.size() >= 16 && oglasi[i].opis.size() < 24) izlaz << oglasi[i].opis << "\t\t";
                    else if (oglasi[i].opis.size() >= 8 && oglasi[i].opis.size() < 16) izlaz << oglasi[i].opis << "\t\t\t";
                    else izlaz << oglasi[i].opis << "\t\t\t\t";
                    izlaz << oglasi[i].cijena << "\t\t";
                    izlaz << oglasi[i].stanje << "\t\t";
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
        std::string linijaInfo;
        getline(ulaz, linijaInfo);
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
            }
            if (!promijenjeno)
            {
                std::cout << "Unijeli ste pogresan ID, pokusajte ponovo!\n";
            }
        } while (!promijenjeno);
        for (int i = 0; i < oglasi.size(); i++)
        {
            if (i != *indexElementaZaBrisanje)
            {
                noviOglasi.push_back(oglasi[i]);
            }
        }
    	std::ofstream izlaz("pomocniOglasi.txt", std::ios::app);
    	if (izlaz.is_open()) {
            izlaz << "ID\tUsername\tNaslov\t\t\t\tOpis\t\t\t\tCijena\t\tStanje\t\tKategorija\n";
    		for (int i = 0; i < noviOglasi.size(); i++)
    		{
                izlaz << noviOglasi[i].id << "\t";
                if (noviOglasi[i].autor.size() >= 8) izlaz << noviOglasi[i].autor << "\t";
                else izlaz << noviOglasi[i].autor << "\t\t";
                if (noviOglasi[i].naslov.size() >= 24) izlaz << noviOglasi[i].naslov << "\t";
                else if (noviOglasi[i].naslov.size() >= 16 && noviOglasi[i].naslov.size() < 24) izlaz << noviOglasi[i].naslov << "\t\t";
                else if (noviOglasi[i].naslov.size() >= 8 && noviOglasi[i].naslov.size() < 16) izlaz << noviOglasi[i].naslov << "\t\t\t";
                else izlaz << noviOglasi[i].naslov << "\t\t\t\t";
                if (noviOglasi[i].opis.size() >= 24) izlaz << noviOglasi[i].opis << "\t";
                else if (noviOglasi[i].opis.size() >= 16 && noviOglasi[i].opis.size() < 24) izlaz << noviOglasi[i].opis << "\t\t";
                else if (noviOglasi[i].opis.size() >= 8 && noviOglasi[i].opis.size() < 16) izlaz << noviOglasi[i].opis << "\t\t\t";
                else izlaz << noviOglasi[i].opis << "\t\t\t\t";
                izlaz << noviOglasi[i].cijena << "\t\t";
                izlaz << noviOglasi[i].stanje << "\t\t";
                izlaz << noviOglasi[i].kategorija << "\n";
    		}
    		izlaz.close();
            std::cout << "Oglas sa ID-om: " << oglasi[*indexElementaZaBrisanje].getID() << " je uspjesno uklonjen\n";
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
                unos << "ID\tGodiste\t\tKilovati\tBroj brzina\tKilometraza\tBoja\t\tTip\t\tVrsta goriva\n";
                for (int i = 0; i < vozila.size(); i++)
                {
                    if (vozila[i].getID() != oglasi[*indexElementaZaBrisanje].getID())
                    {
                        unos << vozila[i].getID() << "\t";
                        unos << vozila[i].getGodiste() << "\t\t";
                        unos << vozila[i].getKilovati() << "\t\t";
                        unos << vozila[i].getBrBrzina() << "\t\t";
                        unos << vozila[i].getKilometraza() << "\t\t";
                        if(vozila[i].getBoja().size() >= 8) unos << vozila[i].getBoja() << "\t";
                        else unos << vozila[i].getBoja() << "\t\t";
                        if(vozila[i].getTip().size() >= 8) unos << vozila[i].getTip() << "\t";
                        else unos << vozila[i].getTip() << "\t\t";
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
                unos << "ID\tVrsta\tKvadrati\tBroj soba\tBroj spratova\tGrad\t\tUlica\n";
                for (int i = 0; i < nekretnine.size(); i++)
                {
                    if (nekretnine[i].getID() != oglasi[*indexElementaZaBrisanje].getID())
                    {
                        unos << nekretnine[i].getID() << "\t";
                        unos << nekretnine[i].getVrstaNekretine() << "\t";
                        unos << nekretnine[i].getKvadrati() << "\t\t";
                        unos << nekretnine[i].getBrSoba() << "\t\t";
                        unos << nekretnine[i].getBrSpratova() << "\t\t";
                        if(nekretnine[i].getGrad().size() >= 8) unos << nekretnine[i].getGrad() << "\t";
                        else unos << nekretnine[i].getGrad() << "\t\t";
                        unos << nekretnine[i].getUlica() << "\n";
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
                unos << "ID\tVrsta\tRAM\tPohrana(GB)\tProcesor\tProizvodjac\tOS\n";
                for (int i = 0; i < tehnika.size(); i++)
                {
                    if (tehnika[i].getID() != oglasi[*indexElementaZaBrisanje].getID())
                    {
                        unos << tehnika[i].getID() << "\t";
                        unos << tehnika[i].getVrstaTehnike()  << "\t";
                        unos << tehnika[i].getRam() << "\t";
                        unos << tehnika[i].getPohrana() << "\t\t";
                        if(tehnika[i].getProcesor().size() >= 8) unos << tehnika[i].getProcesor() << "\t";
                        else unos << tehnika[i].getProcesor() << "\t\t";
                        if(tehnika[i].getProizvodjac().size() >= 8) unos << tehnika[i].getProizvodjac() << "\t";
                        else unos << tehnika[i].getProizvodjac() << "\t\t";
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
        std::string linijaInfo;
        getline(ispis, linijaInfo);
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

void Oglas::ispisOglasa(std::vector<Oglas> oglasi)
{
    std::cout << "ID\tUsername\t\tNaslov\t\t\tOpis\t\t\tCijena\t\tStanje\t\tKategorija\n";
    for (int i = 0; i < oglasi.size(); i++) {
        std::cout << oglasi[i].id << "\t";
        if (oglasi[i].autor.size() >= 8) std::cout << oglasi[i].autor << "\t";
        else std::cout << oglasi[i].autor << "\t\t";
        if (oglasi[i].naslov.size() >= 24) std::cout << oglasi[i].naslov << "\t";
        else if (oglasi[i].naslov.size() >= 16 && oglasi[i].naslov.size() < 24) std::cout << oglasi[i].naslov << "\t\t";
        else if (oglasi[i].naslov.size() >= 8 && oglasi[i].naslov.size() < 16) std::cout << oglasi[i].naslov << "\t\t\t";
        else std::cout << oglasi[i].naslov << "\t\t\t\t";
        if (oglasi[i].opis.size() >= 24) std::cout << oglasi[i].opis << "\t";
        else if (oglasi[i].opis.size() >= 16 && oglasi[i].opis.size() < 24) std::cout << oglasi[i].opis << "\t\t";
        else if (oglasi[i].opis.size() >= 8 && oglasi[i].opis.size() < 16) std::cout << oglasi[i].opis << "\t\t\t";
        else std::cout << oglasi[i].opis << "\t\t\t\t";
        std::cout << oglasi[i].cijena << "\t\t";
        std::cout << oglasi[i].stanje << "\t\t";
        std::cout << oglasi[i].kategorija;
        std::cout << std::endl;
    }
}

void Oglas::ispisOglasaDetaljno(std::vector<Oglas> oglasi, int ID)
{
    int indexZaIspis;
    for (int i = 0; i < oglasi.size(); i++) {
        if (oglasi[i].getID() == ID) {
            indexZaIspis = i;
        }
    }
    switch (oglasi[indexZaIspis].getKategorija())
    {
        case vozilo: {
            auto tempVozilo = std::make_shared<Vozilo>();
            std::vector<Vozilo> vozila = tempVozilo->getVozila();
            std::cout << "ID\tGodiste\t\tKilovati\tBroj brzina\tKilometraza\tBoja\t\tTip\t\tVrsta goriva\n";
            for (int i = 0; i < vozila.size(); i++)
            {
                if (vozila[i].getID() == oglasi[indexZaIspis].getID())
                {
                    std::cout << vozila[i].getID() << "\t";
                    std::cout << vozila[i].getGodiste() << "\t\t";
                    std::cout << vozila[i].getKilovati() << "\t\t";
                    std::cout << vozila[i].getBrBrzina() << "\t\t";
                    std::cout << vozila[i].getKilometraza() << "\t\t";
                    if (vozila[i].getBoja().size() >= 8) std::cout << vozila[i].getBoja() << "\t";
                    else std::cout << vozila[i].getBoja() << "\t\t";
                    if (vozila[i].getTip().size() >= 8) std::cout << vozila[i].getTip() << "\t";
                    else std::cout << vozila[i].getTip() << "\t\t";
                    std::cout << vozila[i].getVrstaGoriva() << "\n";
                }
            }
        }
        case nekretnina: {
            auto tempNekretnina = std::make_shared<Nekretnina>();
            std::vector<Nekretnina> nekretnine = tempNekretnina->getNekretnine();
            std::cout << "ID\tVrsta\tKvadrati\tBroj soba\tBroj spratova\tGrad\t\tUlica\n";
            for (int i = 0; i < nekretnine.size(); i++)
            {
                if (nekretnine[i].getID() == oglasi[indexZaIspis].getID())
                {
                    std::cout << nekretnine[i].getID() << "\t";
                    std::cout << nekretnine[i].getVrstaNekretine() << "\t";
                    std::cout << nekretnine[i].getKvadrati() << "\t\t";
                    std::cout << nekretnine[i].getBrSoba() << "\t\t";
                    std::cout << nekretnine[i].getBrSpratova() << "\t\t";
                    if (nekretnine[i].getGrad().size() >= 8) std::cout << nekretnine[i].getGrad() << "\t";
                    else std::cout << nekretnine[i].getGrad() << "\t\t";
                    std::cout << nekretnine[i].getUlica() << "\n";
                }
            }
        }
        case tehnika: {
            auto tempTehnika = std::make_shared<Tehnika>();
            std::vector<Tehnika> tehnika = tempTehnika->getTehnike();
            std::cout << "ID\tVrsta\tRAM\tPohrana(GB)\tProcesor\tProizvodjac\tOS\n";
            for (int i = 0; i < tehnika.size(); i++)
            {
                if (tehnika[i].getID() == oglasi[indexZaIspis].getID())
                {
                    std::cout << tehnika[i].getID() << "\t";
                    std::cout << tehnika[i].getVrstaTehnike() << "\t";
                    std::cout << tehnika[i].getRam() << "\t";
                    std::cout << tehnika[i].getPohrana() << "\t\t";
                    if (tehnika[i].getProcesor().size() >= 8) std::cout << tehnika[i].getProcesor() << "\t";
                    else std::cout << tehnika[i].getProcesor() << "\t\t";
                    if (tehnika[i].getProizvodjac().size() >= 8) std::cout << tehnika[i].getProizvodjac() << "\t";
                    else std::cout << tehnika[i].getProizvodjac() << "\t\t";
                    std::cout << tehnika[i].getOperativniSistem() << "\n";
                }
            }
        }
    }
}

bool Oglas::trebaBrisati(int kategorija)
{
    if (this->kategorija != kategorija) {
        return true;
    }
}

void Oglas::filtrirajPoCijeni(std::vector<Oglas> &oglasi)
{
    int minCijena;
    int maxCijena;
    std::cout << "Unesite minimalnu cijenu: ";
    std::cin >> minCijena;
    std::cout << "Unesite maksimalnu cijenu: ";
    std::cin >> maxCijena;
    std::vector<Oglas> noviVektor;
    for (int i = 0; i < oglasi.size(); i++) {
        if (oglasi[i].cijena < minCijena || oglasi[i].cijena > maxCijena) {
            continue;
        }
        else {
            noviVektor.push_back(oglasi[i]);
        }
    }
    oglasi = noviVektor;
}

void Oglas::filtrirajPoKategoriji(std::vector<Oglas> &oglasi)
{
    int kategorija;
    std::cout << "Unesite broj kategorije koju zelite vidjeti (1 - vozila, 2 - nekretnine, 3 - tehnika): ";
    std::cin >> kategorija;
    std::vector<Oglas> noviVektor;
    for (int i = 0; i < oglasi.size(); i++) {
        if (oglasi[i].getKategorija() != kategorija) {
            continue;
        }
        else {
            noviVektor.push_back(oglasi[i]);
        }
    }
    oglasi = noviVektor;
}

void Oglas::sortirajPoCijeniRastuci(std::vector<Oglas> &oglasi)
{
    for (int i = 0; i < oglasi.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (oglasi[i].cijena < oglasi[j].cijena) {
                std::swap(oglasi[i], oglasi[j]);
            }
        }
    }
}

void Oglas::sortirajPoCijeniOpadajuci(std::vector<Oglas> &oglasi)
{
    for (int i = 0; i < oglasi.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (oglasi[i].cijena > oglasi[j].cijena) {
                std::swap(oglasi[i], oglasi[j]);
            }
        }
    }
}

void Oglas::pretragaPoRijeci(std::vector<Oglas> &oglasi)
{
    std::string rijec;
    std::cout << "Unesite kljucnu rijec za pretragu: ";
    std::cin >> rijec;
    std::cin.ignore();
    std::vector<Oglas> noviVektor;
    for (int i = 0; i < oglasi.size(); i++) {
        if (oglasi[i].naslov.find(rijec) == std::string::npos) {
            continue;
        }
        else {
            noviVektor.push_back(oglasi[i]);
        }
    }
    oglasi = noviVektor;
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
            if (o.autor.size() >= 8) izlaz << o.autor << "\t";
            else izlaz << o.autor << "\t\t";
            if (o.naslov.size() >= 24) izlaz << o.naslov << "\t";
            else if (o.naslov.size() >= 16 && o.naslov.size() < 24) izlaz << o.naslov << "\t\t";
            else if (o.naslov.size() >= 8 && o.naslov.size() < 16) izlaz << o.naslov << "\t\t\t";
            else izlaz << o.naslov << "\t\t\t\t";
            if (o.opis.size() >= 24) izlaz << o.opis << "\t";
            else if (o.opis.size() >= 16 && o.opis.size() < 24) izlaz << o.opis << "\t\t";
            else if (o.opis.size() >= 8 && o.opis.size() < 16) izlaz << o.opis << "\t\t\t";
            else izlaz << o.opis << "\t\t\t\t";
            izlaz << o.cijena << "\t\t";
            izlaz << o.stanje << "\t\t";
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


