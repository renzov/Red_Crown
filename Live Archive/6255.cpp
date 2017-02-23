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

const int MAXS = (1 << 20);
int d[25][25];
int N;
int sum[25];
bool vis[ MAXS ];

void dfs( int S ){
	vis[S] = true;
	for ( int i=0; i < N; ++i ){
		if ( ((S >> i) & 1) && sum[i] < 0 ){
			if ( !vis[S ^ (1<<i)] ){ 
				for ( int j=0; j < N; ++j ) if ( (S>>j)&1 )
					sum[ j ] += d[j][i];
				dfs( S ^ (1<<i) );
				for ( int j=0; j < N; ++j ) if ( (S>>j)&1 )
					sum[ j ] -= d[j][i];
			}
		}
	}
}

int main(){
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				scanf("%d", &d[i][j]);
		fill( sum, sum + N, 0 );
		fill( vis, vis + (1<<N), false );
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				sum[i] -= d[i][j];
		dfs( (1<<N) - 1 );
		int cnt = 0;
		for ( int i=0; i < N; ++i ){
			if ( vis[1<<i] ){
				if (cnt) putchar(' ');
				printf("%d", i+1);
				cnt++;
			}
		}
		if ( cnt == 0 ) printf("0");
		puts("");
	}
	return 0;
}

