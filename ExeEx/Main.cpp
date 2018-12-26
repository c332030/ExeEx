#include <Windows.h>
#include <string>

#include "Tools.h"
#include "ExeEx.h"

using namespace std;

int exec(PSTR lpCmdLine) {
	ExeEx exeEx;
	exeEx.execute(lpCmdLine);

	getchar();

	return 0;
}

/*
int main(int argc, char** args) {
	return exec("");
}
*/

/**/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nShowCmd
) {
	return exec(lpCmdLine);
}
