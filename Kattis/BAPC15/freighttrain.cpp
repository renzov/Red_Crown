#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXW = 10005;
int N, W, L;
int w[MAXW];

bool possible( int len ){
	// Apply greedy algorithm
	int i = 0;
	int beg = 1;
	int cntTrains = L;

	while ( beg <= N && cntTrains > 0 ){
		if ( i >= W ){ // Already tranport all to luxemburg
			cntTrains--;
			beg = N + 1; // tranport all to amsterdam
		}
		else {
			if ( (N - beg + 1) <= len ){ // Move all to luxemburg
				cntTrains--;
				beg = N + 1;
			}
			else { 
				if ( (w[i] - beg + 1) > len ){ // Can not move the next full wagon
					// Move to amsterdam from beg to w[i] - 1
					cntTrains--; 
					beg = w[i];
				}
				else {
					do {
						i++;
					}
					while ( i < W && ( w[i] - beg + 1) <= len );
					// Move those trains to luxemburg
					beg = beg + len; 
					cntTrains--;
				}
			}
		}
	}
	return beg > N;
}

int main(){
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d", &N, &W, &L);
		for ( int i=0; i < W; ++i ) scanf("%d", w + i );
		// Binary search the answer	
		int l = 0;
		int r = (N + L  - 1) / L;
		int m;
		while ( r - l > 1 ){
			m = ( l + r ) >> 1;
			if ( possible( m ) ) r = m;
			else l = m;
		}
		printf("%d\n", r);
	}
	return 0;
}

