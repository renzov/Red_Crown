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
#include <cassert>

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

const int MAXN = 50005;
const int MLOG = 18;

int N;
vector<int> T[MAXN];
vector<int> W[MAXN];
int P[MLOG][MAXN];
int L[MAXN];
int d[MAXN];

void bfs(){
	queue<int> q;
	q.push(0);
	fill( d, d + N, -1 );
	d[0] = L[0] = 0;
	int u, v, w;
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		for ( int i=0; i < (int) T[u].size(); ++i ){
			v = T[u][i];
			w = W[u][i];
			if ( d[v] == -1 ){
				d[v] = d[u] + w;
				L[v] = L[u] + 1;
				P[0][v] = u;
				q.push( v );
			}
		}
	}
	
}

int lca( int u, int v ){
	if ( L[v] < L[u] ) swap( u , v );
	int D = L[v] - L[u];
	int log;
	for ( log=0; (1 << log) < N; ++log );
	log--;
	// go up
	for ( int i=log; i >= 0 && D > 0; --i ){
		if ( (1<<i) <= D ){
			v = P[i][v];
			D -= ( 1 << i );
		}
	}
	if ( v == u ) return u;
	for ( int i=log; i >= 0; --i ){
		if ( P[i][u] != -1 && P[i][u] != P[i][v] ){
			u = P[i][u], v = P[i][v];
		}
	}
	return P[0][u];
}

int main(){
	int u, v, w, l;
	int M;

	scanf("%d", &N);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		T[u].push_back(v); W[u].push_back(w);
		T[v].push_back(u); W[v].push_back(w);
	}

	for ( int i=0; (1 << i) < N; ++i )
		for ( int j=0; j < N; ++j )
			P[i][j] = -1;

	bfs();
	for ( int i=1; (1 << i) < N; ++i ){
		for ( int j=0; j < N; ++j )
			if ( P[i-1][j] != -1 )
				P[i][j] = P[ i - 1 ][ P[i-1][j] ];
	}

	scanf("%d", &M);	
	while ( M-- ){
		scanf("%d %d", &u, &v);
		if ( v == u ){ 
			printf("0\n");
			continue;
		}
		l = lca( u , v );
		printf("%d\n", d[u] + d[v] - 2*d[l]);
	}
	return 0;
}

