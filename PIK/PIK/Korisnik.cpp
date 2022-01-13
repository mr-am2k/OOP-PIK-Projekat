#include "Korisnik.h"
#include "Oglas.h"
#include "Vozilo.h"
#include "Tehnika.h"
#include "Nekretnina.h"
#include <iostream>
#include <regex> //Biblioteka regex je potreba kako bi mogli koristiti regex prilikom unosa sifre/maila/broja telefona. Na ovaj nacin nema potrebe za kompleksnom logikom da specifisemo nacin unosa nekog od spomenutih atributa
#include <fstream>
#include <Windows.h>

std::vector<Korisnik> korisnici;

Korisnik::Korisnik() : Osoba()
{
	this->brAktivnihOglasa = 0;
	this->brZavrsenihOglasa = 0;
}
void Korisnik::setIme()
{
	std::cout << "Unesite vase ime: ";
	std::cin >> this->ime;
}

void Korisnik::setPrezime()
{
	std::cout << "Unesite vase prezime: ";
	std::cin >> this->prezime;
}

void Korisnik::setUsername()
{
	this->ucitajKorisnike();
	bool postoji;
	do {
		postoji = false;
		do {
			std::cout << "Unesite username: ";
			std::cin >> this->username;
			if (this->username.size() < 3) std::cout << "Username mora biti minimalno 3 karaktera!\n";
		} while (this->username.size() < 3);
		for (int i = 0; i < korisnici.size(); i++) {
			if (this->username == korisnici[i].getUsername()) { //Iskljucujemo mogucnost da se korisnik registruje sa username-om koji vec postoji
				std::cout << "[GRESKA]: Username vec postoji!\n";
				postoji = true;
				break;
			}
		}
	} while (postoji);
}

void Korisnik::setSifra()
{
	char znak = 'a';
	const std::regex sifraPravilo("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[!@#\$%\^&_\*\+\-\.\,])(?=.{8,})");
	do {
		std::cout << "Unesite sifru: ";
		this->sifra = this->skrivenaSifra(this->sifra, znak); //Pozivom metode skrivena sifra omoguciti cemo prilikom unosa sifre da se ispisuje specijalni karakter
		std::cout << std::endl;
		if (!regex_search(this->sifra, sifraPravilo)) std::cout << "[GRESKA]: Sifra mora sadrzavati minimalno 8 karaktera!\n[GRESKA]: Mora imati mala i velika slova, broj i specijalni karakter.\n";
	} while (!regex_search(this->sifra, sifraPravilo));
}


void Korisnik::setEmail()
{
	const std::regex emailPravilo("(\\w+)(\\.|_)?(\\w*)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	do {
		std::cout << "Unesite email: ";
		std::cin >> this->email;
		if (!regex_match(this->email, emailPravilo)) std::cout << "[GRESKA]: Email mora biti u obliku primjer@naziv.nesto\n";
	} while (!regex_match(this->email, emailPravilo));
}

void Korisnik::setBrojTelefona()
{
	const std::regex brojPravilo("\\d{3}/\\d{3}-\\d{3,4}");
	do {
		std::cout << "Unesite broj telefona na sljedeci nacin(123/456-789): ";
		std::cin >> this->brojTelefona;
		if (!regex_match(this->brojTelefona, brojPravilo)) std::cout << "[GRESKA]: Broj telefona mora biti u obliku 123/456-789\n";
	} while (!regex_match(this->brojTelefona, brojPravilo));
}

void Korisnik::setSpol()
{
	std::shared_ptr<int> izbor = std::make_shared<int>();
	do
	{
		std::cout << "Unesite spol (musko: 0 | zensko: 1): ";
		std::cin >> *izbor;
		if (*izbor < 0 || *izbor > 1) std::cout << "[GRESKA]: Spol moze biti samo 0 ili 1.\n";
	} while (*izbor < 0 || *izbor > 1);
	this->spol = static_cast<Spol>(*izbor);
	std::cin.ignore();
}

const int Korisnik::getbrAktivnihOglasa() const
{
	return this->brAktivnihOglasa;
}

const int Korisnik::getbrZavrsenihOglasa() const
{
	return this->brZavrsenihOglasa;
}

