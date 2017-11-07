#pragma once
#include "DblLinkList.cpp"
#include"String.h"
#include"oprations.h"
#include "string.h"

char *replace(char *src, char *sub, char *dst)
{
	int pos = 0;
	int offset = 0;
	int srcLen, subLen, dstLen;
	char *pRet = NULL;

	srcLen = strlen(src);
	subLen = strlen(sub);
	dstLen = strlen(dst);
	pRet = (char *)malloc(srcLen + dstLen - subLen + 1);
	if (NULL != pRet)
	{
		pos = strstr(src, sub) - src;
		memcpy(pRet, src, pos);
		offset += pos;
		memcpy(pRet + offset, dst, dstLen);
		offset += dstLen;
		memcpy(pRet + offset, src + pos + subLen, srcLen - pos - subLen);
		offset += srcLen - pos - subLen;
		*(pRet + offset) = '\0';
	}
	return pRet;
}

void find(DblLinkList<String> &text)
{
	cout << "what string:" << endl;
	char str1[100];
	cin >> str1;
	int n = 0;
	text.moveToHead(); text.moveToNext();
	for (int i = 0; i < text.getSize(); i++)
	{
		if (text.getData().include(str1))
		{
			cout << text.getPos() << ":" << text.getData() << endl; n++;
		}
		text.moveToNext();
	}
	cout<<n << "  lines found" << endl;

}




void subs(DblLinkList<String> &text)
{
	char str1[10];
	cout << "from what:" << endl;
	cin >> str1;
	char str2[10];
	cout << "to what:" << endl;
	cin >> str2;

	text.moveToHead(); text.moveToNext();
	for (int i = 0; i < text.getSize(); i++)
	{
		while (text.getData().include(str1))
		{
			text.insert(replace((char*)text.getData().c_str(), str1, str2));
			text.remove(text.getPos() - 1);
		}
		text.moveToNext();
	}
	cout << "subs finished" << endl;
}


int main()
{


	DblLinkList<String> text;
	read(text);
	help();
	run();
	char ch;
	ch = getchar();
	while(1)
	{
	switch (ch)
		{
		case'h':help(); run(); break;
		case'a':head(text); run(); break;
		case'o':show(text); run(); break;
		case'e':end(text); run(); break;
		case'p':pre(text); run(); break;
		case'n':next(text); run(); break;
		case'g':go(text); run(); break;
		case'i':insert(text); run(); break;
		case'd':deleteTo(text); run(); break;
		case'c':subCurLine(text); run(); break;
		case'u':count(text); run(); break;
		case'f':find(text); run(); break;
		case'b':subs(text); run(); break;
		case'r':read(text); run(); break;
		case'w':writeTo(text); run(); break;
		case'q':quit(); run(); break;
		default:break;

		}
	
	ch = getchar();
	}


	system("pause");
	return 0;
}
