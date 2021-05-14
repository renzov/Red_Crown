/*
    Solution for NEERC'2010 Problem X: Xtrapolation
    (C) Roman Elizarov
*/

#include <iostream>

using namespace std;

int main() {
	long long sum = 0;
	while (true) {
		int num;
		cin >> num;
		if (num == 0)
			break;
		sum += num;
		cout << sum << endl;
	}
	return 0;
}
