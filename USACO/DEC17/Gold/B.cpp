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

const int MAXN = 100006;
const int MOD = 1000000007;
int N, K;
vector<int> T[MAXN];
int col[MAXN];
long long dp[MAXN][4];

long long dfs( int u, int cu, int p, int cp ){
	if ( cu == cp || (col[u] && col[u] != cu) ) return 0LL;
	long long &res = dp[u][cu];
	if ( res != -1 ) return res;

	res = 1;
	int v;
	long long ways;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		ways = 0;
		for ( int cv=1; cv <= 3; ++cv ){
			ways += dfs( v, cv, u, cu );
			ways %= MOD;
		}
		res *= ways; 
		res %= MOD;
	}
	return res;
}

int main(){
	freopen ("barnpainting.out","w",stdout);
	freopen("barnpainting.in","r",stdin);	
	
	int u, v;
	int c;

	scanf("%d %d", &N, &K);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		T[u].push_back(v), T[v].push_back(u);
	}
	fill( col, col + (N + 1), 0 );
	for ( int i=0; i < K; ++i ){
		scanf("%d %d", &u, &c);
		col[u] = c;
	}

	for ( int i=1; i <= N; ++i )
		dp[i][1] = dp[i][2] = dp[i][3] = -1;

	long long res = dfs( 1, 1, -1, -1 ) + dfs( 1, 2, -1, -1 ) + dfs( 1, 3, -1, -1 );
	printf("%lld\n", res % MOD);
	return 0;
}

