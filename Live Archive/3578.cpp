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
#include <list>

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
const int MAXN = 505;
int N;
int M;
int G[ MAXN ][2];
bool vis[ MAXN ];
int pos[MAXN];
int s;

void dfs( int u ){
	vis[u] = true;
	if ( u >= s )
		pos[ u - s ] = M++;
	else 
		pos[ N + u - s ] = M++;

	if ( !vis[ G[u][0] ] ) dfs( G[u][0] );
	if ( !vis[ G[u][1] ] ) dfs( G[u][1] );
}

int lis( int *S, int n ){
	int best[ MAXN ]; 
	int m = 1;
	best[ 0 ] = S[0];
	int p;

	for ( int i=0; i < n; ++i ){
		p = lower_bound( best , best + m , S[i] ) - best;
		if ( m == p ){
			best[ m++ ] = S[i];
		}
		else {
			best[ p ] = min( best[p] , S[i] );
		}
	}
	return m;
}

int main(){
	while ( scanf("%d",&N) && N ){
		for ( int i=0; i < N; ++i ){
			scanf("%d %d",&G[i][0],&G[i][1]);
			G[i][0]--,G[i][1]--;
		}
		bool ok = true;
		int res = -1;
		for ( int i=0; i < N && ok; ++i ){
			fill( vis, vis + N , false );
			M = 0;
			s = i;
			dfs( i );
			ok = M == N;
			if ( ok ){
				res = max( res , lis( pos + 1 , N - 1 ) );
				reverse( pos , pos + N );
				res = max( res , lis( pos , N - 1 ) );
			}
		}
		if ( !ok ) puts("Not solvable.");
		else {
			puts("Knot solvable.");
			printf("%d\n",N - 1 - res);
		}
	}
	return 0;
}

