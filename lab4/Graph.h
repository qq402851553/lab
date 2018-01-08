#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>

using namespace std;

class Graph
{
public:
	virtual int n() = 0;
	virtual int e() = 0;
	virtual int first(int) = 0;
	virtual int next(int, int) = 0;
	virtual void setEdge(int, int, int) = 0;
	virtual void delEdge(int, int) = 0;
	virtual int weight(int, int) = 0;
	virtual int getMark(int) = 0;
	virtual void setMark(int, int) = 0;
};

class Graphm :public Graph
{
public:
	Graphm(int numVert);
	~Graphm();
	int n();
	int e();
	int first(int);
	int next(int, int);
	void setEdge(int, int, int);
	void delEdge(int, int);
	int weight(int, int);
	int getMark(int);
	void setMark(int, int);
private:
	int numVertex, numEdge;
	int **matrix;
	int *mark;
};
#endif
