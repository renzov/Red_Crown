#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<climits>
#include<cstdlib>
using namespace std;
const int MAXN = 21;

int N;
int M;
map<string, int> idx;

bool cover[1 << MAXN] = {0};
int X[MAXN + 5], Y[MAXN + 5], P[MAXN + 5];
string W[MAXN + 5];

int tour[1 << MAXN][ MAXN ];

inline int dist( const int &i, const int &j ){
	return abs( X[i] - X[j] ) + abs( Y[i] - Y[j] ); 
}

inline bool in( const int &mask, const int &p ){
	return ( mask >> p ) & 1;
}

int main(){

	cin >> N;
	M = 0;
	for ( int i=0; i < N; ++i ){
		cin >> X[i] >> Y[i] >> W[i];
		if ( idx.find( W[i] ) == idx.end() )
			idx[ W[i] ] = M++;
		P[i] = idx[ W[i] ];
	}
	// Find subsets that cover every pokemon
	int all = (1 << M) - 1;
	for ( int mask=1; mask < (1 << N); ++mask ){
		int covered = 0;
		for ( int i=0; i < N; ++i )
			if ( in( mask, i ) )
				covered |= ( 1 << P[i] );
		cover[ mask ] = covered == all;
	} 
	// Do TSP DP, we start and end at point (0,0)
	int sub;
	int res = INT_MAX;
	// Initialize
	for ( int i=0; i < N; ++i ){
		tour[ 1 << i ][ i ] = abs( X[i] ) + abs( Y[i] );
		if ( cover[ 1 << i ] ){
			res = min( res, tour[ 1 << i ][i] + abs( X[i] ) + abs( Y[i] ) );
		}
	}

	for ( int mask=3; mask < (1 << N); ++mask ){
		
		if ( ( mask & ( mask - 1 ) ) == 0 ) continue;

		for ( int i=0; i < N; ++i ){
			tour[mask][i] = INT_MAX;
			if ( in( mask, i ) ){
				sub = mask ^ ( 1 << i );
				for ( int j=0; j < N; ++j )
					if ( in( sub, j ) && tour[sub][j] < INT_MAX ){
						tour[mask][i] = min( tour[mask][i], tour[sub][j] + dist( i, j ) );
					}
				if ( cover[mask] ){
					res = min( res, tour[mask][i] + abs( X[i] ) + abs( Y[i] ) );
				}
			}	
		}
	}
	printf("%d\n", res);
	return 0;
}
