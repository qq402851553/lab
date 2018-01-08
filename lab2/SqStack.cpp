#include<iostream>

#define OVER_FLOW 0
#define UNDER_FLOW 0
#define SUCCESS 1

using namespace std;

template<class ElemType>
class SqStack
{
	protected:
		int count;
		int maxSize;
		ElemType *elems;
		
		bool Full()const;
		void Init(int size=40); 
		
		public:
			SqStack(int size=40);  //���캯��ģ�� 
			virtual ~SqStack();   //��������ģ�� 
			int Length() const;     // ��ջ���� 
			bool Empty() const;         //�ж�ջ�� 
			void Clear();
		    int Push(const ElemType &e);
			int Top(ElemType &e) const;
			int Pop(ElemType &e);
			SqStack(const SqStack<ElemType>&copy);
			SqStack <ElemType>&operator=(const SqStack<ElemType>&copy);
				 
};

   template<class ElemType>
   bool SqStack<ElemType>::Full()const
   {   //ջ����������true�����򷵻�false 
   	  return count==maxSize;
   }
       
   template<class ElemType>
   void SqStack<ElemType>:: Init(int size)
   {
   	  maxSize=size;
   	  if(elems!=NULL) delete []elems;
   	  elems=new ElemType[maxSize];
   	  count=0;
   }
   
   template<class ElemType>
     SqStack<ElemType>::SqStack(int size)
     {
     	elems=NULL;
     	Init(size);
	 }
	 
	 template <class ElemType>
	 SqStack <ElemType>::~SqStack()
	 {
	 	delete []elems;
	  } 
	  
	  template <class ElemType>
	 int SqStack<ElemType>::Length() const
	  {
	  	return count;
	  }
	  
	  template <class ElemType>
	  bool SqStack<ElemType>::Empty() const
	  {
	  	return count==0;
	  }
	  
	  template <class ElemType>
	  void SqStack<ElemType>::Clear()
	  {
	  	count=0;
	   } 
   
      template <class ElemType>
      int SqStack<ElemType>::Push(const ElemType &e)
      {
      	if(Full())
      	   return OVER_FLOW;
      	else 
      	{
      		elems[count++]=e;
      		return SUCCESS;
		  }
	  }
	  
	  template <class ElemType>
	  int SqStack<ElemType>::Top(ElemType &e)const
	  {
	  	  if(Empty())
	  	    return UNDER_FLOW;
	  	  else
	  	    {
	  	    	e=elems[count-1];
	  	    	return SUCCESS;
			  }
	  }
	  
	  template <class ElemType>
	  int SqStack<ElemType>::Pop(ElemType &e)
	  {
	  	if(Empty())
	  	  return UNDER_FLOW;
	  	else 
	  	  {
	  	  	e=elems[count-1];
			count--;
			return SUCCESS; 
		  }
	  }
	  
	  template <class ElemType>
	  SqStack<ElemType>::SqStack(const SqStack<ElemType>&copy)
	  {
	  	 elems=NULL;
	  	 Init(copy.maxSize);
	  	 count=copy.count;
	  	 for(int curPosition=1;curPosition<=Length();curPosition++)
		   {
		   	  elems[curPosition-1]=copy.elems[curPosition-1];
		   }
	  }
	  
	  template <class ElemType>
	  SqStack<ElemType>&SqStack<ElemType>::operator=(const SqStack<ElemType>&copy)
	  {
	  	if(copy!=this)
	  	{
	  		Init(copy.maxSize);
	  		count=copy.count;
	  	    for(int curPosition=1;curPosition<=Length();curPosition++)
		   {
		   	  elems[curPosition-1]=copy.elems[curPosition-1];
		   }
		}
		  return *this;
	  }
