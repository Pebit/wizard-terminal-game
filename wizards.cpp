#include <iostream>
#include <string>
#include <ctime>
struct Zar {
private:
	int fata[6];
	bool bust;
public:
	Zar() : bust(0), fata{ 0, 0, 0, 0, 0, 0 } {}
	void aruncare() {
		int r = rand() % 6;
		std::cout << "a picat " << r;
		this->fata[r]++;
		verificare_bust(r);
	}
	void verificare_bust(int r) {
		if (this->fata[r] > 1) {
			this->bust = 1;
			std::cout << "\nBUSTT!!!\n";
		}
	}
	bool get_bust() {
		return this->bust;
	}
	void inc_fata(int i) {
		this->fata[i]++;
	}
	void dec_fata(int i) {
		this->fata[i]--;
	}
	int get_fata(int i) {
		return this->fata[i];
	}
	void memory_wipe()
	{
		this->bust = 0;
		for (int i = 0; i < 6; i++)
		{
			fata[i] = 0;
		}
	}
};

struct Jucator {
private:
	std::string nume;
	int mana;
	int cristale;
public:
	Jucator() : nume("Jucator_Default"), mana(0), cristale(0) {}
	Jucator(int index) : nume("Jucator_Default"), mana(0), cristale(0) {}
	Jucator(int index, std::string nume) : nume(nume), mana(0), cristale(0) {}

	std::string get_nume();
	void procura() {
		this->mana += 100;
	}
	void cristalizeaza() {
		if (this->mana > 100) {
			this->cristale += 100;
			this->mana -= 100;
		}
		else {
			this->cristale += mana;
			mana = 0;
		}
	}
	void crist_or_proc() {
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
	void fura_mana(Jucator& other) {
		if (other.mana > 50) {
			other.mana -= 50;
			this->mana += 50;
		}
		else {
			other.mana = 0;
			this->mana += other.mana;
		}
	}
	void fura_cristale(Jucator& other) {
		if (other.cristale > 35) {
			other.cristale -= 35;
			this->mana += 35;
		}
		else {
			other.cristale = 0;
			this->mana += other.cristale;
		}
	}
	void enchant(Zar& zar) {
		std::cout << "puterea de amplificat va fi:\n 1:procura(full)\n2:fura mana\n3:fura cristale\n4:cristalizeaza/procura\n5:cristalizeaza(full)\n";
		int decider = -1;
		while (decider < 1 or decider > 5)
			std::cin >> decider;
		switch (decider) {
		case 1:
			zar.inc_fata(1);
			break;
		case 2:
			zar.inc_fata(2);
			break;
		case 3:
			zar.inc_fata(3);
			break;
		case 4:
			zar.inc_fata(4);
			break;
		case 5:
			zar.inc_fata(5);
			break;
		default:
			zar.inc_fata(1);
			break;
		}
	}

	friend std::istream& operator>>(std::istream& in, Jucator& jucator);
	friend std::ostream& operator<<(std::ostream& os, const Jucator& jucator);
};

std::string Jucator::get_nume() {
	return this->nume;
}

std::istream& operator>>(std::istream& is, Jucator& jucator) {
	is >> jucator.nume;
	return is;
}
std::ostream& operator<<(std::ostream& os, const Jucator& jucator) {
	os << "Nume:" << jucator.nume << ": " << jucator.mana << "m " << jucator.cristale << "c\n";
	return os;
}

int main()
{
	srand((int)time(0));

	Zar zarul_mistic;
	int nr_runde = 2;

	int nr_jucatori;
	std::cout << "introduceti numarul de jucatori (maxim 7)\n";
	std::cin >> nr_jucatori;

	Jucator arrJucatori[8];
	for (int i = 1; i <= nr_jucatori; i++)
	{
		std::cout << "vrajitor " << i << ":";
		std::cin >> arrJucatori[i];
	}

	for (int runda = 1; runda <= nr_runde; runda++) {
		std::cout << "RUNDA" << runda << '\n';

		for (int id_jucator = 1; id_jucator <= nr_jucatori; id_jucator++) {
			std::cout << arrJucatori[id_jucator];
			zarul_mistic.memory_wipe();

			int maiarunci = 1;
			while (maiarunci) {
				zarul_mistic.aruncare();

				if (zarul_mistic.get_bust()) {
					break;
				}

				std::cout << "\nMai dai cu zarul, " << arrJucatori[id_jucator].get_nume() << " ?\n 0 = nu sau 1 = da:";
				std::cin >> maiarunci;
			}
			if (not zarul_mistic.get_bust()) {
				if (zarul_mistic.get_fata(0))
					arrJucatori[id_jucator].enchant(zarul_mistic);
				for (int fata = 1; fata < 6; fata++) {
					while (zarul_mistic.get_fata(fata)) {
						int jucator_ales = -1;
						switch (fata) {
						case 1:
							arrJucatori[id_jucator].procura();
							std::cout << "ai PROCURAT 100 mana\n";
							break;
						case 2:
							std::cout << "alege un jucator de la care sa furi (" << 1 << "->" << nr_jucatori << ")\n";
							while ((jucator_ales < 1 or jucator_ales > nr_jucatori) and jucator_ales != id_jucator)
								std::cin >> jucator_ales;
							arrJucatori[id_jucator].fura_mana(arrJucatori[jucator_ales]);
							std::cout << "ai FURAT 50 mana de la\n" << arrJucatori[jucator_ales] << "\n";
							break;
						case 3:
							std::cout << "alege un jucator de la care sa furi (" << 1 << "->" << nr_jucatori << ")\n";
							while ((jucator_ales < 1 or jucator_ales > nr_jucatori) and jucator_ales != id_jucator)
								std::cin >> jucator_ales;
							arrJucatori[id_jucator].fura_cristale(arrJucatori[jucator_ales]);
							std::cout << "ai FURAT 35 cristale de la\n" << arrJucatori[jucator_ales] << " si s-au transformat in mana\n";
							break;
						case 4:
							arrJucatori[id_jucator].crist_or_proc();
							break;
						case 5:
							arrJucatori[id_jucator].cristalizeaza();
							break;
						default:
							std::cout << "eroare citire fete";
							break;
						}
						zarul_mistic.dec_fata(fata);
					}
				}
			}
		}
	}
}