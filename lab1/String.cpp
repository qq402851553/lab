#pragma once
#include "String.h"



String::String()
{
	length = 0;
	data = new char[1];
	*data = '\0';

}

String::String(const char * str)
{
	if (!str)
	{
		length = 0;
		data = new char[1];
		*data = '\0';
	}
	else
	{
		length = strlen(str);
		data = new char[length + 1];
		strcpy_s(data,length+1, str);
	}


}

String::String(const String & str)
{
	length = str.size();
	data = new char[length + 1];
	strcpy_s(data, length + 1, str.c_str());

}

String::~String()
{
	delete[]data;
	length = 0;

}

String String::operator+(const String & str) const
{
	String newString;
	newString.length = length + str.size();
	newString.data = new char[newString.length + 1];
	strcpy_s(newString.data, newString.length+1, data);
	strcat_s(newString.data, newString.length + 1, str.data);
	return newString;

}

String & String::operator=(const String & str)
{
	if (this == &str)	return *this;

	delete[]data;
	length = str.length;
	data = new char[length + 1];
	strcpy_s(data, length + 1, str.c_str());
	return *this;

}

String & String::operator+=(const String & str)
{
	length += str.length;
	char *newData = new char[length + 1];
	strcpy_s(newData,length+1, data);
	strcat_s(newData, length + 1, str.data);
	delete[]data;
	data = newData;
	return *this;

}

bool String::operator==(const String & str) const
{
	if (length != str.length)	return false;
	return strcmp(data, str.data) ? false : true;

}

char & String::operator[](int n) const
{
	if (n >= length) return data[length - 1]; 
	else return data[n];

}

int String::size() const
{
	return length;

}

const char * String::c_str() const
{
	return data;

}

bool String::include(const char * str)
{
	bool bo;
	bo=((strstr(this->data, str) == NULL)?false :  true);
	return bo;
}





istream & operator >> (istream & is, String & str)
{
	char tem[1000];  
	is >> tem;
	str.length = strlen(tem);
	str.data = new char[str.length + 1];
	strcpy_s(str.data, str.length + 1, tem);
	return is;

}

ostream & operator<<(ostream & os, String & str)
{
	os << str.data;
	return os;

}
