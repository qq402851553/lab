#include"SqStack.cpp"
#include<ctype.h>

   void readNumber(char*& p,SqStack<double>& sta);
   double cal(double num1,char op,double num2);
   char orderBetween(char ch1,char ch2);
   
  double evaluate(char* s)
  {
  	char temp; 
  	SqStack<double> opnd;//������ջ 
  	SqStack<char> optr;//�����ջ 
  	optr.Push('\0');
  	while(!optr.Empty())
  	{
  	   if(isdigit(*s))	
  	      readNumber(s,opnd);
  	   else
  	   {
  	   	    optr.Top(temp);   //tempΪջ���������*sΪ��ǰ����� 
		    switch(orderBetween(temp,*s))
		   {
		   	  case '<':
		   	  	optr.Push(*s);s++;break;
		   	  case '=':
		   	  	optr.Pop(temp);s++;break;
		   	  case '>':
		   	  	 char op;optr.Pop(op);
		   	  	 double data1;opnd.Pop(data1);
		   	  	 double data2;opnd.Pop(data2);
		   	  	 opnd.Push(cal(data2,op,data1));
		   	  	 break;
		   }
	   }
	}
     double result;opnd.Pop(result);return result;  //��������ջ�����ؽ�� 
  }
  
     void  readNumber(char*& p,SqStack<double>& sta)  //���ַ����е������ַ�ת��Ϊ���� 
      {
      	sta.Push(double(*p-'0'));
      	while(isdigit(*(++p)))
      	{
      		double temp1;sta.Pop(temp1);
      		sta.Push(temp1*10+double(*p-'0'));
		}
		if('.'!=*p) return;
		double fraction=1;
		while(isdigit(*(++p)))
		{
			double temp2;sta.Pop(temp2);
			sta.Push(temp2+(*p-'0')*(fraction/=10));
		}
	  }
	  
	  double cal(double num1,char op,double num2)  //���� 
	  {
	  	switch(op)
	  	{
	  		case '+':
	  			return num1+num2;break;
	  		case '-':
	  			return num1-num2;break;
	  		case '*':
	  			return num1*num2;break;
	  		case '/':
	  			return num1/num2;break;
		}
	  }
	  char orderBetween(char ch1,char ch2)  //�Ƚ�ջ��������뵱ǰ�ַ���������������ȼ� 
	  {
	  	int char1;int char2;
	  	switch(ch1)
	  	{
	  		case '+':
	  			char1=0;break;
	  		case '-':
	  			char1=1;break;
	  		case '*':
	  			char1=2;break;
	  		case '/':
	  			char1=3;break;
	  		case '(':
	  			char1=4;break;
	  		case ')':
	  			char1=5;break;
	  		case '\0':
	  			char1=6;break;
		}
		switch(ch2)
	  	{
	  		case '+':
	  			char2=0;break;
	  		case '-':
	  			char2=1;break;
	  		case '*':
	  			char2=2;break;
	  		case '/':
	  			char2=3;break;
	  		case '(':
	  			char2=4;break;
	  		case ')':
	  			char2=5;break;
	  		case '\0':
	  			char2=6;break;
	  			
		}
		const char pre[7][7]={
		//��ǰ�����     |------------------------------------| 
	   //         +    -    *    /    (    )    \0
		         '>', '>', '<', '<', '<', '>', '>',
		         '>', '>', '<', '<', '<', '>', '>',
		         '>', '>', '>', '>', '<', '>', '>',
		         '>', '>', '>', '>', '<', '>', '>',
		         '<', '<', '<', '<', '<', '=', ' ',
		         ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		         '<', '<', '<', '<', '<', ' ', '=',
			    };
			return pre[char1][char2];
	  }
