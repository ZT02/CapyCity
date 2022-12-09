#include <iostream>
using namespace std;
const enum Gebaeude { Empty, Wasserkraftwerk, Windkraftwerk, Solarpanele };
class CapycitySim {

private:
	int rowsG, colsG;
	Gebaeude** matrix;


public:
	CapycitySim() {
		defineSize();
		return;
	}

	void blueprint() {
		cout << "----Blueprint----" << endl;
		int maxLength = 0;
		//Labels der Gebauede mit Padding, damit sie gleichmaessig verteilt sind
		string labelListWithPadding[4]{ "Leer", "Wasserkraftwerk", "Windkraftwerk", "Solarpanele"};
		


		//Laengsten Bezeichnung finden
		for (int i = 0; i < 4; i++)
			if (maxLength < labelListWithPadding[i].length())
				maxLength = labelListWithPadding[i].length();

		//Padding errechnen und dem Bezeichnung hinzufuegen
		for (int i = 0; i < 4; i++) {
			//Padding berechnen
			
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
				switch (matrix[i][x]) {
				case Empty:
					cout << labelListWithPadding[0];
					break;
				case Wasserkraftwerk:
					cout << labelListWithPadding[1];
					break;
				case Windkraftwerk:
					cout << labelListWithPadding[2];
					break;
				case Solarpanele:
					cout << labelListWithPadding[3];
					break;
				default:
					cout << "Unbekanntes Element!";
				}
					
			}
			cout << "\n" << endl;
		}
		
	
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
				if (matrix[i + pos_y][x + pos_x] != 0)
					matrix[i + pos_y][x + pos_x] = Empty;
		}
	}


	void build() {
		cout << "----Let's plan Capycity!----" << endl;
		int length, width, pos_x, pos_y, buildType;
		string labellist[4]{ "Leer", "Wasserkraftwerk", "Windkraftwerk", "Solarpanele" };
		//Auswahl
		cout << "Folgende Bauwerke stehen zur Verfuegung: " << endl;

		for (int i = 1; i < 4; i++)
			cout << "[" << i << "] " << labellist[i] << endl;

		//Eingabe
		cout << "Typ, Laenge, Breite, Position (x, y): " << endl;
		cin >> buildType >> width >> length >> pos_x >> pos_y;

		//Eingabepruefung
		if (buildType > 4 - 1 || buildType <= 0) {
			cout << "Kein gueltiger Gebaeudetyp wurde ausgewählt!" << endl;
			build();
			return;
		}


		if ((pos_x + length) > colsG || pos_y + width > rowsG || pos_x < 0 || pos_y < 0) {
			cout << "Gebaeudebereich liegt ausserhalb des Baubereichs. Versuch es nochmal" << endl;
			build();
			return;
		}


		for (int i = 0; i < length; i++) {
			for (int x = 0; x < width; x++)
				if (matrix[i + pos_y][x + pos_x] != 0) {
					cout << "Bauvorhaben kollidiert mit " << labellist[matrix[i + pos_y][x + pos_x]] << "\n Initialisiere neuen Bauversuch...." << endl;
					build();
					return;
				}
		}



		//Baufunktion
		for (int i = 0; i < length; i++) {
			for (int x = 0; x < width; x++)
				matrix[i + pos_y][x + pos_x] = Gebaeude(buildType);
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
		matrix = new Gebaeude * [rowsG];
		for (int i = 0; i < rowsG; ++i) {
			matrix[i] = new Gebaeude[colsG];
			for (int x = 0; x < colsG; x++)
				matrix[i][x] = Empty;

		}
	}




};


int main() {
	
	CapycitySim test = CapycitySim();
	bool run = true;

	//run ist bei delete Auswahl in Menu negativ -> Abbruch
	while (run) {
		run = test.buildmenu();
	}

	return 1;
}