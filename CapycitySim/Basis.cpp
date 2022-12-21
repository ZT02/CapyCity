#include <iostream>
#include "../CapycitySim/Bauelemente.cpp"
#include <map>
class Material;
Building Gebaeude[] = { Empty(), Wasserkraftwerk(), Windkraftwerk(), Solarpanele() };
class CapycitySim {

private:
	int rowsG, colsG;
	Building** matrix;

public:
	CapycitySim();
	void blueprint() const;
	void deleteArea();
	void deleteCity();
	bool buildmenu();
	void build();
	void defineSize();
	int getRowsG();
	int getColsG();
	Building** getMatrix();
};


CapycitySim::CapycitySim() {
	defineSize();
	return;
}


void CapycitySim::blueprint() const {
	cout << "----Blueprint----" << endl;

	//maxLength = Laeng des lengsten Wortes
	int gesamtPreis = 0, maxLength = 0;

	//Labels der Gebauede mit Padding, damit sie gleichmaessig verteilt sind
	string labelListWithPadding[sizeof(Gebaeude) / sizeof(Building)]{};

	//Tabelle mit benutzen Gebaeuden und deren Materialaien
	int** allMats = new int* [4];
	for (int i = 0; i < 4; ++i) {
		allMats[i] = new int[sizeof(Gebaeude) / sizeof(Building)];
		for (int x = 0; x < sizeof(Gebaeude) / sizeof(Building); x++)
			allMats[i][x] = 0;
	}

	//Laengsten Label finden
	for (int i = 0; i < sizeof(Gebaeude) / sizeof(Building); i++)
		if (maxLength < Gebaeude[i].getLabel().length())
			maxLength = Gebaeude[i].getLabel().length();

	//Padding errechnen und dem Label hinzufuegen
	for (int i = 0; i < sizeof(Gebaeude) / sizeof(Building); i++) {
		//Padding berechnen
		labelListWithPadding[i] = Gebaeude[i].getLabel();
		int paddingNeeded = maxLength - labelListWithPadding[i].length();
		string Padding = " ";
		labelListWithPadding[i] += Padding;

		while (paddingNeeded != 0) {

			labelListWithPadding[i] += Padding;
			paddingNeeded--;
		}
	}

	//Ausgabe
	//Matrix durchlaufen
	cout << endl;
	for (int i = 0; i < rowsG; i++) {
		for (int x = 0; x < colsG; x++) {
			for (int y = 0; y < sizeof(Gebaeude) / sizeof(Building); y++)
				if (matrix[i][x].getLabel() == Gebaeude[y].getLabel()) { //Label mit Padding waehlen
					cout << labelListWithPadding[y]; //Ausgabe Label mit Padding
						allMats[0][y]++;
						gesamtPreis += Gebaeude[y].getGrundpreis(); //Preis und Gesamtpreis addieren
						auto po = Gebaeude[y].getMats();
						//Materialien fuer Gebaeude zaehlen -> In Tabelle schreiben, Preis auch auf Gesamtpreis addieren
						//Materialkosten auch zu Gesamtpreis addieren
						allMats[1][y] += po.at(Holz());
						gesamtPreis += (Holz().getPreis() * po.at(Holz()));
						allMats[2][y] += po.at(Metall());
						gesamtPreis += (Metall().getPreis() * po.at(Metall()));
						allMats[3][y] += po.at(Kunststoff());
						gesamtPreis += (Kunststoff().getPreis() * po.at(Kunststoff()));
				}
		}
		cout << "\n" << endl;
	}

	//Ausgabe Anzahl der jeweiligen Gebaeudeart + Gebaeudelabel + Einzel preis, dann Gesamtmaterialien diese Gebaeudeart (insgesamt, nicht einzeln)
	for (int i = 1; i < sizeof(Gebaeude) / sizeof(Building); i++) {
		cout << allMats[0][i] << "x: " << Gebaeude[i].getLabel() << ": Einzelpreis -> " << Gebaeude[i].getGrundpreis() << endl;
		cout << "Materialien:\n" << " " << allMats[1][i] << "x: Holz" << endl;
		cout << " " << allMats[2][i] << "x: Metall" << endl;
		cout << " " << allMats[3][i] << "x: Kunststoff\n" << endl;
	}

	//Gesamtpreis fuer Capycity : )
	cout << "-----------------\n" << "Gesamtkosten -> " << gesamtPreis << "\n-----------------" << endl;
	cout << endl;

	//Matrix wieder loeschen die oben erstellt wurde
	for (int i = 0; i < 4; i++)
		delete[] allMats[i];

	delete[] allMats;
}


void CapycitySim::deleteArea() {
	cout << "----Na? Falsch geplant?----" << endl;
	int length, width, pos_x, pos_y;

	cout << "Laenge, Breite, Position (x, y): " << endl;
	cin >> width >> length >> pos_x >> pos_y;

	//Eingabe pruefen
	if ((pos_x + length) > colsG || pos_y + width > rowsG || pos_x < 0 || pos_y < 0) {
		cout << "Loeschbereich liegt ausserhalb des Baubereichs. Versuch es nochmal" << endl;
		deleteArea();
		return;
	}

	//Loeschen -> Feld durch "Empty" Feld ersetzen
	for (int i = 0; i < length; i++) {
		for (int x = 0; x < width; x++)
			if (matrix[i + pos_y][x + pos_x].getLabel() != Empty().getLabel())
				matrix[i + pos_y][x + pos_x] = Gebaeude[0];
	}
}


