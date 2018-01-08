#include<iostream>
#include"evaluate.h"
using namespace std;

bool judge(char* s);
int main()
{
	char s[100];
    cin>>s;
    while(judge(s)==false)
      {
	   cout<<"����ʽ��������������: "<<"\n";
	   cin>>s; 
	  } 
    cout<<evaluate(s)<<endl;
	system("pause");
	return 0;
}

  bool judge(char* s)
  {
  	int flag=1;
  	while(*s!='\0'){
	     if(!(*s>=40 && *s<=43) && *s!=45 && *s!=47 && !(*s>='0' && *s<='9'))
  	   {
  	   	   flag=0;
	   }
		 s++;
          if(flag==0)
            {
                return false;
				break; 
			}
	  }
	  return true;
  }
