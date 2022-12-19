#include <iostream>
#include "Materialien.cpp"
#include <map>
using namespace std;
//Ich habe mich fuer Carlas Idee entschieden da diese einfach zu implementieren ist, auﬂerdem spare ich mir eine Extra Klasse fuer die Verwaltung.
//Zuviele Klassen sind unuebersichtlich, andererseits waere es gut verschiedene Funktionen zu trennen.
class Building {

private:
	int Grundpreis;
	string Label;
	map<Material, int> mats;

public:
	Building() { Grundpreis = 0; Label = "leer"; }
	Building(int Grundpreis, string Label, map<Material, int> mats) : Grundpreis(Grundpreis), Label(Label), mats(mats) {}
	virtual int getGrundpreis() const{
		return Grundpreis;
	}
	virtual string getLabel() const{
		return Label;
	}
	virtual map<Material, int> getMats() const{
		return mats;
	}

};

class Empty : public Building {
public:
	Empty() : Building(0, "leer", map<Material, int> { {Holz(), 0}, {Metall(), 0}, {Kunststoff(), 0}}) {}
};

class Wasserkraftwerk : public Building {
public:
	Wasserkraftwerk() : Building(1000, "Wasserkraftwerk", map<Material, int>{ {Holz(), 1}, {Metall(), 2}, {Kunststoff(), 1}}) {
	}


};

class Windkraftwerk : public Building {
public:
	Windkraftwerk() : Building(500, "Windkraftwerk", map<Material, int>{ {Holz(), 2}, {Metall(), 0}, {Kunststoff(), 1}}) {
	}
};

class Solarpanele : public Building {
public:
	Solarpanele() : Building(50, "SolarPanele", map<Material, int>{ {Holz(), 0}, {Metall(), 1}, {Kunststoff(), 2}}) {
	}

};
