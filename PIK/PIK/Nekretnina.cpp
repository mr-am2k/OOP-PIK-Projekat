#include "Nekretnina.h"
#include <iostream>
#include <fstream>
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
        if (this->kvadrati < 1) std::cout << "Broj kvadrata mora biti veci od 1!\n";
    } while (this->kvadrati<1);
    std::cin.ignore();
}

void Nekretnina::setBrSoba()
{
    do {
        std::cout << "Unesite broj soba: ";
        std::cin >> this->brSoba;
        if (this->brSoba < 1) std::cout << "Broj soba mora biti veci od 0\n";
    } while (this->brSoba < 1);
    std::cin.ignore();
}

void Nekretnina::setBrSpratova()
{
    do {
        std::cout << "Unesite broj spratova: ";
        std::cin >> this->brSpratova;
        if (this->brSpratova < 1) std::cout << "Broj spratova mora biti veci do 1!\n";
    } while (this->brSpratova < 1);
    std::cin.ignore();
}

void Nekretnina::setGrad()
{
    std::cout << "Unesite naziv grada: ";
    getline(std::cin, this->grad);
}

void Nekretnina::setUlica()
{
    std::cout << "Unesite adresu: ";
    getline(std::cin, this->ulica);
}

void Nekretnina::setVrstaNekretnine()
{
    std::shared_ptr<int> izbor = std::make_shared<int>();
    do
    {
        std::cout << "Unesite vrstu nekretnine (1. Kuca 2. Stan 3.Vikendica 4. Apartman): ";
        std::cin >> *izbor;
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

void Nekretnina::unosOglasa()
{
    this->setKvadrati();
    this->setBrSoba();
    this->setBrSpratova();
    this->setGrad();
    this->setUlica();
    this->setVrstaNekretnine();

    try {
        std::ofstream izlaz("nekretnine.txt", std::ios::app);
        if (izlaz.is_open()) {
            izlaz << this->getID() << "\t";
            izlaz << this->getKvadrati() << "\t";
            izlaz << this->getBrSoba() << "\t";
            izlaz << this->getBrSpratova() << "\t";
            izlaz << this->getGrad() << "\t";
            izlaz << this->getUlica() << "\t";
            izlaz << this->getVrstaNekretine() << "\n";
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
