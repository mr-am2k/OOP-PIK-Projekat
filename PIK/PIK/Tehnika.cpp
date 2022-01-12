#include "Tehnika.h"
#include<iostream>
#include <fstream>

Tehnika::Tehnika()
{
}

Tehnika::Tehnika(std::string a, Kategorija k) : Oglas()
{
    this->ram = 1;
    this->pohrana = 256;
    this->proizvodjac = "Acer";
    this->procesor = "Intel";
    this->operativniSistem = "Windows";
    this->vrstaTeh = laptop;
    this->autor = a;
    this->kategorija = k;
}

void Tehnika::setRam()
{
    do {
        std::cout << "Unesite kolicinu RAM-a(MB): ";
        std::cin >> this->ram;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->ram < 1) std::cout << "[GRESKA] Uneseni parametar mora biti pozitivan broj!\n";
    } while (this->ram < 1);
    std::cin.ignore();
}

void Tehnika::setPohrana()
{
    do {
        std::cout << "Unesite kolicinu memorije za pohranu(GB): ";
        std::cin >> this->pohrana;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->pohrana < 1) std::cout << "[GRESKA] Uneseni parametar mora biti pozitivan broj!\n";
    } while (this->pohrana < 1);
    std::cin.ignore();
}

void Tehnika::setProizvodjac()
{
    std::cout << "Unesite naziv proizvodjaca: ";
    getline(std::cin, this->proizvodjac);
    for (int i = 0; i < this->proizvodjac.length(); i++)
    {
        if (this->proizvodjac[i] == 32) this->proizvodjac[i] = 95;
    }
}

void Tehnika::setProcesor()
{
    std::cout << "Unesite naziv i model procesora: ";
    getline(std::cin, this->procesor);
    for (int i = 0; i < this->procesor.length(); i++)
    {
        if (this->procesor[i] == 32) this->procesor[i] = 95;
    }
}

void Tehnika::setOperativniSistem()
{
    std::cout << "Unesite naziv operativnog sistema: ";
    getline(std::cin, this->operativniSistem);
    for (int i = 0; i < this->operativniSistem.length(); i++)
    {
        if (this->operativniSistem[i] == 32) this->operativniSistem[i] = 95;
    }
}

void Tehnika::setVrstaTehnike()
{
    std::shared_ptr<int> izbor = std::make_shared<int>();
    do
    {
        std::cout << "Unesite vrstu tehnike (1. Laptop 2. Racunar 3. Mobitel): ";
        std::cin >> *izbor;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (*izbor < 1 || *izbor >3) std::cout << "Neispravan unos, probajte ponovo!\n";
    } while (*izbor < 1 || *izbor > 3);
    this->vrstaTeh = static_cast<vrstaTehnike>(*izbor);
    std::cin.ignore();
}

int Tehnika::getRam()
{
    return this->ram;
}

int Tehnika::getPohrana()
{
    return this->pohrana;
}

std::string Tehnika::getProizvodjac()
{
    return this->proizvodjac;
}

std::string Tehnika::getProcesor()
{
    return this->procesor;
}

std::string Tehnika::getOperativniSistem()
{
    return this->operativniSistem;
}

std::string Tehnika::getVrstaTehnikeString()
{
    switch (this->vrstaTeh) {
    case laptop:
        return "laptop";
    case racunar:
        return "racunar";
    case mobitel:
        return "mobitel";
    default:
        return "Greska";
    }
}

vrstaTehnike Tehnika::getVrstaTehnike()
{
    return this->vrstaTeh;
}

const std::vector<Tehnika> Tehnika::getTehnike() const
{
    std::vector<Tehnika> tehnika;
    auto tempTehnika = std::make_shared<Tehnika>();
    try {
        std::ifstream ulaz("tehnika.txt", std::ios::app);
        if (ulaz.is_open()) {
            int vrsta;
            std::string linijaInfo;
            getline(ulaz, linijaInfo);
            while (ulaz >> tempTehnika->id >> vrsta >> tempTehnika->ram >> tempTehnika->pohrana >> tempTehnika->procesor >> tempTehnika->proizvodjac >> tempTehnika->operativniSistem)
            {
                tempTehnika->vrstaTeh = static_cast<vrstaTehnike>(vrsta);
                tehnika.push_back(*tempTehnika);
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

    return tehnika;
}

void Tehnika::unosOglasa()
{
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "\t*** UNOS DETALJNIH INFORMACIJA TEHNIKE ***\n";
    std::cout << "--------------------------------------------------------------\n";
    this->setVrstaTehnike();
    this->setRam();
    this->setPohrana();
    this->setProcesor();
    this->setProizvodjac();
    this->setOperativniSistem();
    //unos podataka u datoteku
    try {
        std::ofstream izlaz("tehnika.txt", std::ios::app);
        if (izlaz.is_open()) {
            izlaz << this->getID() << "\t";
            izlaz << this->getVrstaTehnike() << "\t";
            izlaz << this->getRam() << "\t";
            izlaz << this->getPohrana() << "\t\t";
            if (this->getProcesor().size() >= 8) izlaz << this->getProcesor() << "\t";
            else izlaz << this->getProcesor() << "\t\t";
            if (this->getProizvodjac().size() >= 8) izlaz << this->getProizvodjac() << "\t";
            else izlaz << this->getProizvodjac() << "\t\t";
            izlaz << this->getOperativniSistem() << "\n";
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
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "\t*** USPJESNO STE DODALI NOVI OGLAS ***\n";
    std::cout << "--------------------------------------------------------------\n";
}
