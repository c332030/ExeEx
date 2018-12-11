#include <Windows.h>
#include <string>

#include "Tools.h"
#include "ExeEx.h"

using namespace std;
/*
int main() {

	ExeEx exeEx;
	exeEx.execute();

	getchar();

	return 0;
}
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nShowCmd
) {
	ExeEx exeEx;
	exeEx.execute();


	return 0;
}
