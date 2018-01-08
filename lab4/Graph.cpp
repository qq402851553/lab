#include"Graph.h"

Graphm::Graphm(int numVert)
{
	int i, j;
	numVertex = numVert;
	numEdge = 0;
	mark = new int[numVert];
	for (i = 0; i<numVert; i++)
		mark[i] = 1;
	matrix = (int **)new int*[numVertex];
	for (i = 0; i<numVertex; i++)
		matrix[i] = new int[numVertex];
	for (i = 0; i<numVertex; i++)
		for (j = 0; j<numVertex; j++)
			matrix[i][j] = 0;
}

Graphm::~Graphm()
{
	delete[]mark;
	for (int i = 0; i<numVertex; i++)
		delete[]matrix[i];
	delete[]matrix;
}

int Graphm::n()
{
	return numVertex;
}

int Graphm::e()
{
	return numEdge;
}

int Graphm::first(int v)
{
	int i;
	for (i = 0; i<numVertex; i++)
		if (matrix[v][i] != 0)
			return  i;
	return i;//There is none return n.
}

int Graphm::next(int v1, int v2)
{
	int i;
	for (i = v2 + 1; i<numVertex; i++)
		if (matrix[v1][i] != 0)
			return i;
	return i;//There is none return n.
}

void Graphm::setEdge(int v1, int v2, int wgt)
{
	if (wgt<0)
	{
		cout << "Illegal weight value" << endl;
		return;
	}
	if (matrix[v1][v2] == 0)
		numEdge++;
	matrix[v1][v2] = wgt;
}

void Graphm::delEdge(int v1, int v2)
{
	if (matrix[v1][v2] != 0)
		numEdge--;
	matrix[v1][v2] = 0;
}

int Graphm::weight(int v1, int v2)
{
	return matrix[v1][v2];
}

int Graphm::getMark(int v)
{
	return mark[v];
}

void Graphm::setMark(int v, int val)
{
	mark[v] = val;
}
