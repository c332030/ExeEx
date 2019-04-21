#include "LogUtils.h"


LogUtils::LogUtils(){}

LogUtils::~LogUtils(){}

void console(string str) {
	//cout << str << endl;
}

void LogUtils::trace(string str) {
	console(str);
}

void LogUtils::debug(string str) {
	console(str);
}

void LogUtils::info(string str) {
	console(str);
}

void LogUtils::warn(string str) {
	console(str);
}

void LogUtils::error(string str) {
	console(str);
}
