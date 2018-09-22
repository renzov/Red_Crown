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
const int MAXN = 128;

int N;
vector<int> G[MAXN];
int indeg[MAXN];
int outdeg[MAXN];
int tsm = 0;
int vis[MAXN];
int root;

void dfs( int u ){
	int v;

	vis[u] = tsm;

	if ( u != root ) 
		indeg[u]++, outdeg[root]++;

	for ( int i=0; i < (int) G[u].size(); ++i ){
		v = G[u][i];
		if ( vis[v] < tsm ){
			dfs( v );
		}
	}
}


int main(){
	int M;
	int u, v;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
	}
	for ( int i=1; i <= N; ++i ){
		tsm = i;
		root = i;
		dfs( i );
	}
	int res = 0;
	for ( int i=1; i <= N; ++i )
		if ( outdeg[i] + indeg[i] == N - 1 )
			res++;
	printf("%d\n", res);
	return 0;
}

