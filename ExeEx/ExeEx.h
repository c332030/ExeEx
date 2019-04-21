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
	�����ļ�����
*/
	const char* EXE_EX = "ExeEx";

	const char* EXTEND_EXE = "exe";
	const char* ARGS = "args";

	/*
		��Ҫ��չ�� exe ������
	*/
	const string EXE_EXTEND = "Ex";

	/*
		ִ���ļ���չ��
	*/
	const string EXE_NAME = ".exe";

	/*
		�����ļ���չ��
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
