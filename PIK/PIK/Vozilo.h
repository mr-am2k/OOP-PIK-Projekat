#pragma once
#include "Oglas.h"
enum vrstaGoriva {
    dizel=1, benzin
};
class Vozilo :
    public Oglas
{
private: 
    int godiste, kilovati, brBrzina, kilometraza;
    std::string boja, tip;
    vrstaGoriva vrsta;
public:
    Vozilo();
    Vozilo(std::string a, Kategorija k);
    void setGodiste();
    void setKilovati();
    void setBrBrzina();
    void setKilometraza();
    void setBoja();
    void setTip();
    void setVrstaGoriva();
    int getGodiste();
    int getKilovati();
    int getBrBrzina();
    int getKilometraza();
    std::string getBoja();
    std::string getTip();
    vrstaGoriva getVrstaGoriva();
    std::string getVrstaGorivaString();
    const std::vector<Vozilo> getVozila() const;
    void unosOglasa() override;
    ~Vozilo() = default;
};

