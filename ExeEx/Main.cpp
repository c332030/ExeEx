#include <Windows.h>
#include <string>

#include "Tools.h"
#include "ExeEx.h"

using namespace std;
/*
int main(int argc, char** args) {

	ExeEx exeEx;
	exeEx.execute("");

	getchar();

	return 0;
}
*/
/**/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nShowCmd
) {
	ExeEx exeEx;
	exeEx.execute(lpCmdLine);

	return 0;
}

