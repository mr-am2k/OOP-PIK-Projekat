#pragma once
#include<iostream>
#include "Korisnik.h"
enum Stanje {
	nedostupno, dostupno
};
enum Kategorija {
	vozilo=1, nekretnina, tehnika 
};
class Oglas
{
protected:
	int id;
	std::string autor, naslov, opis;
	float cijena;
	Stanje stanje;
	Kategorija kategorija;
public:
	Oglas();
	void setID();
	void setNaslov();
	void setOpis();
	void setCijena();
	void setStanje();
	void setKategorija();
	int getID();
	std::string getAutor();
	std::string getNaslov();
	std::string getOpis();
	Kategorija getKategorija();
	float getCijena();
	Stanje getStanje();
	std::string getStanjeString();
	std::string getKategorijaString();
	int generisiRandomID();
	bool provjeriID(int a);
	friend std::istream& operator>>(std::istream& unos, Oglas& o);
	virtual void unosOglasa();
	virtual ~Oglas() = default;
};

