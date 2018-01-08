#pragma once
#ifndef COURSELIST_H
#define COURSELIST_H
#include<iostream>
#include<string>
using namespace std;

class Link
{
public:
	Link();
	Link(string code, string name, int period, int semester, string precondition);
	string getCode();
	void setCode(string str);
	string getName();
	void setName(string str);
	int getPeriod();
	void setPeriod(int p);
	int getSemaster();
	void setSemester(int s);
	string getPrecondition();
	void setPredition(string str);
	Link* getNext();
	void setNext(Link*);
private:
	string code;
	string name;
	int period;
	int semester;
	string precondition;
	Link *next;
};

class List
{
public:
	List();
	void addCourse(Link* course);
	void insertCourse(Link* course);
	Link* getHead();
	Link* getTail();
	void printlist();
private:
	Link *head;
	Link *tail;
};

#endif
