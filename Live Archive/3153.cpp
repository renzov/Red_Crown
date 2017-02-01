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

const int MAXT = 420;

int M;
int N;
int best;
int t[25];
int C[25][25];

bool cmp( const int &i, const int &j ){
	return t[i] < t[j];
}

void backtrack( int u, int S, int left ,int size ){
	if ( left < 0 ) return;
	if ( size > best ) best = size;
	if ( size >= M ) return;
	if ( (M-size) <= (best-size) ) return; 
	
	for ( int v=0, w; v < N; ++v ){
		if ( !((S >> v)&1) ){
			w = C[u][v] + t[v];
			backtrack( v, S | (1<<v), left - w, size+1 );
		}
	}
}

int main(){
	int ord[25];
	
	while ( scanf("%d", &N) && N ){
		for ( int i=0; i < N; ++i ){ 
			scanf("%d", t+i);
			ord[i] = i; 	
		}
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j ){
				scanf("%d", &C[i][j]);
			}

		for ( int k=0; k < N; ++k )
			for ( int i=0; i < N; ++i )
				for ( int j=0; j < N; ++j )
					if ( C[i][j] > (C[i][k] + C[k][j]) )
						C[i][j] = C[i][k] + C[k][j];

		sort( ord, ord + N, cmp );
		int sum = 0;
		for ( M = 0; M < N && (sum=sum+t[ord[M]]) <= MAXT; ++M );
	
		best = 0;
		for ( int i=0; i < N; ++i ){
			if ( t[ord[i]] <= MAXT )
				backtrack( ord[i], 1 << ord[i], MAXT - t[ ord[i] ] , 1 );
		}
		printf("%d\n", best);
	}
	return 0;
}

