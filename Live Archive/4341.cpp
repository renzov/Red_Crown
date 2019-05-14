#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
using namespace std;

const int MAXN = 1024;
int L[MAXN];

void process(){
	string line, word;
	getline(cin, line);
	istringstream in(line);
	int N = 0;

	while ( in >> word )
		L[N++] = word.length();
	
	int res = 0;
	int last = 0;
	int cnt = 0;

	for ( int i=0; i < N; ++i )
		if ( last == L[i] ){
			cnt++;
		}
		else {
			res = max( res, cnt );
			cnt = 1;
			last = L[i];
		}
	res = max( res, cnt );
	cout << res << endl;
}

int main(){
	int runs;
	string trash;
	cin >> runs;
	getline(cin, trash); // read the newline character
	while ( runs-- )
		process();
	return 0;
}
