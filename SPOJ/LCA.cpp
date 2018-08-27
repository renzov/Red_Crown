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

const int MAXN = 10000;
const int MLOG = 18;
vector<int> T[MAXN];
int indeg[MAXN] = {0};
int P[MLOG][MAXN];
int L[MAXN];
int N;
int log;

void clean_up(){
	for ( int i=0; i < N; ++i ){
		T[i].clear();
		indeg[i] = 0;
	}
}

void dfs( const int &u ){
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		L[v] = L[u] + 1;
		dfs(v);
	}
}

int go_up( int u, int D ){
	for ( int i=log; D >= 0 && i >= 0; --i ){
		if ( (1 << i) <= D ){
			D -= (1 << i);
			u = P[i][u];
		}
	}
	return u;
}

int lca( int u, int v ){
	if ( L[ u ] > L[ v ] ) swap( u , v );
	v = go_up( v , L[v] - L[u] );
	if ( u == v ) return u;
	for ( int i=log; i >= 0; --i ){
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			u = P[i][u], v = P[i][v];
	}
	return P[0][u];
}

void process( const int &casenum ){
	scanf("%d", &N);
	int outd;
	int u, v;

	for ( log=0; (1 << log) < N; ++log );
	log--;
	for ( int i=0; i <=log; ++i )
		fill( P[i], P[i] + N, -1 );

	for ( u=0; u < N; ++u ){
		scanf("%d", &outd);
		for ( int j=0; j < outd; ++j ){
			scanf("%d", &v);
			v--;
			T[u].push_back(v);
			indeg[v]++;
			P[0][v] = u;
		}
	}

	for ( int i=0; i < N; ++i )
		if ( indeg[i] == 0 ){
			L[i] = 0;
			dfs( i );
			break;
		}

	for ( int i=1; i <= log; i++ ){
		for ( int j=0; j < N; ++j )
			if ( P[i - 1][j] != -1 )
				P[i][j] = P[ i - 1 ][ P[i-1][j] ];
	}

	int Q;
	scanf("%d", &Q);
	printf("Case %d:\n", casenum);
	while ( Q-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		printf("%d\n", lca(u, v) + 1);
	}
}

int main(){

	int runs;
	scanf("%d", &runs);
	for ( int i=1; i <= runs; ++i ){
		process( i );
		clean_up();
	}
	return 0;
}

