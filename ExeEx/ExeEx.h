#pragma once

#include <Windows.h>
#include <string>

#include "Tools.h"
#include "LogUtils.h"

using namespace std;

class ExeEx
{
private:

	/*
	配置文件根名
*/
	const char* EXE_EX = "ExeEx";

	const char* EXTEND_EXE = "exe";
	const char* ARGS = "args";

	/*
		需要扩展的 exe 的名称
	*/
	const string EXE_EXTEND = "Ex";

	/*
		执行文件扩展名
	*/
	const string EXE_NAME = ".exe";

	/*
		配置文件扩展名
	*/
	const string INI = ".ini";

public:
	ExeEx();
	~ExeEx();

	string getExePath();

	string getExeName(string path);

	string getDirPath(string path);

	string getExeFilePath(string path);

	string getExecuteCommand(string lpCmdLine);

	bool writeExeEx(char*, string exeName);

	bool writeCmdLine(char*);

	void execute(string lpCmdLine);
};
