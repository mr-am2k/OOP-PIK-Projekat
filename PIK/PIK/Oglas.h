#pragma once
#include<iostream>
#include "Korisnik.h"
enum Stanje {
	nedostupno=1, dostupno
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
	const int getBrojAktivnihOglasa() const;
	const int getBrojNedostupnihOglasa() const;
	const std::vector<Oglas> getOglasi() const;
	void mojiOglasi(Korisnik& tempKorisnik);
	void promijeniStanjeOglasa(Korisnik& tempKorisnik);
	void izbrisiOglas(Korisnik& tempKorisnik);
	int generisiRandomID();
	bool provjeriID(int a);
	void ispisOglasa(std::vector<Oglas> oglasi);
	void ispisOglasaDetaljno(std::vector<Oglas> oglasi, int ID);
	bool trebaBrisati(int kategorija);
	void filtrirajPoCijeni(std::vector<Oglas> &oglasi);
	void filtrirajPoKategoriji(std::vector<Oglas> &oglasi);
	void sortirajPoCijeniRastuci(std::vector<Oglas> &oglasi);
	void sortirajPoCijeniOpadajuci(std::vector<Oglas> &oglasi);
	void pretragaPoRijeci(std::vector<Oglas> &oglasi);
	friend std::istream& operator>>(std::istream& unos, Oglas& o);
	virtual void unosOglasa();
	virtual ~Oglas() = default;
};

