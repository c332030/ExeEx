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
	�����ڴ������̨����

	��Ҫ����ӽ��̿���̨���ݵ����
	c++ ����getchar() ��֤�ӳ��������ڵ�ǰ�������н���ǰ
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
	�����ڴ���ǿ���̨����

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nShowCmd
) {
	return exec(lpCmdLine);
}
*/