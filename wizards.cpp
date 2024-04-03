#include <iostream>
#include <string>
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
};

struct Zar {
private:
	int fata[6];
	bool bust;
public:
	Zar() : bust(0), fata {0, 0, 0, 0, 0, 0} {}
};

int main()
{

}