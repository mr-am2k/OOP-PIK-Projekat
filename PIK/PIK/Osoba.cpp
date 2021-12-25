#include "Osoba.h"
#include <iostream>
#include <conio.h>
Osoba::Osoba()
{
	this->ime = "Niko";
	this->prezime = "Kovac";
	this->username = "n1ko";
	this->sifra = "deagle";
	this->email = "nikokovac@gmail.com";
	this->brojTelefona = "061123456";
	this->spol = musko;
}

const std::string Osoba::getIme() const
{
	return this->ime;
}

const std::string Osoba::getPrezime() const
{
	return this->prezime;
}

const std::string Osoba::getUsername() const
{
	return this->username;
}

const std::string Osoba::getSifra() const
{
	return this->sifra;
}

const std::string Osoba::getEmail() const
{
	return this->email;
}

const std::string Osoba::getBrojTelefona() const
{
	return this->brojTelefona;
}

const Spol Osoba::getSpol() const
{
	return this->spol;
}

const std::string Osoba::getSpolString() const
{
	switch (this->spol) {
	case 0:
		return "musko";
	case 1:
		return "zensko";
	default:
		return "[GRESKA]";
	}
}

std::string Osoba::skrivenaSifra(std::string s, char znak = 'a')
{
	sifra.clear();
	while (znak = _getch()) {
		if (znak == 13) { //ako se pritisne enter vraca unesenu sifru
			return sifra;
		}
		else if (znak == 8 && sifra.size() != 0) { //ako se pritisne backspace brise zadnji karakter
			sifra.erase(sifra.size() - 1);
			std::cout << "\b \b"; //unos se vraca za jedno mjesto unazad
			continue;
		}
		else if (znak == 8 && sifra.size() == 0) { //ako se pritisne backspace kad nema nikakvog unosa
			continue;
		}
		sifra += znak;
		std::cout << "*";
	}
}



