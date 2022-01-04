#pragma once
#include "Oglas.h"
enum vrstaTehnike {
    laptop=1, racunar, mobitel
};
class Tehnika :
    public Oglas
{
private:
    int ram, pohrana;
    std::string proizvodjac, procesor, operativniSistem;
    vrstaTehnike vrstaTeh;
public:
    Tehnika(std::string a, Kategorija k);
    void setRam();
    void setPohrana();
    void setProizvodjac();
    void setProcesor();
    void setOperativniSistem();
    void setVrstaTehnike();
    int getRam();
    int getPohrana();
    std::string getProizvodjac();
    std::string getProcesor();
    std::string getOperativniSistem();
    std::string getVrstaTehnikeString();
    vrstaTehnike getVrstaTehnike();
    void unosOglasa() override;
    ~Tehnika() = default;
};