const int Korisnik::getBrojKorisnika() const
{
	try {
		korisnici.clear();
		std::ifstream ulaz("korisnici.txt");
		auto brojac = std::make_shared<int>();
		*brojac = 0;
		if (ulaz.is_open()) {
			std::shared_ptr<Korisnik> temp = std::make_shared<Korisnik>();
			std::string linijaInfo;
			std::string spolString;
			std::getline(ulaz, linijaInfo);
			while (ulaz >> temp->ime >> temp->prezime >> temp->username >> temp->sifra >> temp->email >> temp->brojTelefona >> spolString >> temp->brAktivnihOglasa >> temp->brZavrsenihOglasa) {
				*brojac = *brojac + 1;
			}
			ulaz.close();
			return *brojac;
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

const std::vector<Korisnik> Korisnik::getKorisnike() const
{
	try {
		korisnici.clear();
		std::ifstream ulaz("korisnici.txt");
		if (ulaz.is_open()) {
			std::shared_ptr<Korisnik> temp = std::make_shared<Korisnik>();
			std::string linijaInfo;
			std::string spolString;
			std::getline(ulaz, linijaInfo);
			while (ulaz >> temp->ime >> temp->prezime >> temp->username >> temp->sifra >> temp->email >> temp->brojTelefona >> spolString >> temp->brAktivnihOglasa >> temp->brZavrsenihOglasa) {
				if (spolString == "musko") temp->spol = musko;
				else temp->spol = zensko;
				korisnici.push_back(*temp);
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
	return korisnici;
}

bool Korisnik::prijava()
{
	this->ucitajKorisnike();
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
		for (int i = 0; i < korisnici.size(); i++) {
			if (this->username == korisnici[i].getUsername()) {
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
		for (int i = 0; i < korisnici.size(); i++) {
			if (this->username == korisnici[i].getUsername() && this->sifra == korisnici[i].getSifra()) {
				postoji = true;
				this->ime = korisnici[i].getIme();
				this->prezime = korisnici[i].getPrezime();
				this->email = korisnici[i].getEmail();
				this->brojTelefona = korisnici[i].getBrojTelefona();
				this->spol = korisnici[i].getSpol();
				this->brAktivnihOglasa = korisnici[i].getbrAktivnihOglasa();
				this->brZavrsenihOglasa = korisnici[i].getbrZavrsenihOglasa();
				break;
			}
		}
		if (!postoji) std::cout << "[GRESKA]: Unesena sifra ne odgovara unesenom username-u!\n";
	} while (!postoji);
	return postoji;
}

void Korisnik::promijeniSifru()	//poziva setter sifre i mijenja vrijednost sifre u korisnici.txt na novu sifru
{
	this->setSifra();
	this->ucitajKorisnike();
	for (int i = 0; i < korisnici.size(); i++) {
		if (this->username == korisnici[i].getUsername()) {
			korisnici[i].sifra = this->sifra;
		}
	}
	try {
		std::ifstream unos("korisnici.txt");
		std::string temp;
		std::getline(unos, temp);
		unos.close();
		std::ofstream izlaz("korisnici.txt");
		izlaz << temp << std::endl;
		for (int i = 0; i < korisnici.size(); i++) {
			if (izlaz.is_open()) {
				if (korisnici[i].ime.size() >= 8) izlaz << korisnici[i].ime << "\t";
				else izlaz << korisnici[i].ime << "\t\t";
				if (korisnici[i].prezime.size() >= 8) izlaz << korisnici[i].prezime << "\t";
				else izlaz << korisnici[i].prezime << "\t\t";
				if (korisnici[i].username.size() >= 8) izlaz << korisnici[i].username << "\t";
				else izlaz << korisnici[i].username << "\t\t";
				if (korisnici[i].sifra.size() >= 8) izlaz << korisnici[i].sifra << "\t";
				else izlaz << korisnici[i].sifra << "\t\t";
				if (korisnici[i].email.size() >= 24) izlaz << korisnici[i].email << "\t";
				else if (korisnici[i].email.size() >= 16 && korisnici[i].email.size() < 24) izlaz << korisnici[i].email << "\t\t";
				else if (korisnici[i].email.size() >= 8 && korisnici[i].email.size() < 16) izlaz << korisnici[i].email << "\t\t\t";
				else izlaz << korisnici[i].email << "\t\t\t\t";
				izlaz << korisnici[i].brojTelefona << "\t";
				izlaz << korisnici[i].getSpolString() << "\t\t";
				izlaz << korisnici[i].brAktivnihOglasa << "\t\t";
				izlaz << korisnici[i].brZavrsenihOglasa << "\n";
			}
			else {
				throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
			}
		}
		izlaz.close();
	}
	catch (const char* greska) {
		std::cout << greska;
		exit(0);
	}

	std::cout << "Uspjesna izmjena sifre!" << std::endl;
}


void Korisnik::ucitajKorisnike()
{
	try {
		korisnici.clear();
		std::ifstream ulaz("korisnici.txt");
		if (ulaz.is_open()) {
			std::shared_ptr<Korisnik> temp = std::make_shared<Korisnik>();
			std::string linijaInfo;
			std::string spolString;
			std::getline(ulaz, linijaInfo);
			while (ulaz >> temp->ime >> temp->prezime >> temp->username >> temp->sifra >> temp->email >> temp->brojTelefona >> spolString >> temp->brAktivnihOglasa >> temp->brZavrsenihOglasa) {
				if (spolString == "musko") temp->spol = musko;
				else temp->spol = zensko;
				korisnici.push_back(*temp);
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


void Korisnik::dodajOglas()
{
	std::shared_ptr<Oglas> temp = std::make_shared<Oglas>();
	temp->setKategorija();
	std::shared_ptr<Oglas> o = nullptr;
	switch (temp->getKategorija()) {
	case vozilo: {
		o = std::make_shared<Vozilo>(this->getUsername(), temp->getKategorija());
		break;
	}
	case nekretnina: {
		o = std::make_shared<Nekretnina>(this->getUsername(), temp->getKategorija());
		break;
	}
	case tehnika: {
		o = std::make_shared<Tehnika>(this->getUsername(), temp->getKategorija());
		break;
	}
	default: {
		std::cout << "Greska!";
	}
	}
	std::cin >> *o;
	o->unosOglasa();
}



std::ostream& operator<<(std::ostream& izlaz, Korisnik& k) //Operator  << sluzi za ispis infomracija o korisniku
{
	izlaz << "--------------------------------------------------------------\n";
	izlaz << "\t\t*** INFORMACIJE O KORISNIKU ***\n";
	izlaz << "--------------------------------------------------------------\n";
	izlaz << "Ime: " << k.ime << std::endl;
	izlaz << "Prezime: " << k.prezime << std::endl;
	izlaz << "Username: " << k.username << std::endl;
	izlaz << "Sifra: " << k.sifra << std::endl;
	izlaz << "Email: " << k.email << std::endl;
	izlaz << "Broj telefona: " << k.brojTelefona << std::endl;
	izlaz << "Spol: " << k.getSpolString() << std::endl;
	izlaz << "--------------------------------------------------------------\n";
	return izlaz;
}

std::istream& operator>>(std::istream& ulaz, Korisnik& k) //Opretaor >> sluzi za registraciju novog korisnika
{
	std::cout << "--------------------------------------------------------------\n";
	std::cout << "\t\t*** REGISTRACIJA KORISNIKA ***\n";
	std::cout << "--------------------------------------------------------------\n";
	k.setIme();
	k.setPrezime();
	k.setUsername();
	k.setSifra();
	k.setEmail();
	k.setBrojTelefona();
	k.setSpol();
	try {
		std::ofstream izlaz("korisnici.txt", std::ios::app);
		if (izlaz.is_open()) {
			if (k.ime.size() >= 8) izlaz << k.ime << "\t";
			else izlaz << k.ime << "\t\t";
			if (k.prezime.size() >= 8) izlaz << k.prezime << "\t";
			else izlaz << k.prezime << "\t\t";
			if (k.username.size() >= 8) izlaz << k.username << "\t";
			else izlaz << k.username << "\t\t";
			if (k.sifra.size() >= 8) izlaz << k.sifra << "\t";
			else izlaz << k.sifra << "\t\t";
			if (k.email.size() >= 24) izlaz << k.email<< "\t";
			else if (k.email.size() >= 16 && k.email.size() < 24) izlaz << k.email << "\t\t";
			else if (k.email.size() >= 8 && k.email.size() < 16) izlaz << k.email << "\t\t\t";
			else izlaz << k.email << "\t\t\t\t";
			izlaz << k.brojTelefona << "\t";
			izlaz << k.getSpolString() << "\t\t";
			izlaz << k.brAktivnihOglasa << "\t\t";
			izlaz << k.brZavrsenihOglasa << "\n";
			izlaz.close();
		}
		else {
			throw "[IZUZETAK]: Otvaranje datoteke nije uspjelo!\n";
		}
	}
	catch (const char* greska) {
		std::cout << greska;
		exit(0);
	}
	std::cout << "--------------------------------------------------------------\n";
	std::cout << "\nUspjesno ste se registrovali...\n";
	std::cout << "--------------------------------------------------------------\n";
	Sleep(2000);
	return ulaz;
}
