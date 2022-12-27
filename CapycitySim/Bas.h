#include "Blue.h";
#include <vector>
#include <algorithm>
class CapycitySim {
private:
	vector<Blueprint> plaene;
	int currentBlueprint;
	void deleteBlueprint(int pos);
	void newBlueprint();
	void changeBlueprint();
	void printAll();
	void deleteAllBlueprints();

public:
	CapycitySim();
	~CapycitySim();
	bool buildmenu();
	
};