#include "Nekretnina.h"
#include <iostream>
#include <fstream>

Nekretnina::Nekretnina()
{
}

Nekretnina::Nekretnina(std::string a, Kategorija k) : Oglas()
{
    this->kvadrati = 100;
    this->brSoba = 3;
    this->brSpratova = 1;
    this->grad = "Sarajevo";
    this->ulica = "Ulica programera";
    this->vrstaNekret = stan;
    this->autor = a;
    this->kategorija = k;
}

void Nekretnina::setKvadrati()
{
    
    do {
        std::cout << "Unesite broj kvadrata: ";
        std::cin >> this->kvadrati;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->kvadrati < 1) std::cout << "[GRESKA] Uneseni parametar mora biti pozitivan broj!\n";
    } while (this->kvadrati<1);
    std::cin.ignore();
}

void Nekretnina::setBrSoba()
{
    do {
        std::cout << "Unesite broj soba: ";
        std::cin >> this->brSoba;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->brSoba < 1) std::cout << "[GRESKA] Uneseni parametar mora biti pozitivan broj!\n";
    } while (this->brSoba < 1);
    std::cin.ignore();
}

void Nekretnina::setBrSpratova()
{
    do {
        std::cout << "Unesite broj spratova: ";
        std::cin >> this->brSpratova;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (this->brSpratova < 1) std::cout << "[GRESKA] Uneseni parametar mora biti pozitivan broj!\n";
    } while (this->brSpratova < 1);
    std::cin.ignore();
}

void Nekretnina::setGrad()
{
    std::cout << "Unesite naziv grada: ";
    getline(std::cin, this->grad);
    for (int i = 0; i < this->grad.length(); i++)
    {
        if (this->grad[i] == 32) this->grad[i] = 95;
    }
}

void Nekretnina::setUlica()
{
    std::cout << "Unesite adresu: ";
    getline(std::cin, this->ulica);
    for (int i = 0; i < this->ulica.length(); i++)
    {
        if (this->ulica[i] == 32) this->ulica[i] = 95;
    }
}

void Nekretnina::setVrstaNekretnine()
{
    std::shared_ptr<int> izbor = std::make_shared<int>();
    do
    {
        std::cout << "Unesite vrstu nekretnine (1. Kuca 2. Stan 3.Vikendica 4. Apartman): ";
        std::cin >> *izbor;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (*izbor < 1 || *izbor >4) std::cout << "Neispravan unos, probajte ponovo!\n";
    } while (*izbor < 1 || *izbor > 4);
    this->vrstaNekret = static_cast<vrstaNekretnine>(*izbor);
    std::cin.ignore();
}

int Nekretnina::getKvadrati()
{
    return this->kvadrati;
}

int Nekretnina::getBrSoba()
{
    return this->brSoba;
}

int Nekretnina::getBrSpratova()
{
    return this->brSpratova;
}

std::string Nekretnina::getGrad()
{
    return this->grad;
}

std::string Nekretnina::getUlica()
{
    return this->ulica;
}

std::string Nekretnina::getVrstaNekretnineString()
{
    switch (this->vrstaNekret) {
    case kuca:
        return "kuca";
    case stan:
        return "stan";
    case vikendica:
        return "vikendica";
    case apartman:
        return "apartman";
    default:
        return "Greska";
    }
}

vrstaNekretnine Nekretnina::getVrstaNekretine()
{
    return this->vrstaNekret;
}

const std::vector<Nekretnina> Nekretnina::getNekretnine() const
{
    std::vector<Nekretnina> nekretnine;
    auto tempNekretnina = std::make_shared<Nekretnina>();
    try {
        std::ifstream ulaz("nekretnine.txt", std::ios::app);
        if (ulaz.is_open()) {
            int vrsta;
            std::string linijaInfo;
            getline(ulaz, linijaInfo);
            while (ulaz >> tempNekretnina->id >> vrsta >> tempNekretnina->kvadrati >> tempNekretnina->brSoba >> tempNekretnina->brSpratova >> tempNekretnina->grad >> tempNekretnina->ulica)
            {
                tempNekretnina->vrstaNekret = static_cast<vrstaNekretnine>(vrsta);
                nekretnine.push_back(*tempNekretnina);
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
    
    return nekretnine;

}

void Nekretnina::unosOglasa()
{
    this->setVrstaNekretnine();
    this->setKvadrati();
    this->setBrSoba();
    this->setBrSpratova();
    this->setGrad();
    this->setUlica();

    try {
        std::ofstream izlaz("nekretnine.txt", std::ios::app);
        if (izlaz.is_open()) {
            izlaz << this->getID() << "\t";
            izlaz << this->getVrstaNekretine() << "\t";
            izlaz << this->getKvadrati() << "\t\t";
            izlaz << this->getBrSoba() << "\t\t";
            izlaz << this->getBrSpratova() << "\t\t";
            if (this->getGrad().size() >= 8) izlaz << this->getGrad() << "\t";
            else izlaz << this->getGrad() << "\t\t";
            izlaz << this->getUlica() << "\n";
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
