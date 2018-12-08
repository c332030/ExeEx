#pragma once

#include <string>

#define FAILURE -1

using namespace std;

class Tools
{
private:
	Tools();
	~Tools();
public:
	static int getCharIndexOfString(char chArr[], int arrLen, char ch, bool reverse);

	static char* string2PChar(string str);
};

