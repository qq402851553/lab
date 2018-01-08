#include"COurseList.h"

Link::Link()
{
}
Link::Link(string newcode, string newname, int newperiod, int newsemester, string newprecondition)
{
	code = newcode;
	name = newname;
	period = newperiod;
	semester = newsemester;
	precondition = newprecondition;
	next = NULL;
}

string Link::getCode()
{
	return code;
}

void Link::setCode(string str)
{
	code = str;
}

string Link::getName()
{
	return name;
}

void Link::setName(string str)
{
	name = str;
}

int Link::getPeriod()
{
	return period;
}

void Link::setPeriod(int p)
{
	period = p;
}

int Link::getSemaster()
{
	return semester;
}

void Link::setSemester(int s)
{
	semester = s;
}

string Link::getPrecondition()
{
	return precondition;
}

void Link::setPredition(string str)
{
	precondition = str;
}

Link* Link::getNext()
{
	return next;
}

void Link::setNext(Link *newNext)
{
	next = newNext;
}

List::List()
{
	head = tail = NULL;
}

void List::addCourse(Link* course)
{
	Link* temp = new Link(course->getCode(), course->getName(), course->getPeriod(), course->getSemaster(), course->getPrecondition());
	if (head == NULL)
		head = temp;
	else
		tail->setNext(temp);
	tail = temp;
}

void List::insertCourse(Link* course)
{
	Link* temp = new Link(course->getCode(), course->getName(), course->getPeriod(), course->getSemaster(), course->getPrecondition());
	if (head == NULL)
		head = temp;
	else
	{
		temp->setNext(head);
		head = temp;
	}

}

Link* List::getHead()
{
	return head;
}

Link* List::getTail()
{
	return tail;
}
void List::printlist()
{
	Link* temp = head;
	while (temp != NULL)
	{
		cout << " code: " << temp->getCode();
		cout << " name:" << temp->getName();
		cout << " period:" << temp->getPeriod();
		cout << " semester:" << temp->getSemaster();
		//cout<<" precondition:"<<temp->getPrecondition();
		temp = temp->getNext();
		cout << endl;
	}
}
