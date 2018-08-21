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
const int MAXN = 10005;

int N, M;
vector<int> G[MAXN];
vector<int> W[MAXN];
vector<int> D[MAXN];
int d[MAXN];
int s, t;
int cnt[MAXN];

void dijkstra(){
	fill( d, d + N, INT_MAX );
	priority_queue< pii, vector<pii>, greater<pii> > q;
	d[s] = 0;
	q.push( pii( 0, s ) );

	int u, v, w, we;

	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second;
		q.pop();
		if ( w > d[u] ) continue;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i], we = W[u][i];
			if ( w + we < d[v] ){
				d[v] = w + we;
				q.push( pii( d[v], v ) );
			}
		}
	}
}

int dfs( int u ){
	if ( cnt[u] != -1 ) return cnt[u];
	int &ret = cnt[u] = 0; 
	
	for ( int i=0; i < (int)D[u].size(); ++i )
		ret += dfs( D[u][i] );
	
	return ret;
}

int main(){
	int u, v, w;
	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(v), W[u].push_back(w);
	}
	scanf("%d %d", &s, &t);
	dijkstra();
	/* Create the shortest path DAG */
	for ( u=0; u < N; ++u ){
		if ( d[u] == INT_MAX ) continue;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			if ( d[u] + W[u][i] == d[v] ) 
				D[u].push_back(v);
		}
	}
	fill( cnt, cnt + N, -1 );
	cnt[t] = 1;
	printf("%d\n", dfs(s));
	return 0;
}

