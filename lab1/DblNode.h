#pragma once
#include<iostream>
using namespace std;

template<class ElemType>
struct DblNode
{
	ElemType data;
	DblNode<ElemType>* back;
	DblNode<ElemType>* next;

	DblNode() { back=next = NULL; };

	DblNode(ElemType item, DblNode<ElemType>* linkback = NULL, DblNode<ElemType>* linknext = NULL)
	{
		data = item;
		back = linkback;
		next = linknext;
	};
};
