#pragma once
#include "Oglas.h"
enum vrstaNekretnine {
    kuca=1, stan, vikendica, apartman
};
class Nekretnina :
    public Oglas
{
private:
    int kvadrati, brSoba, brSpratova;
    std::string grad, ulica;
    vrstaNekretnine vrstaNekret;
public:
    Nekretnina();
    Nekretnina(std::string a, Kategorija k);
    void setKvadrati();
    void setBrSoba();
    void setBrSpratova();
    void setGrad();
    void setUlica();
    void setVrstaNekretnine();
    int getKvadrati();
    int getBrSoba();
    int getBrSpratova();
    std::string getGrad();
    std::string getUlica();
    std::string getVrstaNekretnineString();
    vrstaNekretnine getVrstaNekretine();
    const std::vector<Nekretnina> getNekretnine() const;
    void unosOglasa() override;
    ~Nekretnina() = default;
};

