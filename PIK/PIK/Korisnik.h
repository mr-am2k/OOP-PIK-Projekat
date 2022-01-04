#pragma once
#include "Osoba.h"
class Korisnik :
	public Osoba
{
private:
	int brAktivnihOglasa;
	int brZavrsenihOglasa;
public:
	Korisnik();
	void setIme();
	void setPrezime();
	void setUsername();
	void setSifra();
	void setEmail();
	void setBrojTelefona();
	void setSpol();
	const int getbrAktivnihOglasa() const;
	const int getbrZavrsenihOglasa() const;
	bool prijava() override;
	friend std::ostream& operator<<(std::ostream& izlaz, Korisnik& k);
	friend std::istream& operator>>(std::istream& ulaz, Korisnik& k);
	void ucitajKorisnike();
	void dodajOglas();
	~Korisnik() = default;
};

