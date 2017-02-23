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

const int MAXN = 100005;

int N, M;
vector<int> G[MAXN];
int indeg[MAXN] = {0};
int d[MAXN];
int col[MAXN];

int topsort( int c, int *deg ){
	queue<int> Q[2];
	for ( int i=0; i < N; ++i ) if ( deg[i] == 0 ) Q[ col[i] ].push( i );
	int p = 0; // process vertices
	int res = 0; // number of changes
	int u, v;
	while ( p < N ){
		while ( !Q[ c ].empty() ){
			p++;
			u = Q[c].front();
			Q[c].pop();
			for ( int i=0; i < (int)G[u].size(); ++i ){
				v = G[u][i];
				deg[v]--;
				if ( deg[v] == 0 ) Q[ col[v] ].push( v );
			}
		}
		c = 1 - c;
		if ( p < N ) res++;
	}
	return res;
}


int main(){
	int u, v;
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		for ( int i=0; i < N; ++i ){ 
			scanf("%d", &col[i]);
			col[i]--;
		}
		for ( int i=0; i < M; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			G[u].push_back( v );
			indeg[v]++;
		}
		for ( int i=0; i < N; ++i ) d[i] = indeg[i];
		int res = topsort( 0, d );
		res = min( res, topsort(1, indeg) );
		printf("%d\n", res);
		if ( runs ){
			for ( int i=0; i < N; ++i ){ 
				G[i].clear();
				indeg[i] = 0;	
			}
		}
	}
	return 0;
}

