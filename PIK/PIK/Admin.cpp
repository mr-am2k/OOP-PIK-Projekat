#include "Admin.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <Windows.h>
std::vector<Admin> admini;

Admin::Admin() : Osoba()
{
	this->kod = 0;
}

const int Admin::getKod() const
{
	return this->kod;
}

bool Admin::prijava()
{
	this->ucitajAdmine();
	char znak = 'a';
	bool postoji = false;
	int pokusaji = 0;
	do {
		if (pokusaji == 3) {
			std::cout << "Pogrijesili ste 3 puta sa unosom! Povratak na glavni meni!\n";
			Sleep(2000);
			return false;
		}
		pokusaji++;
		std::cout << "Unesite username: ";
		std::cin >> this->username;
		for (int i = 0; i < admini.size(); i++) {
			if (this->username == admini[i].getUsername()) {
				postoji = true;
				break;
			}
		}
		if (!postoji) std::cout << "[GRESKA]: Uneseni username ne postoji!\n";
	} while (!postoji);
	pokusaji = 0;
	postoji = false;
	do {
		if (pokusaji == 3) {
			std::cout << "Pogrijesili ste 3 puta sa unosom! Povratak na glavni meni!\n";
			Sleep(2000);
			return false;
		}
		pokusaji++;
		std::cout << "Unesite sifru: ";
		this->sifra = this->skrivenaSifra(this->sifra, znak);
		std::cout << std::endl;
		for (int i = 0; i < admini.size(); i++) {
			if (this->username == admini[i].getUsername() && this->sifra == admini[i].getSifra()) {
				postoji = true;
				break;
			}
		}
		if (!postoji) std::cout << "[GRESKA]: Unesena sifra ne odgovara unesenom username-u!\n";
	} while (!postoji);
	pokusaji = 0;
	postoji = false;
	do {
		if (pokusaji == 3) {
			std::cout << "Pogrijesili ste 3 puta sa unosom! Povratak na glavni meni!\n";
			Sleep(2000);
			return false;
		}
		try {
			pokusaji++;
			std::cout << "Unesite vas ADMIN kod: ";
			std::cin >> this->kod;
			if (std::cin.fail()) throw "[IZUZETAK]: Nepravilan unos varijable tipa INT!\n";
			std::cin.clear();
			std::cin.ignore();
		}
		catch (const char* greska) {
			std::cout << greska;
			return 0;
		}
		for (int i = 0; i < admini.size(); i++) {
			if (this->username == admini[i].getUsername() && this->sifra == admini[i].getSifra() && this->kod == admini[i].getKod()) {
				postoji = true;
				this->ime = admini[i].getIme();
				this->prezime = admini[i].getPrezime();
				this->email = admini[i].getEmail();
				this->brojTelefona = admini[i].getBrojTelefona();
				this->spol = admini[i].getSpol();
				break;
			}
		}
		if (!postoji) std::cout << "[GRESKA]: Uneseni ADMIN kod ne odgovara unesenom username-u i sifri!\n";
	} while (!postoji);
	return postoji;
}

void Admin::ucitajAdmine()
{
	try {
		admini.clear();
		std::ifstream ulaz("admini.txt");
		if (ulaz.is_open()) {
			std::shared_ptr<Admin> temp = std::make_shared<Admin>();
			std::string linijaInfo;
			std::string spolString;
			std::getline(ulaz, linijaInfo);
			while (ulaz >> temp->ime >> temp->prezime >> temp->username >> temp->sifra >> temp->email >> temp->brojTelefona >> spolString >> temp->kod) {
				if (spolString == "musko") temp->spol = musko;
				else temp->spol = zensko;
				admini.push_back(*temp);
			}
			ulaz.close();
		}
		else {
			throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
		}
	}
	catch (const char* greska) {
		std::cout << greska;
		exit(0);
	}
}
