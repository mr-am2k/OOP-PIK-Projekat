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
    ~Admin() = default;
};

