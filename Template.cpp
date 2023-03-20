#include <string>
#include "Template.h"

int stringToInt(std::string& a) {
	int res = 0;
	for (int i = 0; i < (int)a.size(); i++) {
		res = res * 10 + (a[i] - '0');
	}
	return res;
}

std::string intToString(int a) {
	std::string res;
	while (a > 0) {
		res.push_back(char(a % 10 + '0'));
		a /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}