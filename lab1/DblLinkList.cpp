#pragma once
#include "DblLinkList.h"
template<class ElemType>
inline void DblLinkList<ElemType>::init()
{
	curr = head = tail = new DblNode<ElemType>;
	size = 0;
}

template<class ElemType>
void DblLinkList<ElemType>::clear()
{
	removeall();
	init();
}

template<class ElemType>
void DblLinkList<ElemType>::removeall()
{
	while (head != NULL)
	{
		curr = head;
		head = head->next;
		delete curr;
	}
}
template<class ElemType>
int DblLinkList<ElemType>::getSize()
{
	return size;
}
template<class ElemType>
int DblLinkList<ElemType>::getPos()
{
	int pos = -1;
	DblNode < ElemType > *p = new DblNode< ElemType >;
	p = head;
	while (p != curr)
	{
		p = p->next;
		pos++;
	}
	return pos;
}
template<class ElemType>
ElemType DblLinkList<ElemType>::getData()
{
	return curr->data;
}
template<class ElemType>
inline DblLinkList<ElemType>::DblLinkList()
{
	init();
}

template<class ElemType>
DblLinkList<ElemType>::~DblLinkList()
{
	removeall();
}

template<class ElemType>
void DblLinkList<ElemType>::moveToHead()
{
	curr = head;
}

template<class ElemType>
void DblLinkList<ElemType>::moveToTail()
{
	curr = tail;
}

template<class ElemType>
void DblLinkList<ElemType>::moveToPre()
{
	if (curr != head) curr = curr->back;
}

template<class ElemType>
void DblLinkList<ElemType>::moveToNext()
{
	if (curr != tail) curr = curr->next;
}

template<class ElemType>
void DblLinkList<ElemType>::moveToPos(int position)
{
	if (position == -1) { curr = head; return; }
	curr = head->next;
	while (position)
	{
		curr = curr->next;
		position--;
	}
	
}

template<class ElemType>
void DblLinkList<ElemType>::insert(const ElemType & it)
{
	size++;
	curr->next = new DblNode<ElemType>(it, curr, curr->next);
	if(curr!=tail) curr->next->next->back = curr->next;
	else tail = curr->next;
	moveToNext();
}

template<class ElemType>
void DblLinkList<ElemType>::remove(int position)
{
	moveToPos(position);
	if (curr == tail) { tail = curr->back; tail->next = NULL; }
	else
	{curr->back->next = curr->next;
	curr->next->back = curr->back; }
	DblNode<ElemType>* ptr = new  DblNode<ElemType>;
	ptr->next =curr;
	if (position==size-1) moveToPre(); else moveToNext();
	delete ptr->next;
	delete ptr;
	size--;
}

template<class ElemType>
void DblLinkList<ElemType>::subCurLine(const ElemType & it)
{
	curr->data = it;
}

