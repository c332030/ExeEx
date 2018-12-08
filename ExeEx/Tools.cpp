#include "Tools.h"

Tools::Tools() {}


Tools::~Tools() {}

int Tools::getCharIndexOfString(char chArr[], int arrLen, char ch, bool reverse = false) {
	if (NULL == chArr) {
		return FAILURE;
	}

	if (reverse) {

		for (int i = arrLen - 1; i >= 0 && '\0' != chArr[i]; i--) {
			if (ch == chArr[i]) {
				return i;
			}
		}
	}
	else {

		for (int i = 0; i < arrLen && '\0' != chArr[i]; i++) {
			if (ch == chArr[i]) {
				return i;
			}
		}
	}

	return FAILURE;
}

char* Tools::string2PChar(string str) {
	if (str.empty()) {
		return NULL;
	}

	int len = str.length() + 1;
	char *iniFile = new char[len];
	
	str.copy(iniFile, str.length(), 0);
	iniFile[str.length()] = '\0';

	return iniFile;
}
