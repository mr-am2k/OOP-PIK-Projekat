#include "Vozilo.h"
#include <iostream>
#include <fstream>

Vozilo::Vozilo()
{
    this->godiste = 2009;
    this->kilovati = 100;
    this->brBrzina = 6;
    this->kilometraza = 200000;
    this->boja = "Crna";
    this->tip = "Limuzina";
    this->vrsta = dizel;
    this->autor = "Niko";
    this->kategorija = vozilo;
}

Vozilo::Vozilo(std::string a, Kategorija k) : Oglas()
{
    this->godiste = 2009;
    this->kilovati = 100;
    this->brBrzina = 6;
    this->kilometraza = 200000;
    this->boja = "Crna";
    this->tip = "Limuzina";
    this->vrsta = dizel;
    this->autor = a;
    this->kategorija = k;
}

void Vozilo::setGodiste()
{
    std::cout << "Unesite godiste vozila: ";
    do {
        std::cin >> this->godiste;
        if (this->godiste < 1900) std::cout << "Greska, godina ne moze biti ispod 1900.\n";
    } while (this->godiste < 1900);
    std::cin.ignore();
}

void Vozilo::setKilovati()
{
    std::cout << "Unesite kilovate: ";
    do {
        std::cin >> this->kilovati;
        if (this->kilovati < 1) std::cout << "Greska, kilovati moraju biti veci od 1\n";
    } while (this->kilovati<1);
    std::cin.ignore();
}

void Vozilo::setBrBrzina()
{
    std::cout << "Unesite broj brzina: ";
    do {
        std::cin >> this->brBrzina;
        if (this->brBrzina < 1) std::cout << "Greska, broj brzina mora biti veci od 0!\n";
    } while (this->brBrzina < 1);
    std::cin.ignore();
}

void Vozilo::setKilometraza()
{
    std::cout << "Unesite broj kilometara: ";
    do {
        std::cin >> this->kilometraza;
        if (this->kilometraza < 0) std::cout << "Greska, broj kilometara ne moze biti negativan!\n";
    } while (this->kilometraza < 0);
    std::cin.ignore();
}

void Vozilo::setBoja()
{
    std::cout << "Unesite boju vozila: ";
    std::cin >> this->boja;
}

void Vozilo::setTip()
{
    std::cout << "Unesite tip vozila: ";
    std::cin >> this->tip;
}

void Vozilo::setVrstaGoriva()
{
    std::shared_ptr<int> izbor = std::make_shared<int>();
    do
    {
        std::cout << "Unesite vrstu goriva (1. Dizel 2. Benzin): ";
        std::cin >> *izbor;
        if (*izbor < 1 || *izbor >2) std::cout << "Neispravan unos, probajte ponovo!\n";
    } while (*izbor < 1 || *izbor > 2);
    this->vrsta = static_cast<vrstaGoriva>(*izbor);
    std::cin.ignore();
}

int Vozilo::getGodiste()
{
    return this->godiste;
}

int Vozilo::getKilovati()
{
    return this->kilovati;
}

int Vozilo::getBrBrzina()
{
    return this->brBrzina;
}

int Vozilo::getKilometraza()
{
    return this->kilometraza;
}

std::string Vozilo::getBoja()
{
    return this->boja;
}

std::string Vozilo::getTip()
{
    return this->tip;
}

vrstaGoriva Vozilo::getVrstaGoriva()
{
    return this->vrsta;
}

std::string Vozilo::getVrstaGorivaString()
{
    switch (this->vrsta) {
    case benzin:
        return "benzin";
    case dizel:
        return "dizel";
    default:
        return "Greska";
    }
}

const std::vector<Vozilo> Vozilo::getVozila() const
{
    std::vector<Vozilo> vozila;
    auto tempVozilo = std::make_shared<Vozilo>();
    try {
        std::ifstream ulaz("vozila.txt", std::ios::app);
        if (ulaz.is_open()) {
            int gorivo;
            while(ulaz >> tempVozilo->id >> tempVozilo->godiste >> tempVozilo->kilovati>> tempVozilo->brBrzina >>  tempVozilo->kilometraza >> tempVozilo->boja >> tempVozilo->tip >> gorivo)
            {
                tempVozilo->vrsta = static_cast<vrstaGoriva>(gorivo);
                vozila.push_back(*tempVozilo);
            }
        }
        else {
            throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
        }
    }
    catch (const char* greska) {
        std::cout << greska;
        exit(0);
    }

    return vozila;
}

void Vozilo::unosOglasa()
{
    this->setGodiste();
    this->setKilovati();
    this->setBrBrzina();
    this->setKilometraza();
    this->setBoja();
    this->setTip();
    this->setVrstaGoriva();

    try {
        std::ofstream izlaz("vozila.txt", std::ios::app);
        if (izlaz.is_open()) {
            izlaz << this->getID() << "\t";
            izlaz << this->getGodiste() << "\t";
            izlaz << this->getKilovati() << "\t";
            izlaz << this->getBrBrzina() << "\t";
            izlaz << this->getKilometraza() << "\t";
            izlaz << this->getBoja() << "\t";
            izlaz << this->getTip() << "\t";
            izlaz << this->getVrstaGoriva() << "\n";
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
}
