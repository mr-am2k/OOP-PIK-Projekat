#include <iostream>
#include "Korisnik.h"
#include "Admin.h"
#include "Oglas.h"
#include "Vozilo.h"
#include <conio.h>

int main(){
	
	Korisnik k;
	Admin a;
	Oglas o;
	int izbor;
	do {
		system("cls");
		std::cout << "GLAVNI MENI\n";
		std::cout << "\t1. Registracija\n";
		std::cout << "\t2. Prijava\n";
		std::cout << "\t3. Admin prijava\n";
		std::cout << "\t4. Izlaz\n";
		std::cout << "\tUnesite vas izbor: ";
		std::cin >> izbor;
		switch (izbor) {
		case 1:
			system("cls");
			std::cin >> k;
			break;
		case 2:
			system("cls");
			if (k.prijava()) {
				int izbor2;
				do {
					std::cout << "KORISNIK MENI\n";
					std::cout << "\t1. Dodaj oglas\n";
					std::cout << "\t2. Moji oglasi\n";
					std::cout << "\t3. Promijeni stanje oglasa\n";
					std::cout << "\t4. Pretraga\n";
					std::cout << "\t5. Prikazi oglase\n";
					std::cout << "\t6. Izbrisi oglas\n";
					std::cout << "\t7. Promijeni sifru\n";
					std::cout << "\t8. Izlaz\n";
					std::cout << "\tUnesite vas izbor: ";
					std::cin >> izbor2;
					switch (izbor2) {
					case 1:
						system("cls");
						k.dodajOglas();
						break;
					case 2:
						system("cls");
						o.mojiOglasi(k);
						break;
					case 3:
						system("cls");
						o.promijeniStanjeOglasa(k);
						break;
					case 4:
						system("cls");
						int izbor3;
						do {
							std::cout << "PRETRAGA MENI\n";
							std::cout << "\t1. Filtriraj po cijeni\n";
							std::cout << "\t2. Filtriraj po kategoriji\n";
							std::cout << "\t3. Sortiraj po cijeni (min-max)\n";
							std::cout << "\t4. Sortiraj po cijeni (max-min)\n";
							std::cout << "\t5. Pretraga po kljucnoj rijeci\n";
							std::cout << "\t6. Izlaz\n";
							std::cout << "\tUnesite vas izbor: ";
							std::cin >> izbor3;
							switch (izbor3) {
							case 1:
								system("cls");

								break;
							case 2:
								system("cls");

								break;
							case 3:
								system("cls");
								
								break;
							case 4:
								system("cls");
								
								break;
							case 5:
								system("cls");

								break;
							case 6:
								std::cin.clear();
								std::cin.ignore(100, '\n');
								return 0;
							}
							std::cout << "\nPritisnite bilo koju tipku za nastavak";
							_getch();
						} while (izbor3!=6);
						break;
					case 5:
						system("cls");

						break;
					case 6:
						system("cls");
						o.izbrisiOglas(k);
						break;
					case 7:
						system("cls");

						break;
					case 8:
						std::cin.clear();
						std::cin.ignore(100, '\n');
						return 0;
					}
					std::cout << "\nPritisnite bilo koju tipku za nastavak";
					_getch();
				} while (izbor2 != 8);
			}
			break;
		case 3:
			system("cls");
			if (a.prijava()) {
				int izbor3;
				do {
					system("cls");
					std::cout << "ADMIN MENI\n";
					std::cout << "\t1. Ispis stanja\n";
					std::cout << "\t2. Pretrazi informacije o korisniku\n";
					std::cout << "\t3. Izlaz\n";
					std::cout << "\tUnesite vas izbor: ";
					std::cin >> izbor3;
					switch (izbor3) {
					case 1:
						system("cls");
						a.ispisStanja();
						break;
					case 2:
						system("cls");
						a.infoOKorisniku();
						break;
					case 3:
						std::cin.clear();
						std::cin.ignore(100, '\n');
						return 0;
					}
					std::cout << "\nPritisnite bilo koju tipku za nastavak";
					_getch();
				} while (izbor3 != 5);
			}
			break;
		case 4:
			std::cin.clear();
			std::cin.ignore(100, '\n');
			return 0;
		}
	} while (izbor != 4);

	return 0;

}
