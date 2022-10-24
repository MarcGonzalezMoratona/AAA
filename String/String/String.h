#pragma once

class String {

private:

public:
	const char* str = nullptr;

	String& operator=(String&& s)
	{
		str = s.str;
		return *this;
	};

	String& operator+(String&& s)
	{
		return *this;
	}

	String();
	
	String(const char* s);
	
	//String(String&& s);

	//int length();

	//void clear();
};