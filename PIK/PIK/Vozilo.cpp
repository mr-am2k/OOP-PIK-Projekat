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
    do {
        std::cout << "Unesite godiste vozila: ";
        std::cin >> this->godiste;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->godiste < 1900 || this->godiste > 2022) std::cout << "[GRESKA] Uneseni parametar mora biti broj u rasponu 1900 - 2022.\n";
    } while (this->godiste < 1900 || this->godiste > 2022);
    std::cin.ignore();
}

void Vozilo::setKilovati()
{
    do {
        std::cout << "Unesite kilovate: ";
        std::cin >> this->kilovati;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->kilovati < 1) std::cout << "[GRESKA] Uneseni parametar mora biti broj veci od 1!\n";
    } while (this->kilovati<1);
    std::cin.ignore();
}

void Vozilo::setBrBrzina()
{
    do {
        std::cout << "Unesite broj brzina: ";
        std::cin >> this->brBrzina;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->brBrzina < 1) std::cout << "[GRESKA] Uneseni parametar mora biti broj veci od 0!\n";
    } while (this->brBrzina < 1);
    std::cin.ignore();
}

void Vozilo::setKilometraza()
{
    do {
        std::cout << "Unesite broj kilometara: ";
        std::cin >> this->kilometraza;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->kilometraza < 0) std::cout << "[GRESKA] Uneseni parametar mora biti broj koji je ne-negativan!\n";
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
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
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
            std::string linijaInfo;
            getline(ulaz, linijaInfo);
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
            izlaz << this->getGodiste() << "\t\t";
            izlaz << this->getKilovati() << "\t\t";
            izlaz << this->getBrBrzina() << "\t\t";
            izlaz << this->getKilometraza() << "\t\t";
            if (this->getBoja().size() >= 8) izlaz << this->getBoja() << "\t";
            else izlaz << this->getBoja() << "\t\t";
            if (this->getTip().size() >= 8) izlaz << this->getTip() << "\t";
            else izlaz << this->getTip() << "\t\t";
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
