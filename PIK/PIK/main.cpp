#include <iostream>
#include "Korisnik.h"
#include "Admin.h"
#include "Oglas.h"
#include "Vozilo.h"
#include <conio.h>
#include <windows.h>

int glavniMenu() {
	int izbor;
	system("cls");
	std::cout << "------------------------------------------------------\n";
	std::cout << "\t\t*** GLAVNI MENU ***\n";
	std::cout << "------------------------------------------------------\n";
	std::cout << "\t1. Registracija\n";
	std::cout << "\t2. Prijava\n";
	std::cout << "\t3. Admin prijava\n";
	std::cout << "\t4. Izlaz\n";
	std::cout << "\tUnesite vas izbor: ";
	std::cin >> izbor;
	if (izbor != 4) return izbor;
	else {  
		std::cin.clear();
		std::cin.ignore(100, '\n');
		return 0;
	}
}

int korisnikMenu() {
	int izbor;
	system("cls");
	std::cout << "------------------------------------------------------\n";
	std::cout << "\t\t*** KORISNIK MENU ***\n";
	std::cout << "------------------------------------------------------\n";
	std::cout << "\t1. Dodaj oglas\n";
	std::cout << "\t2. Moji oglasi\n";
	std::cout << "\t3. Promijeni stanje oglasa\n";
	std::cout << "\t4. Pretraga\n";
	std::cout << "\t5. Prikazi oglase\n";
	std::cout << "\t6. Izbrisi oglas\n";
	std::cout << "\t7. Promijeni sifru\n";
	std::cout << "\t8. Odjava\n";
	std::cout << "\tUnesite vas izbor: ";
	std::cin >> izbor;
	if (izbor != 8) return izbor;
	else {
		std::cout << "\nUspjesno ste se odjavili!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		return 0;
	}
}

int adminMenu() {
	int izbor;
	system("cls");
	std::cout << "------------------------------------------------------\n";
	std::cout << "\t\t*** ADMIN MENU ***\n";
	std::cout << "------------------------------------------------------\n";
	std::cout << "\t1. Ispis stanja\n";
	std::cout << "\t2. Pretrazi informacije o korisniku\n";
	std::cout << "\t3. Odjava\n";
	std::cout << "\tUnesite vas izbor: ";
	std::cin >> izbor;
	if (izbor != 3) return izbor;
	else {
		std::cout << "\nUspjesno ste se odjavili!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		return 0;
	}
}

int pretragaMenu() {
	int izbor;
	system("cls");
	std::cout << "------------------------------------------------------\n";
	std::cout << "\t\t*** PRETRAGA MENU ***\n";
	std::cout << "------------------------------------------------------\n";
	std::cout << "\t1. Filtriraj po cijeni\n";
	std::cout << "\t2. Filtriraj po kategoriji\n";
	std::cout << "\t3. Sortiraj po cijeni (min-max)\n";
	std::cout << "\t4. Sortiraj po cijeni (max-min)\n";
	std::cout << "\t5. Pretraga po kljucnoj rijeci\n";
	std::cout << "\t6. Resetuj filtere\n";
	std::cout << "\t7. Nazad na korisnik meni\n";
	std::cout << "\tUnesite vas izbor: ";
	std::cin >> izbor;
	if (izbor != 7) return izbor;
	else {
		std::cin.clear();
		std::cin.ignore(100, '\n');
		return 0;
	}
}

void ispisiFiltere(bool filteri[], std::string vrijednostiFiltera[]) {	//ispisuje sve aktivne filtere na pretrazi oglasa na osnovu vrijednosit u nizovima (vrijednost: 0 - opseg cijene, 1 - kategorija, 2 - kljucna rijec)
	bool nemaAktivnihFiltera = true;
	for (int i = 0; i < 5; i++) {
		if (filteri[i] == true) nemaAktivnihFiltera = false;			//provjera da li ima aktivnih filtera, u slucaju da nema izlazi iz funkcije
	}
	if (nemaAktivnihFiltera) {
		std::cout << "Nema aktivnih filtera!" << std::endl;
		return;
	}
	std::cout << std::endl << "Aktivni filteri: " << std::endl;
	if (filteri[0]) {
		std::cout << "Filter po cijenama u opsegu: " << vrijednostiFiltera[0] << std::endl;
	}
	if (filteri[1]) {
		std::cout << "Filter po kategoriji: " << vrijednostiFiltera[1] << std::endl;
	}
	if (filteri[2]) {
		std::cout << "Cijene sortirane rastuci." << std::endl;
	}
	if (filteri[3]) {
		std::cout << "Cijene sortirane opadajuci. " << std::endl;
	}
	if (filteri[4]) {
		std::cout << "Filter po kljucnoj rijeci: " << vrijednostiFiltera[2] << std::endl;
	}
	
	
}

