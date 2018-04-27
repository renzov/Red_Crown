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
const int MAXN = 1024;
vector<int> G[MAXN];
bool vis[MAXN];
int match[MAXN];

bool alt_path( const int &u ){
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
	int N, M, K;
	int u, v;

	scanf("%d %d %d", &M, &N, &K);
	while ( K-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v);
	}
	fill( match, match + N, -1 );
	int m = 0;
	for ( int i=0; i < M; ++i ){
		fill( vis, vis + M, false );
		if ( alt_path( i ) ) m++;
	}
	printf("%d\n", N+M - m);
	return 0;
}

