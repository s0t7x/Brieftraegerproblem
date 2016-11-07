/*
Name: Brieftraegerproblem
Author: s0T7x
Website: www.github.com/s0t7x

Git: www.github.com/s0t7x/Brieftraegerproblem

Version: 1.0
*/
#include <iostream>
#include <list>
#include <vector>
#define _MAX 200

#define _A 0
#define _B 1
#define _C 2
#define _D 3
#define _E 4
#define _F 5
#define _G 6
#define _H 7

using namespace std;

/*
Class: Graph
	Klasse zum erstellen eines Graphen anhand einer Adjazenzmatrix.
*/
class Graph {

private:
	int P;			// Anzahl der Knotenpunkte
	int **mat;		// Adjazenzmatrix
	bool *besucht;	// Wurde ein Knoten bereits besucht?
	int imgK = 0;	// Kantengewicht, hinzugefügter imaginärer Kanten
	int route = 0;	// Kantengewicht der Kantenfolge des Eulerkreises

					// Methode für eine einfache Tiefensuche
	void Tiefensuche(int P) {

		//Den aktuellen Knoten als besucht makieren
		besucht[P] = true;

		//Für alle Knoten in mat[p] wiederholen
		for (int i = 0; i != P; ++i)
			if (!besucht[i])
				Tiefensuche(i);
	}

	// Methode zum prüfen, ob der Graph zusammenhängend ist
	bool Zusammenhang() {
		int i = 0;
		int j = 0;

		//Markiere all Knoten als nicht besucht
		for (i = 0; i < P; i++)
			besucht[i] = false;

		//Finde einen Knoten mit Grad ungleich 0
		for (i = 0; i < P; i++)
			for (j = 0; j < P; j++)
				if (mat[i][j] != 0 || mat[i][j] != _MAX)
					break;

		//Gibt es keine Kanten im Graphen gebe true aus
		if (i == P && j == P)
			return true;

		//Tiefensuche für den Knoten i
		Tiefensuche(i);

		//Wurden alle Knoten besucht?
		for (i = 0; i < P; i++)
			for (j = 0; j < P; j++)
				if (besucht[i] == false && mat[i][j] > 0)
					return false;

		return true;
	}

	// Methode zum prüfen, ob der Graph bereits Eulersch ist
	int istEulersch() {
		//Prüfen ob alle Knoten verbunden sind
		if (Zusammenhang() == false)
			return 0;

		//Zähle Knoten mit ungeradem Grad
		int odd = 0;
		int count = 0;
		int i = 0;
		int j = 0;
		for (i = 0; i < P; i++) {
			count = 0;
			for (j = 0; j < P; j++) {
				if (mat[i][j] > 0 && mat[i][j] != _MAX)
					count++;
			}
			if (count & 1 == 1) {
				return 0;
			}
		}

		//Exisstieren Knoten mit ungeradem Grad, so ist der Graph nicht Eulersch. Wenn nicht, wird er Eulersch gemacht
		return 1;
	}

	// Methode zum finden des EulerKreises
	bool EulerKreis(int P) {
		imgK = 0;
		for (int k = 0; k < P; k++)
		{
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < P; j++)
				{
					if (mat[i][k] + mat[k][j] < mat[i][j]) {
						imgK += mat[i][j];
						mat[i][j] = mat[i][k] + mat[k][j];
					}
				}
			}
		}
		return 1;
	}


public:

	// Constructer welcher alle Einträge in einer Adjazenzmatrix gleich 0 setzt
	Graph(int P) {
		this->P = P;
		besucht = new bool[P];
		mat = new int*[P];
		for (int i = 0; i < P; i++)
		{
			mat[i] = new int[P];
			for (int j = 0; j < P; j++)
			{
				mat[i][j] = 0;
			}
		}
	}

	// Methode um eine Kante zum Graphen hinzu zu fügen
	void neueKante(int start, int ziel, int gewicht) {
		if (start > P || ziel > P || start < 0 || ziel < 0 || gewicht < 0)
		{
			cout << "Fehlerhaft Kante!\n";
		}
		else
		{
			mat[start][ziel] = gewicht;
			mat[ziel][start] = gewicht;
		}
	}

	// Methode zum ausgeben des Graphen in der Konsole
	void Ausgabe()
	{
		int i, j;
		for (i = 0; i < P; i++)
		{
			for (j = 0; j < P; j++)
				cout << mat[i][j] << "  ";
			cout << endl;
		}
	}

	// Methode zum ausgeben der minimalsten Routenlänge des Eulerkreises im Graphen
	int Route() {
		route = 0;

		if (!istEulersch())
			EulerKreis(P);

		for (int i = 0; i < P; i++) {
			for (int j = 0; j < P; j++) {
				route += mat[i][j];
			}
		}
		return route = (route + imgK)/2;
	}

};

int main() {
	Graph G(8);

	G.neueKante(_A, _B, 10);
	G.neueKante(_A, _G, 30);

	G.neueKante(_B, _C, 10);
	G.neueKante(_B, _H, 20);

	G.neueKante(_C, _D, 10);
	G.neueKante(_C, _E, 20);
	G.neueKante(_C, _H, 20);

	G.neueKante(_D, _E, 20);

	G.neueKante(_E, _F, 30);
	G.neueKante(_E, _H, 30);

	G.neueKante(_F, _G, 50);

	G.neueKante(_G, _H, 20);


	cout << "Adjazenzmatrix des Graphen G, wie er in der Seminiararbeit beschrieben wurde: \n";
	G.Ausgabe();

	cout << "Eulerkreis im Graphen G hat die Länge: " << G.Route() << endl;

	system("pause");
	return 0;
}
