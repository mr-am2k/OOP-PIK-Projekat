#pragma once
#include <string>
enum Spol{musko,zensko};
class Osoba
{
protected:
	std::string ime, prezime, username, sifra, email, brojTelefona;
	Spol spol;
public:
	Osoba();
	const std::string getIme() const;
	const std::string getPrezime() const;
	const std::string getUsername() const;
	const std::string getSifra() const;
	const std::string getEmail() const;
	const std::string getBrojTelefona() const;
	const Spol getSpol() const;
	const std::string getSpolString() const;
	virtual bool prijava() = 0;
	std::string skrivenaSifra(std::string s, char znak);
	~Osoba() = default;
};

