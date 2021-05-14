#include <iostream>

using namespace std;

int f[4][4];
int sr[4];
int sc[4];
int nr[4];
int nc[4];

void move(int r, int c, int k) {
	f[r - 1][c - 1] = k;
	sr[r - 1] += k;
	sc[c - 1] += k;
	nr[r - 1]++;
	nc[c - 1]++;
}

void pmove(int r, int c, int k, char* extra = "") {
	move(r, c, k);
	cout << r << " " << c << " " <<  k << extra << endl;
}

bool canwin(int s, int n) {
	return s >= 6 && s <= 9 && n == 3;
}

int main() {
	while (1) {
		int r;
		int c;
		int k;
		cin >> r >> c >> k;
		move(r, c, k);

		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				if (f[i - 1][j - 1] == 0) {
					if (canwin(sr[i - 1], nr[i - 1])) {
						pmove(i, j, 10 - sr[i - 1], " WIN");
						return 0;
					}
					if (canwin(sc[j - 1], nc[j - 1])) {
						pmove(i, j, 10 - sc[j - 1], " WIN");
						return 0;
					}
				}
		pmove(r, 5 - c, 5 - k);
	}
}
