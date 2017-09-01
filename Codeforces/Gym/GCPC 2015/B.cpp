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

inline int in( const int &x ){ return 2*x; }
inline int out( const int &x ){ return 2*x + 1; }

const int MAXN = 1024;
vector<int> G[MAXN];
int N;

bool vis[MAXN];
int match[MAXN];

bool alt_path( int u ){
	if ( vis[u] ) return false;
	vis[u] = true;
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( match[v] == -1 || alt_path( match[v] ) ){
			match[v] = u;
			return true;
		}
	}
	return false;
}

int main(){
	int K, v;
	scanf("%d", &N);

	for ( int u=0; u < N; ++u ){
		scanf("%d", &K);
		for ( int j=0; j < K; ++j ){
			scanf("%d", &v);
			G[ u ].push_back( v );
		}
	}
	// Find the maximum matching
	int M = 0;
	fill( match, match + N, -1 );
	for ( int u=0; u < N; ++u ){
		fill( vis, vis + N, false );
		if ( alt_path( u ) ) M++;
	}
	printf("%d\n", N - M);
	return 0;
}

