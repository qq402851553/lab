#include<iostream>
#include"CourseList.h"
#include"Graph.h"
#include<fstream>
using namespace std;
static	List list;//存放初始课程信息
static  List sortedlist;// 存放拓扑排序后的课程信息（顺序）
static  int arraynum[8];//保存每个学期要开设的课程数目
static  int index; //共八个学期
static string courName;//从文件读取课程编码
static string courCode;//从文件读取课程名称
static string courPrecondition;//从文件读取课程的先决条件
static int courperiod;//从文件读取对应课程的开设学时数
static int coursemester;//从文件读取对应课程的开课学期

void readFromFile()
{
	fstream input;
	input.open("course_inf.txt");
	char ch;
	ch = input.get();
	while (!(ch >= '0'&&ch <= '9'))//开始出现数字时，开始读取arraynum[]
		ch = input.get();
	if (ch >= '0'&&ch <= '9' && (index<8))
	{
		while (ch != '\n')
		{
			if (ch >= '0'&&ch <= '9' && (index<8))
				arraynum[index++] = ch - 48;//将读入的字符转换成对应数字
			ch = input.get();
		}
	}
	while (ch != 'c')
		ch = input.get();
	while (ch != '\n')
		ch = input.get();//跳过所有注释行
	while (!input.eof())
	{
		if (ch == 'c')
		{
			while (ch != 9)
			{
				courCode.insert(courCode.size(), 1, ch);//读取courCode
				ch = input.get();
			}
			while (ch == 9)
				ch = input.get();
			while (ch != 9)
			{
				courName.insert(courName.size(), 1, ch);//读取courName
				ch = input.get();
			}
			while (ch == 9)
				ch = input.get();
			courperiod = ch - 48;//读取 courperiod
			ch = input.get();
			while (ch == 9)
				ch = input.get();
			coursemester = ch - 48;//读取coursemester
			ch = input.get();
			while (ch == 9)
				ch = input.get();
			if (ch == 'c')
				while (ch != '\n')//读取 courPrecondition
				{
					courPrecondition.insert(courPrecondition.size(), 1, ch);
					ch = input.get();
				}
		} //if
		ch = input.get();
		if (courCode.size()>0)
		{
			Link*courselink = new Link(courCode, courName, courperiod,
				coursemester, courPrecondition);//读取一次完整的信息即可将它生成一个Link节点
			list.addCourse(courselink);//将Link节点加入List
		}
		courCode.erase();//清除string中的内容，用于下一行次读取文件
		courName.erase();
		courPrecondition.erase();
	}//while	
	input.close();
}
//建图，添加有先决条件的结点之间的边
void buildGraph(List &courseList, Graph* courseGraph)
{
	Link* courselink = courseList.getHead();
	int v1 = 0;
	while (courselink != NULL)
	{
		string str = courselink->getPrecondition();
		for (int i = 0; str[i] != '\0';)
		{
			if (str[i] == 'c')//课程以c开头，由此分辨先决条件
			{
				char ch1 = str[++i];
				char ch2 = str[++i];
				int v2 = 10 * (ch1 - 48) + (ch2 - 48) - 1;//将课程号转换为整型数据,图的下标用int表示的
				courseGraph->setEdge(v2, v1, 1);
			}
			else
				i++;
		}
		v1++;
		courselink = courselink->getNext();
	}
}
void tophelp(Graph* G, int v)// Process v 
{
	G->setMark(v, 0);
	for (int w = G->first(v); w<G->n(); w = G->next(v, w))
		if (G->getMark(w) == 1)
			tophelp(G, w);
	Link* courselink = list.getHead();
	for (int i = 0; i<v; i++)
	{
		courselink = courselink->getNext();
	}
	sortedlist.insertCourse(courselink);//将拓扑排序的正序存入sortedlist中，用于课程的安排
}
void topsort(Graph* G) // Topological sort
{
	int i;
	for (i = 0; i<G->n(); i++) // Initialize 
		G->setMark(i, 1);
	for (i = 0; i<G->n(); i++) // Do vertices
		if (G->getMark(i) == 1)
			tophelp(G, i);       // Call helper
}
void courseArrange()//安排课表
{
	Link* temp = sortedlist.getHead();
	int count[8];
	for (int i = 0; i<8; i++)
		count[i] = 0;
	for (; count[0]<7 && temp != NULL; temp = temp->getNext())//优先安排已经预设学期的课程
	{
		if (temp->getSemaster() == 1)
			count[0]++;
		else if (temp->getSemaster() == 2)
			count[1]++;
		else if (temp->getSemaster() == 3)
			count[2]++;
		else if (temp->getSemaster() == 4)
			count[3]++;
		else if (temp->getSemaster() == 5)
			count[4]++;
		else if (temp->getSemaster() == 6)
			count[5]++;
		else if (temp->getSemaster() == 7)
			count[6]++;
		else if (temp->getSemaster() == 8)
			count[7]++;
	}
	temp = sortedlist.getHead();//再按学期顺序安排已经安排学期的课程，srtedlist中的先后顺序对应了学期的先后顺序
	for (; temp != NULL; temp = temp->getNext())
	{
		if (count[0]<arraynum[0])//semter1
		{
			if (temp->getSemaster() == 0)
			{
				temp->setSemester(1);
				count[0]++;
			}
		}
		else if (count[1]<arraynum[1])//semter2
		{
			if (temp->getSemaster() == 0)
			{
				temp->setSemester(2);
				count[1]++;
			}
		}
		else if (count[2]<arraynum[2])//semter3
		{
			if (temp->getSemaster() == 0)
			{
				temp->setSemester(3);
				count[2]++;
			}
		}
		else if (count[3]<arraynum[3])//semter4
		{
			if (temp->getSemaster() == 0)
			{
				temp->setSemester(4);
				count[3]++;
			}
		}
		else if (count[4]<arraynum[4])//semter5
		{
			if (temp->getSemaster() == 0)
			{
				temp->setSemester(5);
				count[4]++;
			}
		}
		else if (count[5]<arraynum[5])//semter6
		{
			if (temp->getSemaster() == 0)
			{
				temp->setSemester(6);
				count[5]++;
			}
		}
		else if (count[6]<arraynum[6])//semter7
		{
			if (temp->getSemaster() == 0)
			{
				temp->setSemester(7);
				count[6]++;
			}
		}
		else//semter8
		{
			if (temp->getSemaster() == 0)
			{
				temp->setSemester(8);
				count[7]++;
			}
		}
	}
}


