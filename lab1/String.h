#pragma once
#include<iostream>
#include<string.h>

using namespace std;

class String
{
private:
	char* data;
	int length;
public:
	String();
	String(const char* str);
	String(const String &str);
	~String();
	
	String operator+(const String &str) const;
	String& operator=(const String &str);
	String& operator+=(const String &str);
	bool operator==(const String &str) const;
	char& operator[](int n) const;
	int size() const;
	const char* c_str() const;
	bool include(const char* str);

	friend istream& operator >> (istream &is, String &str);
	friend ostream& operator<<(ostream &os, String &str);
};
