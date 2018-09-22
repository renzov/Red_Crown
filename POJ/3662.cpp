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

const int MAXN = 1024;

int N, M, K;
vector<int> G[MAXN];
vector<int> W[MAXN];
int E[MAXN*10];
int d[MAXN];

bool test( const int &bound ){
	deque<int> q;
	fill( d , d + N, INT_MAX );
	d[0] = 0;
	q.push_back( 0 );
	
	int u, v, w;

	while ( !q.empty() ){
		u = q.front(); 
		q.pop_front();
		if ( u == (N-1) ) break;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			w = W[u][i];
			if ( w <= bound ){
				if ( d[v] > d[u] ){
					d[v] = d[u];
					q.push_front(v);
				}
			}
			else {
				if ( d[v] > (d[u] + 1) ){
					d[v] = d[u] + 1;
					q.push_back(v);
				}
			}
		}
	}
	return d[N-1] <= K;
}

int main(){
	int u, v, w;

	scanf("%d %d %d", &N, &M, &K);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
		W[u].push_back(w), W[v].push_back(w);
		E[i] = w;
	}
	E[M] = 0;
	sort( E , E + M + 1 );
	M = unique( E, E + M + 1 ) - E;
	if ( !test( E[M-1] ) ) puts("-1");
	else if ( test( E[0] ) ) printf("%d\n", E[0]);
	else {
		int l = 0;
		int r = M - 1;
		int m;
		while ( r - l > 1 ){
			m = ( l + r ) >> 1;
			if ( test( E[m] ) )
				r = m;
			else 
				l = m;
		}
		printf("%d\n", E[r]);
	}
	return 0;
}

