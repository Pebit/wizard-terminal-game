#include <iostream>
#include <string.h>
#include <ctime>

enum OptiuniMeniu {
	OPT_enchant,
	OPT_procura,
	OPT_fura_mana,
	OPT_fura_cristale,
	OPT_cristaliz_or_procura,
	OPT_cristaliz
};
struct Zar {
private:
	int fata[6];
	bool bust;
public:
	Zar() : bust(0), fata{ 0, 0, 0, 0, 0, 0 } {}

	bool get_bust() { return this->bust; }
	int get_fata(int i) { return this->fata[i]; }
	void inc_fata(int i) { this->fata[i]++; }
	void dec_fata(int i) { this->fata[i]--; }

	void aruncare();
	void verificare_bust(int r);
	void memory_wipe();
};

void Zar::memory_wipe() {
	this->bust = 0;
	for (int i = 0; i < 6; i++)
	{
		fata[i] = 0;
	}
}
void Zar::aruncare() {
	{
		int r = rand() % 6;
		std::cout << "a picat ";
		switch (r) {
		case OPT_enchant:
			std::cout << "<ENCHANT>\n";
			break;
		case OPT_procura:
			std::cout << "<PROCURA>\n";
			break;
		case OPT_fura_mana:
			std::cout << "<FURA MANA>\n";
			break;
		case OPT_fura_cristale:
			std::cout << "<FURA CRISTALE>\n";
			break;
		case OPT_cristaliz_or_procura:
			std::cout << "<CRISTALIZEAZA/PROCURA>\n";
			break;
		case OPT_cristaliz:
			std::cout << "<CRISTALIZEAZA>\n";
			break;
		default:
			std::cout << "eroare cod 0\n";
			break;
		}
		this->fata[r]++;
		verificare_bust(r);
	}
}
void Zar::verificare_bust(int r) {
	if (this->fata[r] > 1) {
		this->bust = 1;
		std::cout << "BUSTT!!!\n";
	}
}

struct Jucator {
private:
	char* nume;
	int mana;
	int cristale;
public:
	Jucator(const char* nume = "Jucator_Default") : mana(200), cristale(0) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}

	char* get_nume();
	int get_cristale();
	void procura();
	void cristalizeaza();
	void crist_or_proc();
	void fura_mana(Jucator& other);
	void fura_cristale(Jucator& other);
	void enchant(Zar& zar);
	void consolare();

	friend std::istream& operator>>(std::istream& in, Jucator& jucator);
	friend std::ostream& operator<<(std::ostream& os, const Jucator& jucator);

	~Jucator() {
		delete[] nume;
	}
};

char* Jucator::get_nume() {
	return this->nume;
}
int Jucator::get_cristale() {
	return this->cristale;
}

void Jucator::procura() {
	this->mana += 100;
}
void Jucator::cristalizeaza() {
	if (this->mana > 100) {
		this->cristale += 100;
		this->mana -= 100;
		std::cout << "ai CRISTALIZAT 100 ";
	}
	else {
		this->cristale += mana;
		std::cout << "ai CRISTALIZAT" << mana << " ";
		mana = 0;
	}
}
void Jucator::crist_or_proc() {
	std::cout << "cristalizeaza(0), procura(1)";
	bool decider;
	std::cin >> decider;
	if (decider) {
		this->mana += 50;
	}
	else {
		if (this->mana > 50) {
			this->cristale += 50;
			this->mana -= 50;
		}
		else {
			this->cristale += mana;
			mana = 0;
		}
	}
}
void Jucator::fura_mana(Jucator& other) {
	if (other.mana > 50) {
		other.mana -= 50;
		this->mana += 50;
		std::cout << "ai FURAT 50 ";
	}
	else {
		this->mana += other.mana;
		std::cout << "ai FURAT " << other.mana << " ";
		other.mana = 0;
	}
}
void Jucator::fura_cristale(Jucator& other) {
	if (other.cristale > 35) {
		other.cristale -= 35;
		this->mana += 35;
		std::cout << "ai FURAT 35 ";
	}
	else {
		this->mana += other.cristale;
		std::cout << "ai FURAT " << other.cristale << " ";
		other.cristale = 0;
	}
}
void Jucator::enchant(Zar& zar) {
	int decider = -1;
	while (decider < 1 or decider > 5)
		std::cin >> decider;
	switch (decider) {
	case OPT_procura:
		zar.inc_fata(1);
		break;
	case OPT_fura_mana:
		zar.inc_fata(2);
		break;
	case OPT_fura_cristale:
		zar.inc_fata(3);
		break;
	case OPT_cristaliz_or_procura:
		zar.inc_fata(4);
		break;
	case OPT_cristaliz:
		zar.inc_fata(5);
		break;
	default:
		std::cout << "eroare cod 2";
		break;
	}
}
void Jucator::consolare() {
	this->mana += 50;
}

std::istream& operator>>(std::istream& is, Jucator& jucator) {
	is >> jucator.nume;
	return is;
}
std::ostream& operator<<(std::ostream& os, const Jucator& jucator) {
	os << jucator.nume << " - " << jucator.mana << "m " << jucator.cristale << "c\n";
	return os;
}


