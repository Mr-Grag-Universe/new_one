#pragma once
#include <iostream>
#include <string>

bool translator(std::string & a, int & b) {
	int l = a.size();
	for (int i = 0; i < l; ++i) {
		if (a[i] > '9' || a[i] < '0') { return 0; }
		int k = pow(10, l - i - 1);
		switch (a[i]) {
			case '0': break;
			case '1': b += 1 * k; break;
			case '2': b += 2 * k; break;
			case '3': b += 3 * k; break;
			case '4': b += 4 * k; break;
			case '5': b += 5 * k; break;
			case '6': b += 6 * k; break;
			case '7': b += 7 * k; break;
			case '8': b += 8 * k; break;
			case '9': b += 9 * k; break;
		}
	}
	//std::cout << b;
	return 1;
}