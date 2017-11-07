#pragma once
#include "DblLinkList.cpp"
#include"String.h"
#include<fstream>


void run()
{
	cout << "chose a letter for a function (h for help again)" << endl;

}

void help()
{
	cout << "h:help" << endl;
	cout << "a:head" << endl;
	cout << "o:show" << endl;
	cout << "e:end" << endl;
	cout << "p:pre" << endl;
	cout << "n:next" << endl;
	cout << "g:go" << endl;
	cout << "i:insert" << endl;
	cout << "d:delete" << endl;
	cout << "c:subCurline" << endl;
	cout << "u:count" << endl;
	cout << "f:find" << endl;
	cout << "b:sub" << endl;
	cout << "r:read" << endl;
	cout << "w:write" << endl;
	cout << "q:quit" << endl;
	
	

	/* ```````````````````*/
}
void show(DblLinkList<String>&text)
{
	cout << "the text now:" << endl;
	text.moveToHead(); text.moveToNext();
	for (int i = 0; i < text.getSize(); i++)
	{
		cout << text.getData() << endl;
		text.moveToNext();
	}
}
void head(DblLinkList<String>&text)
{
	text.moveToPos(0);
	cout << "0:" << text.getData() << endl;
}
void end(DblLinkList<String>&text)
{
	text.moveToPos(text.getSize() - 1);
	cout << text.getSize() - 1 << ":" << text.getData() << endl;
}
void pre(DblLinkList<String>&text)
{
	text.moveToPre();
	cout<<text.getPos()<<":"<< text.getData() << endl;
}
void next(DblLinkList<String>&text)
{
	text.moveToNext();
	cout << text.getPos() << ":" << text.getData() << endl;
}
void go(DblLinkList<String>&text)
{
	int line;
	cout << "which line:" << endl;
	cin >> line;
	text.moveToPos(line);
	cout << text.getPos() << ":" << text.getData() << endl;
}
void insert(DblLinkList<String>&text)
{
	int line;
	cout << "which line:" << endl;
	cin >> line;
	text.moveToPos(line - 1);
	cout << "insert:" << endl;
	String s;
	cin >> s;
	text.insert(s);
	cout << "insert finished" << endl;
}


void deleteTo(DblLinkList<String>&text)
{
	int line;
	cout << "which line:" << endl;
	cin >> line;
	text.remove(line);
	cout << "delete finished" << endl;
}

void subCurLine(DblLinkList<String>&text)
{
	cout << "sub to:" << endl;
	String s;
	cin >> s;
	int pos = text.getPos();
	text.remove(pos);
	text.moveToPos(pos-1);
	text.insert(s);
	cout <<"after sub:" <<text.getPos() << ":" << text.getData() << endl;
}

void count(DblLinkList<String>&text)
{
	int scount = 0,ccount=0;
	scount = text.getSize();
	text.moveToHead(); text.moveToNext();
	for (int i = 0; i < scount; i++)
	{
		ccount += text.getData().size();
		text.moveToNext();
	}
	cout << "scount:" << scount << endl;
	cout << "ccount:" << ccount << endl;
}
void read(DblLinkList<String>&text)
{
	fstream f;
	String s;
	char* ch =new char[10];
	cout << "input file:";
	cin >> ch;
	f.open(ch, ios::in);
	text.clear();
	while (!f.eof())
	{
		f >> s;
		text.insert(s);
	}
	f.close();
	cout << "read finished" << endl;

}

void writeTo(DblLinkList<String>&text)
{
	fstream f;
	String s;
	char* ch = new char[10];
	cout << "output file:";
	cin >> ch;
	f.open(ch, ios::out);
	text.moveToHead(); text.moveToNext();
	for (int i = 0; i < text.getSize(); i++)
	{
		f << text.getData() << endl;
		text.moveToNext();
	}
	f.close();
	cout << "write finished" << endl;
}
void quit()
{
	cout << "quit finished" << endl;
	exit(0);
}




