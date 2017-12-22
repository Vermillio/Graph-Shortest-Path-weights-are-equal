#include <iostream>
//#include <queue>
#include <fstream>
#include "ShortestPathGraph.h"

using namespace std;
using namespace grph;

void grph::ShortestPathFinder::findProc(int curVertex)
{
	stack.pop();
	if (curVertex == End)
	{
		found = true;
		return;
	}
	used[curVertex] = true;
	for (auto it : (*Gr)[curVertex])
		if (!used[it.to])
			stack.push(it.to);

	while (! stack.empty() && used[stack.front()])
		stack.pop();

	if (stack.empty())
		return;

	parents[stack.front()] = curVertex;
	findProc(stack.front());
}

vector<int> grph::ShortestPathFinder::run(int vStart, int vEnd, Graph *G)
{
	found = false;
	while (!stack.empty())
		stack.pop();
	used.resize(G->size());
	parents.resize(G->size());
	End = vEnd;
	Gr = G;
	stack.push(vStart);
	for (int i = 0; i < used.size(); ++i)
		used[i] = false;

	findProc(vStart);
	if (found)
	{
		vector<int> shortest;
		int i = vEnd;
		while (i != vStart)
		{
			shortest.push_back(i);
			i = parents[i];
		}
		shortest.push_back(vStart);
		reverse(shortest.begin(), shortest.end());
		return shortest;
	}
	return vector<int>();
}

void grph::Graph::readFile(string filename)
{
	ifstream fin(filename, ios::in);

	if (!fin.is_open())
	{
		//	ErrorMessage("Couldn't open file.");
		return;
	}

	char buff[20], weight[20];
	int i = 0, to;
	while (!fin.eof())
	{
		fin >> buff;
		if (isdigit(buff[0]))
		{
			to = atoi(buff);
			if (gr.size() <= to)
				gr.resize(to + 1);

			fin >> weight;

			gr[i].push_back({ to, atof(weight) });
		}
		else {
			++i;
			if (gr.size() < i)
				gr.resize(i);
		}
	}
	fin.close();
}

void grph::ShortestPathFinder::demo()
{
	Graph G;
	string filename;
	cout << "Enter filename (must be stored in " << getcd() << " )" << endl;
	cin >> filename;
	G.readFile(filename);
	unsigned int start, end;
	cout << "Enter start : ";
	cin >> start;
	cout << "Enter end : ";
	cin >> end;
	//ShortestPathFinder finder;
	vector<int> path = run(start, end, &G);
	cout << path;
}

string grph::getcd()
{
	wchar_t *w = nullptr;
	wstring ws = _wgetcwd(w, _MAX_PATH);
	return string(ws.begin(), ws.end());
}

vector<edge> grph::Graph::operator[](int index)
{
	return gr[index];
}

int grph::Graph::size()
{
	return gr.size();
}

ostream & grph::operator<<(ostream & c, Graph &gr)
{
	for (int i = 0; i < gr.size(); ++i)
	{
		c << "Vertex " << i << ": ";
		for (auto j : gr[i])
			c << "{ " << i << " -> " << j.to << " w = " << j.weight << " } ";
		c << endl;
	}
	c << endl;
	return c;
}

ostream & grph::operator<<(ostream & c, vector<int> x)
{
	for (int i = 0; i < x.size(); ++i)
		cout << x[i] << " ";
	cout << endl;
	return c;
}
