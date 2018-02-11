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
const int MAXN = 2024;
int N;

int X[MAXN];
int Y[MAXN];
int D[MAXN];
vector<int> G[MAXN];
int dfsnum[MAXN];
int low[MAXN];
bool inS[MAXN];
int comp[MAXN];
int indeg[MAXN];
stack<int> S;
int num;
int ncomp;

bool inside( const int &a, const int &b ){ // b inside a
	return 2*abs( X[a] - X[b] ) <= D[a] && 2*abs( Y[a] - Y[b] ) <= D[a];
}

void dfs( int u ){
	low[u] = dfsnum[u] = num++;
	S.push(u); inS[u] = true;

	int v;

	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( dfsnum[v] == -1 ){
			dfs(v);
			low[u] = min( low[u], low[v] );
		}
		else if ( inS[v] ) {
			low[u] = min( low[u], dfsnum[v] );
		}
	}
	
	if ( low[u] == dfsnum[u] ){
		do {
			v = S.top();
			S.pop();
			inS[v] = false;
			comp[v] = ncomp;
		}
		while ( v != u );
		ncomp++;
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; i++ )
			scanf("%d %d %d", X+i, Y+i, D+i);

		for ( int i=1; i < N; ++i ){
			for ( int j=0; j < i; ++j ){
				if ( inside( i , j ) ) G[i].push_back(j);
				if ( inside( j , i ) ) G[j].push_back(i);
			}
		}
		// find strongly connected components
		fill( dfsnum, dfsnum + N, -1 );
		ncomp = num = 0;
		for ( int i=0; i < N; ++i )
			if ( dfsnum[i] == -1 )
				dfs(i);
		
		int u,v;
		for ( u=0; u < N; ++u ){
			for ( int i=0; i < (int) G[u].size(); ++i ){
				v = G[u][i];
				if ( comp[u] != comp[v] ) indeg[ comp[v] ]++;
			}
		}
		
		int res = 0;
		for ( int i=0; i < ncomp; ++i ) 
			if ( indeg[i] == 0 ) res++;

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