void printSchoolTimeTable()//打印课表
{

	Link* temp = sortedlist.getHead();//semter1
	cout << "courses of semester 1 :" << endl;
	fstream output;
	output.open("course_table.txt");
	output << "第一学期课程: " << endl;
	for (; temp != NULL; temp = temp->getNext())
	{
		if (temp->getSemaster() == 1)
		{
			output << temp->getCode() << "  " << temp->getName() << endl;
			cout << temp->getCode() << "  " << temp->getName() << endl;
		}
	}

	temp = sortedlist.getHead();//semter2
	cout << "courses of semester 2 :" << endl;
	output << "第二学期课程: " << endl;
	for (; temp != NULL; temp = temp->getNext())
	{
		if (temp->getSemaster() == 2)
		{
			output << temp->getCode() << "  " << temp->getName() << endl;
			cout << temp->getCode() << "  " << temp->getName() << endl;
		}
	}

	temp = sortedlist.getHead();//semter3
	cout << "courses of semester 3 :" << endl;
	output << "第三学期课程: " << endl;
	for (; temp != NULL; temp = temp->getNext())
	{
		if (temp->getSemaster() == 3)
		{
			output << temp->getCode() << "  " << temp->getName() << endl;
			cout << temp->getCode() << "  " << temp->getName() << endl;
		}
	}

	temp = sortedlist.getHead();//semter4
	cout << "courses of semester 4 :" << endl;
	output << "第四学期课程: " << endl;
	for (; temp != NULL; temp = temp->getNext())
	{
		if (temp->getSemaster() == 4)
		{
			output << temp->getCode() << "  " << temp->getName() << endl;
			cout << temp->getCode() << "  " << temp->getName() << endl;
		}
	}

	temp = sortedlist.getHead();//semter5
	cout << "courses of semester 5 :" << endl;
	output << "第五学期课程: " << endl;
	for (; temp != NULL; temp = temp->getNext())
	{
		if (temp->getSemaster() == 5)
		{
			output << temp->getCode() << "  " << temp->getName() << endl;
			cout << temp->getCode() << "  " << temp->getName() << endl;
		}
	}

	temp = sortedlist.getHead();//semter6
	cout << "courses of semester 6 :" << endl;
	output << "第六学期课程: " << endl;
	for (; temp != NULL; temp = temp->getNext())
	{
		if (temp->getSemaster() == 6)
		{
			output << temp->getCode() << "  " << temp->getName() << endl;
			cout << temp->getCode() << "  " << temp->getName() << endl;
		}
	}

	temp = sortedlist.getHead();//semter7
	cout << "courses of semester 7 :" << endl;
	output << "第七学期课程: " << endl;
	for (; temp != NULL; temp = temp->getNext())
	{
		if (temp->getSemaster() == 7)
		{
			output << temp->getCode() << "  " << temp->getName() << endl;
			cout << temp->getCode() << "  " << temp->getName() << endl;
		}
	}

	temp = sortedlist.getHead();//semter8
	cout << "courses of semester 8 :" << endl;
	output << "第八学期课程: " << endl;
	for (; temp != NULL; temp = temp->getNext())
	{
		if (temp->getSemaster() == 8)
		{
			output << temp->getCode() << "  " << temp->getName() << endl;
			cout << temp->getCode() << "  " << temp->getName() << endl;
		}
	}
	output.close();
}






int main()
{
	readFromFile();//从文件读取课程信息
	Graphm graph(38);
	buildGraph(list, &graph);//做课程信息图	
	topsort(&graph);//对图进行拓扑排序
	//sortedlist.printlist();//打印排序后的结构
	cout << endl;
	courseArrange();//安排课表
	printSchoolTimeTable();//打印课表，并将其存入文件
	system("pause");
	return 0;
}
