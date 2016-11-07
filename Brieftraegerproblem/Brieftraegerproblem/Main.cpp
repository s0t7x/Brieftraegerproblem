/*
Name: Brieftraegerproblem
Author: s0T7x
Website: www.github.com/s0t7x

Git: www.github.com/s0t7x/Brieftraegerproblem

Version: 0.2
*/
#include <iostream>
#include <list>
#include <vector>

using namespace std;

/*
Class: Graph
	Klasse zum erstellen eines Graphen anhand einer Adjazenzmatrix.
*/
class Graph {
private:

	int P = NULL;			//Anzahl der Knotenpunkte
	list<int> *mat;	//Dynamischer Array für die Adjazenzmatrix

public:

	//Der Graph besteht aus einer Menge Knoten P(Knotenpunkte) und einer Menge ungerichteter Kanten K: G = (P, K)
	//nP sei hierber die Anzahl der Knoten P
	Graph(int nP) {
		this->P = nP;
		mat = new list<int>[P];
	
	}

	//Destructor zur Speicherreinigung
	~Graph() {
		delete[] mat;
	}

	//Eine Kante zu Punkt P mit dem Kantengewicht g hinzu zu fügen
	void neueKante(int P, int g) {
		mat[P].push_back(g);
	}

	//Tiefensuche
	void Tiefensuche(int P, bool besucht[])
	{
		//Den aktuellen Knoten als besucht makieren
		besucht[P] = false;

		//Für alle Knoten in mat[p] wiederholen
		list<int>::iterator i;
		for (i = mat[P].begin(); i != mat[P].end(); ++i)
			if (!besucht[*i])
				Tiefensuche(*i, besucht);
	}

	bool Zusammenhang() {
		int i = 0;
		bool besucht[20];
		//Test
		//Markiere all Knoten als nicht besucht
		
		for (i = 0; i < P; i++)
			besucht[i] = false;

		//Finde einen Knoten mit Grad ungleich 0
		for (i = 0; i < P; i++)
			if (mat[i].size() != 0)
				break;

		//Gibt es keine Kanten im Graphen gebe true aus
		if (i == P)
			return true;
		
		//Tiefensuche für den Knoten
		Tiefensuche(i, besucht);

		//Wurden alle Knoten besucht?
		for (i = 0; i < P; i++)
			if (besucht[i] == false && mat[i].size() > 0)
				return false;

		return true;
	}

	int Eulersch()
	{
		//Prüfen ob alle Knoten verbunden sind
		if (Zusammenhang() == false)
			return 0;

		//Zähle Knoten mit ungeradem Grad
		int odd = 0;
		for (int i = 0; i < P; i++)
			if (mat[i].size() & 1)
				odd++;

		//Exisstieren Knoten mit ungeradem Grad, so ist der Graph nicht Eulersch
		return (odd) ? 1 : 0;
	}

};

int main()
{
	Graph g1(5);
	g1.neueKante(1, 0);
	g1.neueKante(0, 2);
	g1.neueKante(2, 1);
	g1.neueKante(0, 3);
	g1.neueKante(3, 4);
	cout << "Result for Graph 1: ";
	g1.Eulersch();

	return 0;
}
