#include "Materialien.cpp"
#include <map>
//Ich habe mich fuer Carlas Idee entschieden da diese einfach zu implementieren ist, außerdem spare ich mir eine Extra Klasse fuer die Verwaltung.
//Zuviele Klassen sind unuebersichtlich, andererseits waere es gut verschiedene Funktionen zu trennen.

class Building {

private:
	int Grundpreis;
	string Label;
	int Leistung;
	map<Material, int> mats;
	
public:
	Building() {
		Grundpreis = 0; Label = "leer"; Leistung = 0; mats = { {Holz(), 0}, {Metall(), 0}, {Kunststoff(), 0} }
		;
	}
	Building(int Grundpreis, string Label, int Leistung, map<Material, int> mats) : Grundpreis(Grundpreis), Label(Label), Leistung(Leistung), mats(mats) {}

	virtual string getLabel() const{
		return Label;
	}

	virtual int getGrundpreis() {
		return Grundpreis;
	}

	virtual map<Material, int> getMats() const{
		return mats;
	}

	virtual int getLeistung() {
		return Leistung;
	}

	virtual int getPreis() const {
		int sum = Grundpreis;
		sum += Holz().getPreis() * mats.at(Holz());
		sum += Metall().getPreis() * mats.at(Metall());
		sum += Kunststoff().getPreis() * mats.at(Kunststoff());
		
		return sum;
	}
};

class Empty : public Building {
public:
	Empty() : Building(0, "leer", 0, map<Material, int> { {Holz(), 0}, {Metall(), 0}, {Kunststoff(), 0}}) {}
};

class Wasserkraftwerk : public Building {
public:
	Wasserkraftwerk() : Building(1000, "Wasserkraftwerk", 2000, map<Material, int>{ {Holz(), 1}, {Metall(), 2}, {Kunststoff(), 1}}) {
	}
};

class Windkraftwerk : public Building {
public:
	Windkraftwerk() : Building(500, "Windkraftwerk", 3000,map<Material, int>{ {Holz(), 2}, {Metall(), 0}, {Kunststoff(), 1}}) {
	}
};

class Solarpanele : public Building {
public:
	Solarpanele() : Building(50, "SolarPanele", 1500,map<Material, int>{ {Holz(), 0}, {Metall(), 1}, {Kunststoff(), 2}}) {
	}
};