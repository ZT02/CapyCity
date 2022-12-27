#include "Blue.h"
Building Gebaeude[] = { Empty(), Wasserkraftwerk(), Windkraftwerk(), Solarpanele() };

void Blueprint::defineSize() {
	//Laenge, Breite eingabe
	cout << "\nNeuer Bauplan wurde begonnen..." << endl;
	cout << "Laenge und Breite eingeben: \n" << endl;
	cin >> colsG >> rowsG;

	if (colsG <= 0 || rowsG <= 0) {
		cout << "--------\nUngueltige Werte\n--------" << endl;
		defineSize();
		return;
	}

	//Baufeld generieren
	Blueprint::matrix = new Building * [rowsG];
	for (int i = 0; i < rowsG; ++i) {
		matrix[i] = new Building[colsG];
		for (int x = 0; x < colsG; x++)
			matrix[i][x] = Empty();
	}
}

//Konstruktor
Blueprint::Blueprint(){
	kennzahl = 0;
	defineSize();
}



//Bereich loeschen
void Blueprint::deleteArea() {
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

//Bauen
void Blueprint::build() {
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

//Kenzahl berechnen
void Blueprint::calculateKennzahl() {
	cout << endl;
	if (rowsG == 0 || colsG == 0) {
		kennzahl = 0;
		return;
	}
	int gesamtLeistung = 0;
	int gesamtPreis = 0;
	int plangGroeße = rowsG*colsG;
	for (int i = 0; i < rowsG; i++) {
		for (int x = 0; x < colsG; x++) {
					gesamtLeistung += matrix[i][x].getLeistung();
					gesamtPreis += matrix[i][x].getPreis(); //Preis und Gesamtpreis addieren
		}
	}
	//Division durch 0 Vermeidung
	if (gesamtLeistung == 0 || gesamtPreis == 0) {
		kennzahl = 0;
		return;
	}
	kennzahl = (double) (gesamtLeistung/(double)(gesamtPreis * plangGroeße));
}

//Einzelausgabe
void Blueprint::print() {
	cout << "----Blueprint----" << endl;
	calculateKennzahl();
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
					gesamtPreis += Gebaeude[y].getPreis(); //Preis und Gesamtpreis addieren
					auto po = Gebaeude[y].getMats();
					//Materialien der Gebaeude zaehlen
					allMats[1][y] += po.at(Holz());
					allMats[2][y] += po.at(Metall());
					allMats[3][y] += po.at(Kunststoff());
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
		cout << " " << "Summiert: " << Gebaeude[i].getPreis() * allMats[0][i] << "\n" << endl;
	}

	//Gesamtpreis & Kennzahl fuer Blueprint : )
	cout << "-----------------\n" << "Gesamtkosten -> " << gesamtPreis << "\n-----------------" << endl;
	cout << "-----------------\n" << "Kennzahl -> " << kennzahl << "\n-----------------" << endl;
	cout << "----------------------------------" << endl;
	cout << endl;

	//Matrix wieder loeschen die oben erstellt wurde
	for (int i = 0; i < 4; i++)
		delete[] allMats[i];

	delete[] allMats;
}

//einzelloeschung
void Blueprint::deleteBlue() {
	cout << "Deleting blueprint........." << endl;

	//unsere matrix loeschen
	for (int i = 0; i < rowsG; ++i)
		delete[] matrix[i];

	delete[] matrix;

	cout << "Deleted" << endl;
}

//Kennzahl return
double Blueprint::getKennzahl(){
	calculateKennzahl();
	return kennzahl;
}

//Reihe return
int Blueprint::getRowsG() const{
	return rowsG;
}

//Spalte return
int Blueprint::getColsG() const{
	return colsG;
}

//matrix return
Building** Blueprint::getMatrix() {
	return matrix;
}


//Funktor
bool Blueprint::operator()( Blueprint& simTwo) {
	return getKennzahl() == simTwo.getKennzahl();
}