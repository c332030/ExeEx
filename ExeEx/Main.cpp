#include <Windows.h>
#include <string>

#include "Tools.h"
#include "ExeEx.h"

using namespace std;

int exec(string lpCmdLine) {
	ExeEx exeEx;
	exeEx.execute(lpCmdLine);

	return 0;
}

/* 
	适用于代理控制台程序

	需要输出子进程控制台内容的情况
	c++ 菜鸟，getchar() 保证子程序的输出在当前程序运行结束前
*/
int main(int argc, char** args) {

	string str = "";
	for (int i = 1; i < argc; i++) {
		str += args[i];
	}

	exec(str);

	getchar();
	return 0;
}


/* 
	适用于代理非控制台程序

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nShowCmd
) {
	return exec(lpCmdLine);
}
*/