void citire_jucatori(int& nr_jucatori, Jucator arrJucatori[]) {
	nr_jucatori = -1;
	while (nr_jucatori < 2 or nr_jucatori > 7)
	{
		std::cout << "introduceti numarul de jucatori (maxim 7)\n";
		std::cin >> nr_jucatori;
	}
	for (int i = 1; i <= nr_jucatori; i++)
	{
		std::cout << "vrajitor " << i << ":";
		std::cin >> arrJucatori[i];
	}
}
int max_score(int nr_jucatori, Jucator arrJucatori[]) {
	int max = -1;
	for (int id_jucator = 1; id_jucator <= nr_jucatori; id_jucator++) {
		std::cout << id_jucator << " " << arrJucatori[id_jucator];
		if (arrJucatori[id_jucator].get_cristale() > max)
			max = arrJucatori[id_jucator].get_cristale();
	}
	return max;
}
void afisare_castigatori(int nr_jucatori, Jucator arrJucatori[], int max) {
	// inca un for in caz de egalitate
	for (int id_jucator = 1; id_jucator <= nr_jucatori; id_jucator++) {
		if (arrJucatori[id_jucator].get_cristale() == max)
			std::cout << "Castigator: " << arrJucatori[id_jucator];
	}
}

int main()
{
	srand((int)time(0));

	Zar zarul_mistic;
	int nr_runde = 4;
	int nr_jucatori;
	Jucator arrJucatori[8];
	citire_jucatori(nr_jucatori, arrJucatori);

	for (int runda = 1; runda <= nr_runde; runda++) {
		std::cout << "RUNDA" << runda << '\n';

		for (int id_jucator = 1; id_jucator <= nr_jucatori; id_jucator++) {
			std::cout << arrJucatori[id_jucator];
			zarul_mistic.memory_wipe();

			bool maiarunci = 1;
			while (maiarunci) {
				zarul_mistic.aruncare();

				if (zarul_mistic.get_bust()) {
					break;
				}

				std::cout << "Mai dai cu zarul, " << arrJucatori[id_jucator].get_nume() << " ?\n 0 = nu sau 1 = da: ";
				std::cin >> maiarunci;
			}
			if (not zarul_mistic.get_bust()) {
				if (zarul_mistic.get_fata(0)) {
					for (int fata = 1; fata < 6; fata++)
						if (zarul_mistic.get_fata(fata)) {
							switch (fata) {
							case OPT_procura:
								std::cout << "1 <PROCURA>\n";
								break;
							case OPT_fura_mana:
								std::cout << "2 <FURA MANA>\n";
								break;
							case OPT_fura_cristale:
								std::cout << "3 <FURA CRISTALE>\n";
								break;
							case OPT_cristaliz_or_procura:
								std::cout << "4 <CRISTALIZEAZA/PROCURA>\n";
								break;
							case OPT_cristaliz:
								std::cout << "5 <CRISTALIZEAZA>\n";
								break;
							default:
								std::cout << "eroare cod 3\n";
								break;
							}
						}

					arrJucatori[id_jucator].enchant(zarul_mistic);
				}
				for (int fata = 1; fata < 6; fata++) {
					while (zarul_mistic.get_fata(fata)) {
						int jucator_ales = -1;
						switch (fata) {
						case OPT_procura:
							arrJucatori[id_jucator].procura();
							std::cout << "ai PROCURAT 100 mana\n";
							break;
						case OPT_fura_mana:
							while ((jucator_ales < 1 or jucator_ales > nr_jucatori) and jucator_ales != id_jucator) {
								std::cout << "alege un jucator de la care sa furi (" << 1 << "->" << nr_jucatori << ")\n";
								std::cin >> jucator_ales;
							}
							arrJucatori[id_jucator].fura_mana(arrJucatori[jucator_ales]);
							std::cout << "mana de la\n" << arrJucatori[jucator_ales] << "\n";
							break;
						case OPT_fura_cristale:
							while ((jucator_ales < 1 or jucator_ales > nr_jucatori) and jucator_ales != id_jucator) {
								std::cout << "alege un jucator de la care sa furi (" << 1 << "->" << nr_jucatori << ")\n";
								std::cin >> jucator_ales;
							}
							arrJucatori[id_jucator].fura_cristale(arrJucatori[jucator_ales]);
							std::cout << "cristale de la\n" << arrJucatori[jucator_ales] << " si s-au transformat in mana\n" << arrJucatori[id_jucator] << "\n";
							break;
						case OPT_cristaliz_or_procura:
							arrJucatori[id_jucator].crist_or_proc();
							std::cout << arrJucatori[id_jucator] << "\n";
							break;
						case OPT_cristaliz:
							arrJucatori[id_jucator].cristalizeaza();
							std::cout << "din mana\n" << arrJucatori[id_jucator] << "\n";
							break;
						default:
							std::cout << "eroare bug in cod 1";
							break;
						}
						zarul_mistic.dec_fata(fata);
					}
				}
			}
			else {
				arrJucatori[id_jucator].consolare();
				std::cout << "consolare +50\n" << arrJucatori[id_jucator] << "\n";
			}
		}
	}
	int max = max_score(nr_jucatori, arrJucatori);
	afisare_castigatori(nr_jucatori, arrJucatori, max);
}