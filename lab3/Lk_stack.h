
template<class Node_entry>

struct Node {

//  ���ݳ�Ա

   Node_entry entry;

   Node<Node_entry> *next;

//  ���캯��

   Node();

   Node(Node_entry item, Node<Node_entry> *add_on = NULL);

};

template<class Stack_entry>

class Stack {

public:

//  ��׼��ջ����

   Stack();

   bool empty() const;

   Error_code push(const Stack_entry &item);

   Error_code pop();

   Error_code top(Stack_entry &item) const;

   void clear();

//  ��ؽṹ�İ�ȫ����

   ~Stack();

   Stack(const Stack<Stack_entry> &original);

   void operator =(const Stack<Stack_entry> &original);

protected:

   Node<Stack_entry> *top_node;

};


template<class Node_entry>

Node<Node_entry>::Node()

{

   next = NULL;

}


template<class Node_entry>

Node<Node_entry>::Node(Node_entry item, Node<Node_entry> *add_on)

{

   entry = item;

   next = add_on;

}


template<class Stack_entry>

Stack<Stack_entry>::Stack()

{

   top_node=NULL;

}

template<class Stack_entry>

bool Stack<Stack_entry>::empty() const

{

  if(top_node==NULL)

     return true;

  else

     return false;

}


template<class Stack_entry>

Error_code Stack<Stack_entry>::push(const Stack_entry &item)

/*

Stack_entry �����ӵ���ջ�Ķ����������̬�ڴ��þ����򷵻سɹ��򷵻��������
*/

{

   Node<Stack_entry> *new_top = new Node<Stack_entry>(item, top_node);

   if (new_top == NULL) return overflow;

   top_node = new_top;

   return success;

}


template<class Stack_entry>

Error_code Stack<Stack_entry>::pop()

/*

 ջ�Ķ����ƶ��� ���ջΪ���򷵻����磻���򷵻سɹ��� 

*/

{

   Node<Stack_entry> *old_top = top_node;

   if (top_node == NULL) return underflow;

   top_node = old_top->next;

   delete old_top;

   return success;

}

template<class Stack_entry>

Error_code Stack<Stack_entry>::top(Stack_entry &item) const

{

   if(empty())

     return underflow;

   else{

     item=top_node->entry;

     return success;

   }

}


template<class Stack_entry>

void Stack<Stack_entry>::clear() //   ���Ԫ��

/*

ջ���

*/

{

   while (!empty())

      pop();

}


template<class Stack_entry>

Stack<Stack_entry>::~Stack() //  ��������

/*

ջ���

*/

{

clear();

}


template<class Stack_entry>

Stack<Stack_entry>::Stack(const Stack<Stack_entry> &original) //  ���ƹ��캯��

/*

���Ƶ�����������ʼ��

*/

{

   Node<Stack_entry> *new_copy, *original_node = original.top_node;

   if (original_node == NULL) top_node = NULL;

   else 

   {                         //  ������ص�

      top_node = new_copy = new Node<Stack_entry>(original_node->entry);

      while (original_node->next != NULL) 

  {

  original_node = original_node->next;

      new_copy->next = new Node<Stack_entry>(original_node->entry);

      new_copy = new_copy->next;

      }

   }

}


template<class Stack_entry>

void Stack<Stack_entry>::operator = (const Stack<Stack_entry> &original) //  Overload assignment

/*

����ջ����

*/

{

   Node<Stack_entry> *new_top, *new_copy, *original_node = original.top_node;

   if (original_node == NULL) new_top = NULL;

   else 

   {                         //  ������ص�

      new_copy = new_top = new Node<Stack_entry>(original_node->entry);

      while (original_node->next != NULL) 

  {

  original_node = original_node->next;

      new_copy->next = new Node<Stack_entry>(original_node->entry);

      new_copy = new_copy->next;

      }

   }

   while (!empty())               //  ���ԭջ���

      pop();

   top_node = new_top;            //  ���µ�ջ��ڴ���

}
