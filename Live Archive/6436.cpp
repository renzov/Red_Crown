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

const int MAXN = 20005;
int N;
vector<int> T[MAXN];
int S[MAXN];
long long res;

void dfs( int u, int p ){
	int v;
	long long sum = 0;
	S[u] = 0;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		dfs( v, u );
		sum += (S[u] * S[v]); // Number of paths passing through two childs of u
		S[u] += S[v];
	}
	S[u]++;
	sum += ( N - S[u] )*( S[u] - 1 ); // Number of paths, one end outside T_u
	res = max( sum, res );
}

int main(){
	int runs;
	int cases = 0;
	int u, v;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			T[u].push_back(v), T[v].push_back(u);
		}
		res = -1;
		dfs( 0, -1 );
		printf("Case #%d: %lld\n", ++cases, res);
		if ( runs ){
			for ( int i=0; i < N; ++i ) T[i].clear();
		}
	}
	return 0;
}

