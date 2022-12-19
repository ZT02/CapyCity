#include <iostream>
using namespace std;
class Material {
private:
	 int Preis;
	 string Label;

public:
	bool operator<(const Material& t) const	{
		return (this->Preis < t.Preis);
	}
	Material() { Preis = 0; }
	 Material(int Preis, string Label) : Preis(Preis), Label(Label){};
	 virtual int getPreis() { return Preis; };
	 virtual string getLabel() { return Label; };
};


class Holz : public Material {
public:
	Holz() : Material( 50, "Kunststoff"){}
	
};


class Metall : public Material {
public:
	Metall() : Material(100, "Metall") {}

};


class Kunststoff : public Material {
public:
	Kunststoff() : Material(25, "Kunststoff") {}

};