int main(){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //smjestaju se vrijednosti trenutnih dimenzija prozora konzole
	MoveWindow(console, r.left, r.top, 1200, 600, TRUE); //mijenjaju se vrijednosti duzine i sirine na nove 1200x600

	Korisnik k;
	Admin a;
	Oglas o;
	bool filteri[5];
	std::string vrijednostiFiltera[3];
	std::vector<Oglas> oglasi = o.getOglasi(filteri);	//uzima oglase iz oglasi.txt i sprema u vektor, te postavlja sve filtere na false
	int izbor;
	while (izbor = glavniMenu()) {
		switch (izbor) {
		case 1:
			system("cls");
			std::cin >> k;
			break;
		case 2:
			system("cls");
			if (k.prijava()) {
				int izbor2;
				while (izbor2 = korisnikMenu()) {
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
						int izbor3;
						while (izbor3 = pretragaMenu()) {
							switch (izbor3) {	//svaka opcija unosa novog filtera ce postaviti vrijednosti u nizovima vrijednostFiltera i filteri, ispisati sve oglase nakon filtriranja/sortiranja, te ispisati filtere koji su aktivni
							case 1:
								system("cls");
								vrijednostiFiltera[0] = o.filtrirajPoCijeni(oglasi);
								filteri[0] = true;
								o.ispisOglasa(oglasi);
								ispisiFiltere(filteri, vrijednostiFiltera);
								break;
							case 2:
								system("cls");
								vrijednostiFiltera[1] = o.filtrirajPoKategoriji(oglasi);
								filteri[1] = true;
								o.ispisOglasa(oglasi);
								ispisiFiltere(filteri, vrijednostiFiltera);
								break;
							case 3:
								system("cls");
								o.sortirajPoCijeniRastuci(oglasi);
								filteri[2] = true;
								filteri[3] = false;
								o.ispisOglasa(oglasi);
								ispisiFiltere(filteri, vrijednostiFiltera);
								break;
							case 4:
								system("cls");
								o.sortirajPoCijeniOpadajuci(oglasi);
								filteri[3] = true;
								filteri[2] = false;
								o.ispisOglasa(oglasi);
								ispisiFiltere(filteri, vrijednostiFiltera);
								break;
							case 5:
								system("cls");
								vrijednostiFiltera[2] = o.pretragaPoRijeci(oglasi);
								filteri[4] = true;
								o.ispisOglasa(oglasi);
								ispisiFiltere(filteri, vrijednostiFiltera);
								break;
							case 6:
								system("cls");
								oglasi = o.getOglasi(filteri);	//ponovo uzima oglase iz oglasi.txt
								std::cout << "Filteri uspjesno resetovani!";
								break;
							}
							std::cout << "\nPritisnite bilo koju tipku za nastavak\n";
							_getch();
						}
						break;
					case 5:
						system("cls");
						o.ispisOglasa(o.getOglasi(filteri));
						int ID;
						std::cout << "Unesite ID oglasa o kojem zeljite detaljne informacije: ";
						std::cin >> ID;
						o.ispisOglasaDetaljno(o.getOglasi(filteri), ID);
						break;
					case 6:
						system("cls");
						o.izbrisiOglas(k);
						break;
					case 7:
						system("cls");
						k.promijeniSifru();
						break;
					}
					std::cout << "\nPritisnite bilo koju tipku za nastavak\n";
					_getch();
				}
			}
			break;
		case 3:
			int izbor4;
			system("cls");
			if (a.prijava()) {
				while (izbor4 = adminMenu()) {
					switch (izbor4) {
					case 1:
						system("cls");
						a.ispisStanja();
						break;
					case 2:
						system("cls");
						a.infoOKorisniku();
						break;
					}
					std::cout << "\nPritisnite bilo koju tipku za nastavak\n";
					_getch();
				}
			}
			break;
		}
		std::cout << "\nPritisnite bilo koju tipku za nastavak\n";
		_getch();
	}
	return 0;

}
