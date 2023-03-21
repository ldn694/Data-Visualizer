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

double dist2p(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

sf::Time min(const sf::Time& a, const sf::Time& b) {
	return a < b ? a : b;
}

sf::Time max(const sf::Time& a, const sf::Time& b) {
	return a > b ? a : b;
}
