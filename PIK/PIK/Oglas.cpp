#include "Oglas.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <fstream>

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
}

void Oglas::setOpis()
{
    std::cout << "Unesite opis oglasa: ";
    getline(std::cin, this->opis);
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
