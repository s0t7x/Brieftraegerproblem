/*
Name: Brieftraegerproblem
Author: s0T7x
Website: www.github.com/s0t7x

Git: www.github.com/s0t7x/Brieftraegerproblem

Version: 0.1
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
	vector<bool> besucht(bool);

public:

	//Der Graph besteht aus einer Menge Knoten P(Knotenpunkte) und einer Menge ungerichteter Kanten K: G = (P, K)
	//nP sei hierber die Anzahl der Knoten P
	Graph(int nP) {
		P = nP;
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
	void Tiefensuche(int P, vector<bool> besucht)
	{
		//Den aktuellen Knoten als besucht makieren
		besucht.at(P) = false;

		//Für alle Knoten in mat[p] wiederholen
		list<int>::iterator i;
		for (i = mat[P].begin(); i != mat[P].end(); ++i)
			if (!besucht[*i])
				Tiefensuche(*i, besucht);
	}

	bool Zusammenhang() {
		int i = 0;
		//Test
		//Markiere all Knoten als nicht besucht
		
		//besucht.clear();

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

};
