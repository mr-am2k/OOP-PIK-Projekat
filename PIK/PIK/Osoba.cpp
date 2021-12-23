#include "Osoba.h"
#include <iostream>
Osoba::Osoba()
{
	this->ime = "Niko";
	this->prezime = "Kovac";
	this->sifra = "deagle";
	this->username = "n1ko";
	this->email = "nikokovac@gmail.com";
	this->brojTelefona = "061123456";
	this->spol = "musko";
}

void Osoba::setIme()
{
	std::cout << "Unesite vase ime: ";
	std::cin >> this->ime;

}

void Osoba::setPrezime()
{
	std::cout << "Unesite vase prezime: ";
	std::cin >> this->prezime;
}

void Osoba::setSifra()
{
	std::cout << "Unesite sifru: ";
	std::cin >> this->sifra;
}

void Osoba::setUsername()
{
	std::cout << "Unesite username: ";
	std::cin >> this->username;
}

void Osoba::setEmail()
{
	std::cout << "Unesite email: ";
	std::cin >> this->email;
}

void Osoba::setBrojTelefona()
{
	std::cout << "Unesite broj telefona: ";
	std::cin >> this->brojTelefona;
}

void Osoba::setSpol()
{
	do
	{
		std::cout << "Unesite spol (musko/zensko): ";
		std::cin >> this->spol;
		
	} while (this->spol != "musko" || this->spol != "zensko");
}

const std::string Osoba::getIme() const
{
	return this->ime;
}

const std::string Osoba::getPrezime() const
{
	return this->prezime;
}

const std::string Osoba::getSifra() const
{
	return this->sifra;
}

const std::string Osoba::getUsername() const
{
	return this->username;
}

const std::string Osoba::getEmail() const
{
	return this->email;
}

const std::string Osoba::getBrojTelefona() const
{
	return this->brojTelefona;
}

const std::string Osoba::getSpol() const
{
	return this->spol;
}

