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

const int MAXN = 1005;
const int MAXS = 128;
int N, S, T;
vector<int> G[2*MAXS*MAXS];
vector<int> C[2*MAXS*MAXS];
int X[MAXS];
int P[MAXS];
int D[MAXN][MAXN];
int D2[ 2*MAXS*MAXS ];

void dijkstra( int s, int n, int lim, int *d ){
	fill( d, d + n, INT_MAX );
	d[s] = 0;
	priority_queue< pii, vector<pii>, greater<pii> > q;
	q.push( pii( 0, s ) );
	int u, v, w;
	int nw;
	while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( w > d[u] ) continue;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			nw = w + C[u][i];
			if ( nw <= lim && nw < d[v] ){
				d[v] = nw;
				q.push( pii(nw, v) );
			}
		}
	}
}

int main(){
	int runs;
	int M;
	int u, v, w;
	int s, t;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d %d", &N, &M, &S, &T);
		for ( int i=0; i < N; ++i )
			G[i].clear(), C[i].clear();
		while ( M-- ){
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			G[u].push_back(v), C[u].push_back(w);
			G[v].push_back(u), C[v].push_back(w);
		}
		for ( int i=0; i < S; ++i ){
			scanf("%d %d", X+i, P+i);
			X[i]--;
		}
		for ( int i=0; i < S; ++i )
			dijkstra( X[i], N, T, D[ X[i] ] );
			
		scanf("%d %d", &s, &t);
		s--,t--;
		// A fictional station in t
		X[S] = t, P[S] = 0;
		// Create a new graph
		int idx;
		map< int, int > H[MAXS];
		map<int,int>::iterator it, it2;

		for ( int i=0; i < S; ++i )
			if ( X[i] == s ){
				idx = i;
				break;
			}
		// Add state (s,0)
		H[ idx ][ 0 ] = 0;
		int ds;
		for ( int i=0; i < S; ++i ){
			for ( int j=0; j <= S; ++j ){
				if ( i != j && (ds = D[ X[i] ][ X[j] ]) <= T ){
					H[ i ][ P[i] < P[j]? T : ds ] = 0;
					H[ j ][ P[i] < P[j]? (T-ds):0 ] = 0; 
				}
			}
		}
		// remap the vertices
		int n = 0;
		for ( int i=0; i <= S; ++i ){
			for ( it=H[i].begin(); it != H[i].end() ; it++ ){
				it->second = n++;
			}
		}
		for ( int i=0; i < n; ++i ){
			G[i].clear(), C[i].clear();
		}
		// Create the reduced graph, edges between different distances from same station
		for ( int i=0; i < S; ++i ){
			if ( !H[i].empty() ){
				for ( it = it2 = H[i].begin(), it2++; it2 != H[i].end(); it = it2++ ){
					G[ it->second ].push_back( it2->second );
					C[ it->second ].push_back( P[i]*( it2->first - it->first ) );
				}
			}
		}
		// Add edges between stations
		for ( int i=0; i < S; ++i ){
			for ( int j=0; j <= S; ++j ){
				if ( i!=j && (ds=D[ X[i] ][ X[j] ]) <= T ){
					u = H[ i ][ P[i] < P[j]? T:ds ];
					v = H[ j ][ P[i] < P[j]? (T-ds):0 ];
					G[u].push_back(v); C[u].push_back(0);
				}
			}
		}
		dijkstra( H[ idx ][0], n, INT_MAX, D2 );
		printf("%d\n", D2[ n - 1 ]);
	}
	return 0;
}

