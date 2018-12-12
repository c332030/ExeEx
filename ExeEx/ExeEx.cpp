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
	获取当前文件夹路径
*/
string ExeEx::getDirPath(string path) {

	if (path.empty()) {

		LogUtils::debug("getDirPath path 为空");
		return "";
	}

	int index = path.find_last_of('\\');
	if (index < 0) {

		LogUtils::debug("getDirPath path 中无 \\");
		return "";
	}

	//	cout << "\nindex= " << index << " = " << exeFilePath[index] << endl;

	return path.substr(0, index);
}

/*
	获取当前文件路径
*/
string ExeEx::getExeFilePath(string path) {

	if (path.empty()) {

		LogUtils::debug("getExeFilePath path 为空");
		return "";
	}

	int index = path.find_last_of('.');
	if (index < 0) {

		LogUtils::debug("getExeFilePath path 中无 .");
		return "";
	}

//	cout << "\nindex= " << index << " = " << exeFilePath[index] << endl;

	return path.substr(0, index);
}

/*
	获取文件名
*/
string ExeEx::getExeName(string path) {
	if (path.empty()) {

		LogUtils::debug("getExeName path 为空");
		return "";
	}

	int index = path.find_last_of('\\');
	if (index < 0) {

		LogUtils::debug("getExeName path 中无 \\");
		return "";
	}

	//	cout << "\nindex= " << index << " = " << exeFilePath[index] << endl;

	return path.substr(index + 1, path.length());
}

/*
	获取执行命令
*/
string ExeEx::getExecuteCommand() {

	/*
		当前 exe 路径
	*/
	const string path = getExePath();
	LogUtils::debug("path= " + path);
	if (path.empty()) {

		LogUtils::debug("exe 路径为空");
		return "";
	}

	/*
		当前文件夹路径
	*/
	const string dirPath = getDirPath(path);
	LogUtils::debug("dirPath= " + dirPath);
	if (dirPath.empty()) {

		LogUtils::debug("获取当前文件夹路径失败");
		return "";
	}

	/*
		当前文件路径，无扩展名
	*/
	string exeFilePath = getExeFilePath(path);
	LogUtils::debug("exeFilePath= " + exeFilePath);
	if (exeFilePath.empty()) {

		LogUtils::debug("获取配置文件路径失败");
		return "";
	}

	char *iniFile = Tools::string2PChar(exeFilePath + INI);

	LogUtils::debug(iniFile);

	/*
		文件名
	*/
	string exeName = getExeName(exeFilePath);
	LogUtils::debug("exeName= " + exeName);
	if (exeName.empty()) {
		LogUtils::debug("exeName 为空");
		return "";
	}

	{
		FILE* fh;
		if (fopen_s(&fh, iniFile, "r")) {

			LogUtils::debug("配置文件不存在");

			if (!writeExeEx(iniFile, exeName)
					|| !writeCmdLine(iniFile)
				) {
				LogUtils::debug("初始化配置文件失败");
			}
		}
	}

	/*
		扩展的 exe 名
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
		LogUtils::debug("extendExe 为空");

		if (!writeExeEx(iniFile, exeName)) {
			LogUtils::debug("初始化 exeName 配置失败");
		}
	}

	extendExe = dirPath + '\\' + extendExe;

	/*
		参数
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

		LogUtils::debug("args 为空");
		if (!writeCmdLine(iniFile)) {
			LogUtils::debug("初始化 args 配置失败");
		}
	}
	delete[] iniFile;

	string command = extendExe + ' ' + cmdLine;
//	LogUtils::debug("command= " + command);

	return command;
}

/*
	写入默认扩展 exe 名
*/
bool ExeEx::writeExeEx(char* iniPath, string exeName) {

	if (NULL == iniPath
			|| exeName.empty()
		) {
		LogUtils::debug("写入 exeEx 默认配置信息失败");
		return false;
	}

	char *exeNamePCh = Tools::string2PChar((exeName + EXE_EXTEND + EXE_NAME));

	bool result = WritePrivateProfileString(EXE_EX, EXTEND_EXE, exeNamePCh, iniPath);

	delete[] exeNamePCh;
	return result;
}

/*
	写入默认参数名
*/
bool ExeEx::writeCmdLine(char* iniPath) {

	if (NULL == iniPath) {
		LogUtils::debug("写入 cmdLine 默认配置信息失败");
		return false;
	}

	bool result = WritePrivateProfileString(EXE_EX, ARGS, "", iniPath);

	return result;
}


/*
	执行命令
*/
void ExeEx::execute(string lpCmdLine) {

	string commandStr = getExecuteCommand();

	LogUtils::debug(commandStr);

	char* commandPChar = Tools::string2PChar(commandStr + ' ' + lpCmdLine);

	LogUtils::debug(commandPChar);

	UINT result = WinExec(commandPChar, 0);

	LogUtils::debug("result= " + result);

	if (result < 31) {
		LogUtils::error("执行命令失败：" + commandStr);
	}

	delete[] commandPChar;
}
