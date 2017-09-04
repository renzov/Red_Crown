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
typedef pair< int , int > edge;

int N, M;
const int MAXN = 3005;
const int MAXM = 30005;

vector<int> G[MAXN];
vector<edge> E;
int W[MAXM];
int d[MAXN];

inline int nxt( const int &v, const int &e ){
	return ( E[e].first == v )? E[e].second:E[e].first;
}

void solve( int s ){
	queue<int> q;
	fill( d, d + N + 1, -1 );	
	fill( W, W + M, -1 );
	d[s] = 0;
	q.push( s );
	int w = 1;
	int u, v, e;

	while ( !q.empty() ){
		u = q.front();
		q.pop();

		for ( int i=0; i < (int) G[u].size(); ++i ){
			e = G[u][i];
			v = nxt( u , e );
			if ( W[e] == -1 ) W[e] = w++;  
			if ( d[v] == -1 ){
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
}

int main(){

	int runs;
	int cases = 0;
	scanf("%d", &runs);
	
	int s;
	int u, v, w;

	while ( runs-- ){
		scanf("%d %d %d", &N, &M, &s);
		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &u, &v, &w);	
			G[u].push_back( i ), G[v].push_back( i );
			E.push_back( edge(u, v) );
		}
		solve( s );
		printf("Case %d:\n", ++cases);
		for ( int i=0; i < M; ++i )
			printf("%d %d %d\n", E[i].first, E[i].second, W[i]);

		if ( runs ){
			for ( int i=1; i <= N; ++i ) G[i].clear();
			E.clear();
		}
	}
	return 0;
}

