
#include"Utility.h"

#include"Lk_stack.h"

#include"Huffman.h"

void main() 

{

HuffmanTree hf;

char c=0;

while(c!='3')  

{

cout<<endl<<"1.Huffman compress.";

cout<<endl<<"2.Huffman decompress.";

cout<<endl<<"3.Exit.";

cout<<endl<<"Please select:";

cin>>c;

switch(c)

{

case '1':   

hf.Code();

break;

case '2':

hf.UnCode();

}system("pause");

}system("pause");

system("pause");
}
