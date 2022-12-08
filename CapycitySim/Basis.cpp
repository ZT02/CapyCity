#include <iostream>
#include "../CapycitySim/Bauelemente.cpp"
using namespace std;
class Material;
const Building Gebaeude[] = { Empty(), Wasserkraftwerk(), Windkraftwerk(), Solarpanele() };
class CapycitySim {

private:
	int rowsG, colsG;
	Building** matrix;


public:
	CapycitySim() {
		defineSize();
		return;
	}

	void blueprint() {
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
			if (maxLength < Gebaeude[i].Label.length())
				maxLength = Gebaeude[i].Label.length();

		//Padding errechnen und dem Label hinzufuegen
		for (int i = 0; i < sizeof(Gebaeude) / sizeof(Building); i++) {
			//Padding berechnen
			labelListWithPadding[i] = Gebaeude[i].Label;
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
					if (matrix[i][x].Label == Gebaeude[y].Label) {
						cout << labelListWithPadding[y]; //Asugabe Label mit Padding
						if (Gebaeude[y].Label != "leer") { //Gebauede gleichzeitg zaehlen, "leer" = freies Feld -> nicht zaehlen
							allMats[0][y]++;
							gesamtPreis += Gebaeude[y].Grundpreis; //Preis und Gesamtpreis addieren
							for (int z = 0; z < matrix[i][x].mats.size(); z++) { //Materialien für Gebaeude zaehlen -> In Tabelle schreiben, Preis auch auf Gesamtpreis addieren
								string po = matrix[i][x].mats[z].getLabel();

								if (po == "Holz") {
									allMats[1][y] += 1;
									gesamtPreis += Holz().getPreis();
								}
								else if (po == "Metall") {
									allMats[2][y] += 1;
									gesamtPreis += Metall().getPreis();
								}
								else if (po == "Kunststoff") {
									allMats[3][y] += 1;
									gesamtPreis += Kunststoff().getPreis();
								}
							}
						}
					}
			}
			cout << "\n" << endl;
		}

		//Ausgabe Anzahl der jeweiligen Gebaeudeart + Gebaeudelabel + Einzel preis, dann Gesamtmaterialien diese Gebaeudeart (insgesamt, nicht einzeln)
		for (int i = 1; i < sizeof(Gebaeude) / sizeof(Building); i++) {
			cout << allMats[0][i] << "x: " << Gebaeude[i].Label << ": Einzelpreis -> " << Gebaeude[i].Grundpreis << endl;
			cout << "Materialien:\n" << " " << allMats[1][i] << "x: Holz" << endl;
			cout << " " << allMats[2][i] << "x: Metall" << endl;
			cout << " " << allMats[3][i] << "x: Kunststoff\n" << endl;
		}

		//Gesamtpreis für Capycity : )
		cout << "-----------------\n" << "Gesamtpreis -> " << gesamtPreis << "\n-----------------" << endl;
		cout << endl;

		//Matrix wieder löschen die oben erstellt wurde
		for (int i = 0; i < 4; i++)
			delete[] allMats[i];

		delete[] allMats;
	}


	void deleteArea() {
		cout << "----Na? Falsch geplant?----" << endl;
		int length, width, pos_x, pos_y;

		cout << "Laenge, Breite, Position (x, y): " << endl;
		cin >> width >> length >> pos_x >> pos_y;

		//Eingabe pruefen
		if ((pos_x + length) > colsG || pos_y + width > rowsG || pos_x < 0 || pos_y < 0) {
			cout << "Loeschbereich liegt außerhalb des Baubereichs. Versuch es nochmal" << endl;
			deleteArea();
			return;
		}

		//Löschen -> Feld durch "Empty" Feld ersetzen
		for (int i = 0; i < length; i++) {
			for (int x = 0; x < width; x++)
				if (matrix[i + pos_y][x + pos_x].Label != Empty().Label)
					matrix[i + pos_y][x + pos_x] = Gebaeude[0];
		}
	}


	void build() {
		cout << "----Let's plan Capycity!----" << endl;
		int length, width, pos_x, pos_y, buildType;

		//Auswahl
		cout << "Folgende Bauwerke stehen zur Verfuegung: " << endl;

		for (int i = 1; i < sizeof(Gebaeude) / sizeof(Building); i++)
			cout << "[" << i << "] " << Gebaeude[i].Label << endl;

		//Eingabe
		cout << "Typ, Laenge, Breite, Position (x, y): " << endl;
		cin >> buildType >> width >> length >> pos_x >> pos_y;

		//Eingabepruefung
		if (buildType > sizeof(Gebaeude) / sizeof(Building) - 1 || buildType <= 0) {
			cout << "Kein gueltiger Gebäudetyp wurde ausgewählt!" << endl;
			build();
			return;
		}


		if ((pos_x + length) > colsG || pos_y + width > rowsG || pos_x < 0 || pos_y < 0) {
			cout << "Gebaeudebereich liegt außerhalb des Baubereichs. Versuch es nochmal" << endl;
			build();
			return;
		}


		for (int i = 0; i < length; i++) {
			for (int x = 0; x < width; x++)
				if (matrix[i + pos_y][x + pos_x].Label != Empty().Label) {
					cout << "Bauvorhaben kollidiert mit " << matrix[i + pos_y][x + pos_x].Label << "\n Initialisiere neuen Bauversuch...." << endl;
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


	void deleteCity() {
		cout << "Deleting city..... Bye Capybara.... :( " << endl;

		//unsere matrix löschen
		for (int i = 0; i < rowsG; ++i)
			delete[] matrix[i];

		delete[] matrix;

	}

	bool buildmenu() {
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

	void defineSize() {

		//Laenge, Breite eingabe
		cout << "Simulation wurde begonnen..." << endl;
		cout << "Laenge und Breite eingeben: " << endl;
		cin >> colsG >> rowsG;


		//Baufeld generieren
		matrix = new Building * [rowsG];
		for (int i = 0; i < rowsG; ++i) {
			matrix[i] = new Building[colsG];
			for (int x = 0; x < colsG; x++)
				matrix[i][x] = Empty();

		}
	}




};


int main() {
	cout << Wasserkraftwerk().mats[0].getLabel() << endl;
	CapycitySim test = CapycitySim();
	bool run = true;

	//run ist bei delete Auswahl in Menu negativ -> Abbruch
	while (run) {
		run = test.buildmenu();
	}

	return 1;
}