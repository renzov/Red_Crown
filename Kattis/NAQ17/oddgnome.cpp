#include<iostream>
using namespace std;

int main(){
	int N;
	int last, x;
	int res;
	int runs;

	cin >> runs;
	while ( runs-- ){
		cin >> N;
		bool found = false;
		for ( int i=0; i < N; ++i ){
			cin >> x;
			if ( found ) continue;
			if ( i ){
				if ( x != last + 1 )
					res = i + 1, found = true;
			}
			last = x;
		}
		cout << res << endl;
	}
	return 0;
}
