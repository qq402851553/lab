#pragma once
#include "DblNode.h"
template<class ElemType>
class DblLinkList
{
protected:
	DblNode<ElemType> * head;
	DblNode<ElemType> * tail;
	DblNode<ElemType> * curr;
	int size;
	
public:
	DblLinkList();
	~DblLinkList();
	void moveToHead();
	void moveToTail();
	void moveToPre();
	void moveToNext();
	void moveToPos(int position);
	void insert(const ElemType& it);
	void remove(int position);
	void subCurLine(const ElemType& it);
	void init();
	void clear();
	void removeall();
	int getSize();
	int getPos();
	ElemType getData();

};