void CapycitySim::build() {
	cout << "----Let's plan Capycity!----" << endl;
	int length, width, pos_x, pos_y, buildType;

	//Auswahl
	cout << "Folgende Bauwerke stehen zur Verfuegung: " << endl;

	for (int i = 1; i < sizeof(Gebaeude) / sizeof(Building); i++)
		cout << "[" << i << "] " << Gebaeude[i].getLabel() << endl;

	//Eingabe
	cout << "Typ, Laenge, Breite, Position (x, y): " << endl;
	cin >> buildType >> width >> length >> pos_x >> pos_y;

	//Eingabepruefung
	if (buildType > sizeof(Gebaeude) / sizeof(Building) - 1 || buildType <= 0) {
		cout << "Kein gueltiger Gebaeudetyp wurde ausgewaehlt!" << endl;
		build();
		return;
	}

	if (pos_x + length > colsG || pos_y + width > rowsG || pos_x < 0 || pos_y < 0) {
		cout << "Gebaeudebereich liegt ausserhalb des Baubereichs. Versuch es nochmal" << endl;
		build();
		return;
	}

	for (int i = 0; i < length; i++) {
		for (int x = 0; x < width; x++)
			if (matrix[i + pos_y][x + pos_x].getLabel() != Empty().getLabel()) {
				cout << "Bauvorhaben kollidiert mit " << matrix[i + pos_y][x + pos_x].getLabel() << "\n Initialisiere neuen Bauversuch...." << endl;
				build();
				return;
			}
	}

	//Baufunktion
	for (int i = 0; i < length; i++) {
		for (int x = 0; x < width; x++)
			matrix[i + pos_y][x + pos_x] = Gebaeude[buildType];
	}
}


void CapycitySim::deleteCity() {
	cout << "Deleting city..... Bye Capybara.... :( " << endl;

	//unsere matrix loeschen
	for (int i = 0; i < rowsG; ++i)
		delete[] matrix[i];

	delete[] matrix;

}


bool CapycitySim::buildmenu() {
	cout << "----Was moechten Sie bauen Sir?----" << endl;
	cout << "[1] Gebaeude setzen: Art, Laenge, Breite und Position" << endl;
	cout << "[2] Bereich loeschen: Loescht einen Bereich, betroffene Gebaeude werden verkleinert" << endl;
	cout << "[3] Bauplan: Gibt den Bauplan zurueck" << endl;
	cout << "[4] Programm beenden: Leave Capycity :(" << endl;
	int choice;

	cin >> choice;
	if (choice <= 0 || choice > 4) {
		buildmenu();
	}
	else if (choice == 1) {
		build();
	}
	else if (choice == 2) {
		deleteArea();
	}
	else if (choice == 3) {
		blueprint();
	}
	else if (choice == 4) {
		deleteCity();
		return false;
	}
	return true;
}


void CapycitySim::defineSize() {
	//Laenge, Breite eingabe
	cout << "Simulation wurde begonnen..." << endl;
	cout << "Laenge und Breite eingeben: " << endl;
	cin >> colsG >> rowsG;

	if (colsG <= 0 || rowsG <= 0) {
		cout << "--------\nUngueltige Werte\n--------" << endl;
		defineSize();
		return;
	}

	//Baufeld generieren
	matrix = new Building * [rowsG];
	for (int i = 0; i < rowsG; ++i) {
		matrix[i] = new Building[colsG];
		for (int x = 0; x < colsG; x++)
			matrix[i][x] = Empty();

	}
}

int CapycitySim::getRowsG() {
	return rowsG;
}

int CapycitySim::getColsG() {
	return colsG;
}

Building** CapycitySim::getMatrix() {
	return matrix;
}


//Funktor
class equals {

public:
	bool operator()(CapycitySim& simOne, CapycitySim& simTwo){
		if (simOne.getRowsG() != simTwo.getRowsG() || simOne.getColsG() != simTwo.getRowsG()) {
			cout << "--------\nBauplaene sind nicht identisch\n--------" << endl;
			return false;
		}

		//Bauplaene selbe Groesse? -> Felder einzeln ueberpruefen
		for (int i = 0; i < simOne.getRowsG(); i++) {
			for (int x = 0; x < simOne.getColsG(); x++) {
				if (simOne.getMatrix()[i][x].getLabel() != simTwo.getMatrix()[i][x].getLabel()) {
					cout << "--------\nBauplaene sind nicht identisch\n--------" << endl;
					return false;
				}
			}
			cout << "\n" << endl;
		}
		cout << "--------\nBauplaene sind identisch\n--------" << endl;
		return true;
	}
};


int main() {
	CapycitySim test = CapycitySim();
	CapycitySim test2 = CapycitySim();

	//Funktor test
	equals functor;

	bool run = true;
	//run ist bei delete Auswahl in Menu negativ -> Abbruch
	while (run) {
		run = test.buildmenu();
		test2.buildmenu();
		functor(test, test2);
	}

	return 1;
}
