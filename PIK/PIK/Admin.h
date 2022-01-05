#pragma once
#include "Osoba.h"
class Admin :
    public Osoba
{
private:
    int kod;
public:
    Admin();
    const int getKod() const;
    bool prijava() override;
    void ucitajAdmine();
    void ispisStanja(); //Ispisuje koliko je trenutno korisnika registrovano, koliko je aktivnih oglasa, zvrsenih oglasa, ukupno oglasa
    void infoOKorisniku();
    ~Admin() = default;
};

