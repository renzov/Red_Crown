;#include <iostream>
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
const int MAXN = 10005;
int N, M, K;
vector<int> G[MAXN];
vector<int> W[MAXN];
int d[MAXN];
bool mult[MAXN];
bool vis[MAXN];
bool dijkstra( int s, int t ){
	fill( d, d + N, INT_MAX );
	fill( mult, mult + N, false );
	fill( vis, vis + N, false );

	priority_queue< pii, vector<pii>, greater<pii> > q;
	d[s] = 0;
	q.push( pii(0, s) );
	
	int u, v , w;
	while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( vis[u] ) continue;
		vis[u] = true;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] > w + W[u][i] ){
				mult[v] = mult[u];
				d[v] = w + W[u][i];
				q.push( pii( d[v], v ) );
			}
			else if ( d[v] == w + W[u][i] ){
				mult[v] = true;
			}
		}
	}
	return mult[N-1];
}

int main(){
	int u, v, w;

	scanf("%d %d %d", &N, &M, &K);
	// Ignore
	for ( int i=0; i < K; ++i ) scanf("%d", &u);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		if ( u != v ){
			G[u].push_back(v); W[u].push_back(w);
			G[v].push_back(u); W[v].push_back(w); 
		}
	}
	puts( dijkstra(0, N-1)? "yes":"no" );
	return 0;
}

