#include <Windows.h>
#include <string>

#include "Tools.h"
#include "ExeEx.h"


#include <iostream>

using namespace std;

int main() {

	ExeEx exeEx;
	exeEx.execute();

	getchar();

	return 0;
}
/*
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nShowCmd
) {
	/*
	PSTR cmdLine = "VSCode.exe";
	cmdLine.append(lpCmdLine);




	return 0;
}
*/
