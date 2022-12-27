#include "Bauelemente.cpp"
class Blueprint {

private:
	int rowsG, colsG;
	Building** matrix;
	double kennzahl;
	void defineSize();
	void calculateKennzahl();
	
	int getRowsG() const;
	int getColsG() const;

public:
	Blueprint();
	void print();
	void deleteArea();
	void build();
	void deleteBlue();
	double getKennzahl();
	Building** getMatrix();
	bool operator()(Blueprint& simTwo); //Funktor
};