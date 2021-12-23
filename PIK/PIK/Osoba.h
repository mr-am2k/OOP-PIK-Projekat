#pragma once
#include <string>
class Osoba
{
protected:
	std::string ime, prezime, sifra, username, email, brojTelefona, spol;
public:
	Osoba();
	void setIme();
	void setPrezime();
	void setSifra();
	void setUsername();
	void setEmail();
	void setBrojTelefona();
	void setSpol();
	const std::string getIme() const;
	const std::string getPrezime() const;
	const std::string getSifra() const;
	const std::string getUsername() const;
	const std::string getEmail() const;
	const std::string getBrojTelefona() const;
	const std::string getSpol() const;
	~Osoba() = default;
};

