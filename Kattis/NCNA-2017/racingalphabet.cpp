#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iomanip>

using namespace std;
const int SIZE = 28;
const double PI = 2.0 * acos(0.0);
const double LEN = (PI * 60.0) / SIZE;	// 2 * PI * R / SIZE
const double SPD = 15.0;
int idx[256];
string line;

void process(){
	getline(cin, line, '\n');

	char act = line[0];
	char nxt;
	
	int posAct, posNxt;
	int d;

	double res = 1.0;
	double t;

	for ( int i=1; i < (int)line.size(); ++i ){
		nxt = line[i];
		posAct = idx[ act ];
		posNxt = idx[ nxt ];

		d = abs( posAct - posNxt );
		d = min( d, SIZE - d );

		t = d * LEN / SPD;
		res += (t + 1.0);
		

		act = nxt;
	}
	cout << fixed << setprecision(9) << res << endl;
}

int main(){
	int runs;
	cin	>> runs;
	getline( cin, line, '\n' );
	
	for ( char c='A'; c <= 'Z'; ++c )
		idx[c] = c - 'A';
	idx[' '] = 26;
	idx['\''] = 27;

	while ( runs-- )
		process();
	return 0;
}
