#include "ExeEx.h"

ExeEx::ExeEx() {}


ExeEx::~ExeEx() {}

string ExeEx::getExePath() {

	char path[MAX_PATH];
	memset(path, 0, MAX_PATH);
	GetModuleFileName(NULL, path, MAX_PATH);

	LogUtils::debug(path);

	return path;
}

/*
	��ȡ��ǰ�ļ���·��
*/
string ExeEx::getDirPath(string path) {

	if (path.empty()) {

		LogUtils::debug("getDirPath path Ϊ��");
		return "";
	}

	int index = path.find_last_of('\\');
	if (index < 0) {

		LogUtils::debug("getDirPath path ���� \\");
		return "";
	}

	//	cout << "\nindex= " << index << " = " << exeFilePath[index] << endl;

	return path.substr(0, index);
}

/*
	��ȡ��ǰ�ļ�·��
*/
string ExeEx::getExeFilePath(string path) {

	if (path.empty()) {

		LogUtils::debug("getExeFilePath path Ϊ��");
		return "";
	}

	int index = path.find_last_of('.');
	if (index < 0) {

		LogUtils::debug("getExeFilePath path ���� .");
		return "";
	}

//	cout << "\nindex= " << index << " = " << exeFilePath[index] << endl;

	return path.substr(0, index);
}

/*
	��ȡ�ļ���
*/
string ExeEx::getExeName(string path) {
	if (path.empty()) {

		LogUtils::debug("getExeName path Ϊ��");
		return "";
	}

	int index = path.find_last_of('\\');
	if (index < 0) {

		LogUtils::debug("getExeName path ���� \\");
		return "";
	}

	//	cout << "\nindex= " << index << " = " << exeFilePath[index] << endl;

	return path.substr(index + 1, path.length());
}

/*
	��ȡִ������
*/
string ExeEx::getExecuteCommand() {

	/*
		��ǰ exe ·��
	*/
	const string path = getExePath();
	LogUtils::debug("path= " + path);
	if (path.empty()) {

		LogUtils::debug("exe ·��Ϊ��");
		return "";
	}

	/*
		��ǰ�ļ���·��
	*/
	const string dirPath = getDirPath(path);
	LogUtils::debug("dirPath= " + dirPath);
	if (dirPath.empty()) {

		LogUtils::debug("��ȡ��ǰ�ļ���·��ʧ��");
		return "";
	}

	/*
		��ǰ�ļ�·��������չ��
	*/
	string exeFilePath = getExeFilePath(path);
	LogUtils::debug("exeFilePath= " + exeFilePath);
	if (exeFilePath.empty()) {

		LogUtils::debug("��ȡ�����ļ�·��ʧ��");
		return "";
	}

	char *iniFile = Tools::string2PChar(exeFilePath + INI);

	LogUtils::debug(iniFile);

	/*
		�ļ���
	*/
	string exeName = getExeName(exeFilePath);
	LogUtils::debug("exeName= " + exeName);
	if (exeName.empty()) {
		LogUtils::debug("exeName Ϊ��");
		return "";
	}

	{
		FILE* fh;
		if (fopen_s(&fh, iniFile, "r")) {

			LogUtils::debug("�����ļ�������");

			if (!writeExeEx(iniFile, exeName)
					|| !writeCmdLine(iniFile)
				) {
				LogUtils::debug("��ʼ�������ļ�ʧ��");
			}
		}
	}

	/*
		��չ�� exe ��
	*/
	string extendExe;
	{
		char extendExeArr[MAX_PATH];
		memset(extendExeArr, 0, MAX_PATH);
		GetPrivateProfileString(EXE_EX, EXTEND_EXE, "", extendExeArr, MAX_PATH, iniFile);

		extendExe = extendExeArr;
		LogUtils::debug("extendExe= " + extendExe);
	}

	if (extendExe.empty()) {
		LogUtils::debug("extendExe Ϊ��");

		if (!writeExeEx(iniFile, exeName)) {
			LogUtils::debug("��ʼ�� exeName ����ʧ��");
		}
	}

	extendExe = dirPath + '\\' + extendExe;

	/*
		����
	*/
	string cmdLine;
	{
		char argsArr[MAX_PATH];
		memset(argsArr, 0, MAX_PATH);
		GetPrivateProfileString(EXE_EX, ARGS, "", argsArr, MAX_PATH, iniFile);

		cmdLine = argsArr;
		LogUtils::debug("args= " + cmdLine);
	}
	if (cmdLine.empty()) {

		LogUtils::debug("args Ϊ��");
		if (!writeCmdLine(iniFile)) {
			LogUtils::debug("��ʼ�� args ����ʧ��");
		}
	}
	delete[] iniFile;

	string command = extendExe + ' ' + cmdLine;
//	LogUtils::debug("command= " + command);

	return command;
}

/*
	д��Ĭ����չ exe ��
*/
bool ExeEx::writeExeEx(char* iniPath, string exeName) {

	if (NULL == iniPath
			|| exeName.empty()
		) {
		LogUtils::debug("д�� exeEx Ĭ��������Ϣʧ��");
		return false;
	}

	char *exeNamePCh = Tools::string2PChar((exeName + EXE_EXTEND + EXE_NAME));

	bool result = WritePrivateProfileString(EXE_EX, EXTEND_EXE, exeNamePCh, iniPath);

	delete[] exeNamePCh;
	return result;
}

/*
	д��Ĭ�ϲ�����
*/
bool ExeEx::writeCmdLine(char* iniPath) {

	if (NULL == iniPath) {
		LogUtils::debug("д�� cmdLine Ĭ��������Ϣʧ��");
		return false;
	}

	bool result = WritePrivateProfileString(EXE_EX, ARGS, "", iniPath);

	return result;
}


/*
	ִ������
*/
void ExeEx::execute(string lpCmdLine) {

	string commandStr = getExecuteCommand();

	LogUtils::debug(commandStr);

	char* commandPChar = Tools::string2PChar(commandStr + ' ' + lpCmdLine);

	LogUtils::debug(commandPChar);

	UINT result = WinExec(commandPChar, 0);

	LogUtils::debug("result= " + result);

	if (result < 31) {
		LogUtils::error("ִ������ʧ�ܣ�" + commandStr);
	}

	delete[] commandPChar;
}
