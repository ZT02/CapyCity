#include "bas.h"
using namespace std;

//Konstruktor
CapycitySim::CapycitySim() { plaene = vector<Blueprint>();
	newBlueprint();
}

//Bauplan loeschen 
void CapycitySim::deleteBlueprint(int pos) {
	plaene[pos].deleteBlue();
	plaene.erase(plaene.begin() + pos, plaene.begin() + pos+1);
}

//neuer Bauplan, loescht alle gleichen Plaene mit derselben Kennzahl, sobald 3. Plan erstellt wird
void CapycitySim::newBlueprint() {
	if (!(currentBlueprint < 1)) {
		for (int i = 0; i < currentBlueprint; i++) {
			if (plaene[i](plaene[currentBlueprint])) { //mithilfe des Funktors
				deleteBlueprint(i);
			}
		}
	}

	plaene.push_back(Blueprint());
	currentBlueprint = plaene.size() - 1;
}

//Falls ein anderer weiter bearbeitet werden moechte
void CapycitySim::changeBlueprint() {
	int wahl;
	cout << "Waehle einen Plan aus: " << 0 << " - " << plaene.size() - 1 <<": " << endl;
	cin >> wahl;
	if (wahl < 0 || wahl >= plaene.size()) {
		cout << "Plan existiert nicht... erneute Auswahl." << endl;
		changeBlueprint();
		return;
	}
	currentBlueprint = wahl;
}

//Ausgabe
void CapycitySim::printAll() {
	if (!plaene.size()) {
		cout << "Keine Plaene vorhanden" << endl;
		return;
	}
	cout << "----------------------------------" << "\nSortierte Ausgabe: nach absteigender Kennzahl\n" << endl;
	//Absteigend nach Kennzahlen
	sort(plaene.begin(), plaene.end(), [](Blueprint& one, Blueprint& two) {
		return one.getKennzahl() > two.getKennzahl();
		});

	for (int i = 0; i < plaene.size(); i++)
		plaene[i].print();
}

//Alle loeschen, bei Programm Exit (durch menu)
void CapycitySim::deleteAllBlueprints() {
	for(int i = 0; i < plaene.size(); i++)
		plaene[i].deleteBlue();

	plaene.~vector();
}

CapycitySim::~CapycitySim() {
	deleteAllBlueprints();
}

//Baumenu
bool CapycitySim::buildmenu() {
	cout << "----Was moechten Sie bauen Sir?----" << endl;
	cout << "[1] Gebaeude setzen: Art, Laenge, Breite und Position" << endl;
	cout << "[2] Bereich loeschen: Loescht einen Bereich, betroffene Gebaeude werden verkleinert" << endl;
	cout << "[3] Aktuellen Bauplan ausgeben" << endl;
	cout << "[4] Alle Bauplaene ausgeben" << endl;
	cout << "[5] Anderen Bauplan bearbeiten" << endl;
	cout << "[6] Neuen Bauplan hinzufuegen" << endl;
	cout << "[7] Programm beenden: Leave Capycity :(" << endl;
	int choice;

	cin >> choice;
	if (choice <= 0 || choice > 7) {
		buildmenu();
	}
	else if (choice == 1) {
		plaene[currentBlueprint].build();
	}
	else if (choice == 2) {
		plaene[currentBlueprint].deleteArea();
	}
	else if (choice == 3) {
		plaene[currentBlueprint].print();
	}
	else if (choice == 4) {
		printAll();
	}
	else if (choice == 5) {
		changeBlueprint();
	}
	else if (choice == 6) {
		newBlueprint();
	}
	else if (choice == 7) {
		deleteAllBlueprints();
		return false;
	}
	return true;
}


int main() {
	CapycitySim test = CapycitySim();


	bool run = true;
	//run ist bei delete Auswahl in Menu negativ -> Abbruch
	while (run) {
		run = test.buildmenu();
	}

	return 1;
}

