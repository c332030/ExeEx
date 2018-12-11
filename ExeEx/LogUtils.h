#pragma once

#include <string>

//#include <iostream>

using namespace std;

class LogUtils
{
public:
	LogUtils();
	~LogUtils();

	static void trace(string str);
	static void debug(string str);
	static void info(string str);
	static void warn(string str);
	static void error(string str);
};

