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
typedef pair< long long, int > elem;

const int MAXN = 100005;
int N, M;

vector<int> G[MAXN];
vector<int> W[MAXN];
long long X[MAXN];
long long Y[MAXN];

void dijkstra( int s , long long d[] ){
	fill( d, d + N, LLONG_MAX );
	d[s] = 0;
	priority_queue< elem, vector<elem>, greater<elem> > q;
	q.push( elem(0, s) );
	
	int u, v;
	long long w;
	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second;
		q.pop();
		if ( w > d[u] ) continue;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] > (w + W[u][i]) ){
				d[v] = w + W[u][i];
				q.push( elem(d[v], v) );
			}
		}
	}
}

int main(){
	int runs;
	int u, v, w;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		while ( M-- ){
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			G[u].push_back(v), W[u].push_back(w);
			G[v].push_back(u), W[v].push_back(w);
		}
		// Finding shortest paths from 0 and 1
		dijkstra( 0, X );
		dijkstra( 1, Y );
		// Translate the points
		long long x, y;
		for ( int i=0; i < N; ++i ){
			x = X[i] - Y[i];
			y = X[i] + Y[i];
			X[i] = x, Y[i] = y;
		}
		sort( X, X + N );
		sort( Y, Y + N );
		// medians
		x = X[N/2], y = Y[N/2];
		// calculate the L1 distance to (x,y)
		long long res = 0;
		for ( int i=0; i < N; ++i ){
			res += llabs( X[i] - x ) + llabs( Y[i] - y );
		}
		printf("%.12Lf\n", ((long double)res) / (2*N) );
		if ( runs ){
			for ( int i=0; i < N; ++i )
				G[i].clear(), W[i].clear();
		}
	}
	return 0;
}
