#include <iostream>
#include <string>
#include <algorithm>
#include "lib.h"


using namespace std;


void sortAndReplace(string& str) {

	std::sort(str.begin(), str.end(), std::greater<char>());

	for (int i = 0; i < str.length(); ) {
		if ((str[i] - '0') % 2 == 0) {
			str.replace(i, 1, "KB");
			i = str.rfind("B");
		}
		i++;
	}
	
};

int calculateSum(const string& str) {
	int sum = 0;
	for (char c : str) {
		if (isdigit(c)) {
			sum += (c - '0');
		}
	}
	return sum;
};

bool checkString(const string& str) {
	
	bool flag = false;

	if (str.length() > 2 && atoi(str.c_str()) % 32 == 0) {
		flag = true;
	}

	return flag;
};
