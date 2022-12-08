#include <iostream>;
#include "Materialien.cpp"
#include <vector>
using namespace std;

class Building {
public:
	int Grundpreis;
	string Label;
	vector<Material> mats;
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

class Windkraftwerk : public Building {
public:
	Windkraftwerk() : Building(500, "Windkraftwerk", {Holz(), Holz(), Kunststoff()}) {
	}
};

class Solarpanele : public Building {
public:
	Solarpanele() : Building(50, "SolarPanele", { Metall(), Kunststoff(), Kunststoff() }) {
	}
	
};



