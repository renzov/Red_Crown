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
const int MAXN = 505;
int N;

vector<int> G[MAXN];
vector<int> W[MAXN];
int indeg[MAXN];
int ord[MAXN];
int d[MAXN];

void topsort(){
	queue<int> q;
	for ( int i=0; i < N; ++i ) 
		if ( indeg[i] == 0 ) q.push(i);
	
	int u, v; 
	int n = 0;

	while ( !q.empty() ){
		u = q.front(); q.pop();
		ord[n++] = u;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			indeg[v]--;
			if ( indeg[v] ==  0) q.push(v);
		}
	}
}

void solve( const int &s, const int &t ){
	fill( d, d + N, -INT_MAX );
	d[s] = 0;
	int u, v;
	for ( int i=0; i < N; ++i ){
		u = ord[i];
		if ( d[u] == -INT_MAX ) continue;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			d[v] = max( d[v], d[u] + W[u][i] );
		}
	}
}

int main(){
	int M;
	int u, v, w;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back(v);
		W[u].push_back(w);
		indeg[v]++;
	}
	scanf("%d %d", &u, &v);
	u--, v--;

	topsort();
	solve( u, v );
	if ( d[v] == -INT_MAX ) puts("No solution");
	else printf("%d\n", d[v]);

	return 0;
}

