#include <iostream>
#include <string>
#include <ctime>
struct Jucator {
private:
	std::string nume;
	int mana;
	int cristale;
public:
	Jucator() : nume("Jucator_Default"), mana(0), cristale(0) {}
	Jucator(std::string nume) : nume(nume), mana(0), cristale(0) {}
	void set_nume(std::string nume) {
		this->nume = nume;
	}
	// de facut operator de afisare
};

struct Zar {
private:
	int fata[6];
	bool bust;
public:
	Zar() : bust(0), fata{ 0, 0, 0, 0, 0, 0 } {}
	void aruncare() {
		int r = rand() % 6;
		std::cout << r;
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

};

int main()
{
	srand((int)time(0));
	Zar zarul_mistic;

}