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
	Building(int Grundpreis, string Label, vector<Material> mats) : Grundpreis(Grundpreis), Label(Label), mats(mats) {}
	
};

class Empty : public Building {
public:
	Empty() : Building(0, "leer", {Material()}) {}
	
	

};

class Wasserkraftwerk : public Building {
public:
	Wasserkraftwerk() : Building(1000, "Wasserkraftwerk", { Metall(), Metall(), Holz(), Kunststoff() }) {
	}
	

};

struct Windkraftwerk : public Building {
public:
	Windkraftwerk() : Building(500, "Windkraftwerk", {Holz(), Holz(), Kunststoff()}) {
	}
}; 

struct Solarpanele : public Building {
public:
	Solarpanele() : Building(50, "SolarPanele", { Metall(), Kunststoff(), Kunststoff() }) {
	}
	
};



