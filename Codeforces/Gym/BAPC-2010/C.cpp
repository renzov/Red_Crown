#include<iostream>
#include<algorithm>
using namespace std;
const int SIZE = 1 << 9;
const int MOD = 10007;

int base;
int cnt[SIZE][SIZE];

inline int bit( const int &x, const int &p ){ return (x >> p) & 1; }

void backtrack( const int idx, const int &cur, const int &nxt ){
	if ( idx >= 9 ){
		cnt[base][nxt]++;
		cnt[base][nxt] %= MOD;
		return;
	}
	if ( bit( cur, idx ) ){
		backtrack( idx + 1, cur, nxt );
		return;
	}
	// test on the 3rd dimension
	backtrack( idx + 1, cur | (1 << idx), nxt | (1 << idx) );
	// test horizontally
	if ( ((idx % 3) < 2) && !bit( cur, idx + 1 ) )
		backtrack( idx + 2, cur | (1 << idx) | (1 << (idx + 1)), nxt );
	// test vertically
	if ( (( idx / 3 ) < 2) && !bit( cur, idx + 3 ) )
		backtrack( idx + 1, cur | ( 1 << idx ) | (1 << (idx + 3))  , nxt );
}

void preprocess(){
	for ( int mask = 0; mask < SIZE; ++mask ){
		base = mask;
		backtrack( 0, mask, 0 );
	}
}

void process(){

}


int main(){
	int T;
	preprocess();
	for ( int i = 0; i < SIZE; i++ ){
		for ( int j = 0; j < SIZE; ++j ){
			cout << cnt[i][j] << ' ';
		}
		cout << '\n';
	}
	//scanf("%d", &T);
	//while ( T-- )
	//	process();
	return 0;
}
