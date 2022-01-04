#include "Tehnika.h"
#include<iostream>
#include <fstream>

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
        if (this->ram < 1) std::cout << "RAM mora biti veci od 1 MB!\n";
    } while (this->ram < 1);
    std::cin.ignore();
}

void Tehnika::setPohrana()
{
    do {
        std::cout << "Unesite kolicinu memorije za pohranu(GB): ";
        std::cin >> this->pohrana;
        if (this->pohrana < 1) std::cout << "Pohrana mora biti veca od 1 GB!\n";
    } while (this->pohrana < 1);
    std::cin.ignore();
}

void Tehnika::setProizvodjac()
{
    std::cout << "Unesite naziv proizvodjaca: ";
    getline(std::cin, this->proizvodjac);
}

void Tehnika::setProcesor()
{
    std::cout << "Unesite naziv i model procesora: ";
    getline(std::cin, this->procesor);
}

void Tehnika::setOperativniSistem()
{
    std::cout << "Unesite naziv operativnog sistema: ";
    getline(std::cin, this->operativniSistem);
}

void Tehnika::setVrstaTehnike()
{
    std::shared_ptr<int> izbor = std::make_shared<int>();
    do
    {
        std::cout << "Unesite vrstu tehnike (1. Laptop 2. Racunar 3. Mobitel): ";
        std::cin >> *izbor;
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

void Tehnika::unosOglasa()
{
    this->setVrstaTehnike();
    this->setRam();
    this->setPohrana();
    this->setProcesor();
    this->setProizvodjac();
    this->setOperativniSistem();
    try {
        std::ofstream izlaz("tehnika.txt", std::ios::app);
        if (izlaz.is_open()) {
            izlaz << this->getID() << "\t";
            izlaz << this->getVrstaTehnike() << "\t";
            izlaz << this->getRam()<< "\t";
            izlaz << this->getPohrana() << "\t";
            izlaz << this->getProcesor() << "\t";
            izlaz << this->getProizvodjac()<< "\t";
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

}
