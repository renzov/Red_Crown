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
#include <climits>

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

const int MAXN = 128;
int N, M;
vector<int> G[MAXN];
int V[2*MAXN];
int dp[MAXN][2*MAXN];

int solve( const int &u, const int &pos ){
	if ( pos == M ) return 0;
	if ( dp[u][pos] != -1 ) return dp[u][pos];
	int &res = dp[u][pos];
	
	int v;
	res = ( u != V[pos] ) + solve( u, pos + 1 );
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		res = min ( ( v != V[pos] ) + solve( v, pos + 1 ), res );
	}
	return res;
}

int main(){
	int runs;
	int u, v;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		while ( M-- ){
			scanf("%d %d", &u, &v);
			u--, v--;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		scanf("%d", &M);
		for ( int i=0; i < N; ++i ) 
			for ( int j=0; j < M; ++j )
				dp[i][j] = -1;
		
		for ( int i=0; i < M; ++i ) scanf("%d", V + i), V[i]--;
		int res = INT_MAX;
		
		for ( u=0; u < N; ++u ){
			res = min ( ( u != V[0] ) + solve( u, 1 ), res );
		}
		printf("%d\n", res);
		if ( runs ){
			for ( int i=0; i < N; ++i ) G[i].clear();
		}
	}
	return 0;
}

