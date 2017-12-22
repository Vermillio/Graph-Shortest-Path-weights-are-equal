//Using the wide-width search method, find the shortest path from the initial to any arbitrary vertex of the connected undirected graph 
//specified by the incidence lists (weights of all edges are equal).

#pragma once

#include <queue>
#include <string>
#include <vector>

using namespace std;

namespace grph
{

	struct edge
	{
		int to;
		double weight;

		edge(int _to, double _w) : to(_to), weight(_w) {};
	};

	class Graph
	{

		vector<vector<edge>> gr;

	public:

		vector<edge> Graph::operator[](int index);

		Graph(vector<vector<edge>> _gr) : gr(_gr) {};

		Graph() {};


		void readFile(string filename);

		int size();
	};

	class ShortestPathFinder
	{
		bool found;

		vector<int> parents;

		vector<bool> used;

		//int curPathLen = 1;

		queue<int> stack;

		Graph *Gr;

		int End;

		void findProc(int curVertex);

	public:

		void demo();


		vector<int> run(int vStart, int vEnd, Graph *G);
	};

	string getcd();

	ostream & operator<<(ostream & c, Graph &gr);
	ostream & operator<<(ostream &c, vector<int> x);
}