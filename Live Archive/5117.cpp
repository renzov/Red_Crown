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

const long long MOD = 1000000007LL;
const int MAXN = 128;
vector<int> G[MAXN];
long long C[MAXN];
long long T[MAXN];

int d[MAXN];
int dfsnum[MAXN];
int len, size;
int num;

void dfs( int u, int p ){
	d[u] = ( p != -1 )? d[p] + 1:0;
	dfsnum[u] = num++;
	size++;
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( dfsnum[v] == -1 ) dfs( v, u );
		else if ( dfsnum[v] < dfsnum[u] ){
			len = d[u] - d[v] + 1;
		}
	}
}

int main(){
	int N, K;
	int u, v;
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &K);
		for ( u=0; u < N; ++u ){
			scanf("%d", &v);
			G[u].push_back( v );
			G[v].push_back( u );
		}

		/* F[x] = Number of the colorings of a cycle of length x */
		C[0] = 1;
		C[1] = K;
		C[2] = K * (K - 1);
		C[3] = ( C[2] * (K - 2) ) % MOD;
		for ( int i=4; i <= N; ++i )
			C[ i ] = ( ( K - 1 )*C[i - 2] + ( K - 2 )*C[i - 1] ) % MOD;
		
		/* T[x] = Number of colorings of a tree with x nodes given that root is colored */
		T[0] = 1;
		T[1] = K - 1;
		for ( int i=2; i <= N; ++i )
			T[i] = ( T[i-1] * ( K - 1 ) ) % MOD;
		
		long long res = 1;
		fill( dfsnum, dfsnum + N, -1 );
		num = 0;
		for ( int i=0; i < N; ++i ){
			if ( dfsnum[i] == -1 ){
				len = 0;
				size = 0;
				dfs( i , -1 );
				if ( len == 0 ) len = 2;
				res *= (( C[len] * T[size - len] ) % MOD);
				res %= MOD;
			}
		}
		printf("%lld\n", res);
		if ( runs ){
			for ( int i=0; i < N; ++i ) G[i].clear();
		}
	}
	return 0;
}

