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
#include <cassert>
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
typedef pair< int , int > edge;
typedef pair< int, int > pii;

struct event {
	int x;
	bool close;
	int idx;
	event( int X, bool C, int id){
		x = X, close = C, idx = id;
	}
	event(){}
	bool operator<( const event &ev ){
		if ( x != ev.x ) return x < ev.x;
		return close < ev.close;
	}
};

int N, M, K;
const int MAXN = 10005;
edge E[MAXN];
int WE[MAXN];
map<edge, int> W;
map<edge, int> inv;
vector<int> G[MAXN];
vector<int> C[MAXN];
int V[MAXN];
int d[MAXN];
int D[MAXN];
int val[MAXN];
int p[MAXN]; // parent in the tree
int rep[MAXN]; // representative in the main path
bool inPath[MAXN];
event Ev[2*MAXN];

void dijkstra(){
	int u, v, w, nw;
	edge e;

	fill( d, d + N, INT_MAX );
	fill( rep, rep + N, -1 );
	// Set up the distances of the vertices in the main path
	u = V[K-1];
	d[ u ] = 0;
	p[ u ] = -1;
	rep[u] = K - 1;
	// Taking the path 
	for ( int i=K-2; i >= 0; --i ){
		v = V[i];
		e.first = min(u, v), e.second = max(u, v);
		inPath[ inv[e] ] = true;
		d[v] = d[u] + W[e];
		p[v] = u;
		rep[v] = i; 
		u = v;
	}

	priority_queue< pii , vector<pii> , greater<pii> > q;
	for ( int i=0; i < K; ++i ) q.push( pii( d[ V[i] ] , V[i] ) );
	
	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second;
		q.pop();
		if ( w > d[u] ) continue;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			nw = w + C[u][i];
			if ( nw < d[v] ){ // ** We suppose a vertex in the main path is never relaxed,	
				d[v] = nw;    // that is, the path given in the input is indeed a shortest path.
				p[v] = u;
				rep[v] = rep[u];
				q.push( pii( d[v], v ) );
			}
		}
	}
}

set< pii > S;

int main(){
	int runs;
	edge e;
	int u, v, w;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);	
		// Read the graph
		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &u, &v, &w);
			if ( u > v ) swap(u, v);  
			G[u].push_back(v), G[v].push_back(u);
			C[u].push_back(w), C[v].push_back(w);
			e.first = u, e.second = v;
			if ( W.find(e) != W.end() ){
				if ( W[e] > w ){
					inv[e] = i, W[e] = w;
				}
			}
			else {
				W[e] = w;
				inv[e] = i;
			}
			E[i] = e;
			WE[i] = w;
			inPath[i] = false;
		}
		// Read the path
		scanf("%d", &K);
		for ( int i=0; i < K; ++i ) scanf("%d", V + i);
		// Find a shortest-path tree containing desired path
		dijkstra();
		
		for ( int i=0; i < N; ++i ){
			printf("vertex %d:", i);
			printf("d = %d - p = %d - rep = %d\n", d[i], p[i], rep[i]);
		}
		puts("");
		
		// Now we do the sweep line
		int m = 0;
		for ( int i=0; i < M; ++i ){
			// Check if it is an edge in the path
			if ( inPath[i] ) continue;
			e = E[i];
			// Take the representative it links
			u = rep[ e.first ], v = rep[ e.second ];
			// An edge linking the same representative is useless
			if ( u == v ) continue;
			// vertex not reachable from V[K-1]
			if ( rep[u] == -1 || rep[v] == -1 ) continue;
			if ( u > v ) swap(u, v);
			// Create the events
			printf("inserting edge (%d, %d) - with rep (%d, %d)\n", e.first, e.second, u, v);
			Ev[m++] = event( u, false, i );
			Ev[m++] = event( v, true, i );
		}
		sort( Ev, Ev + m );
		// Do the sweep line
		int j = 0; // for the events
		int len = 0;
		int d1, d2, d3;
		int idx;
		int ru, rv;
		int res = 0;
		for ( int i=0; i < K-1; ++i ){
			// Process all the events that begin and end in i
			printf("len = %d\n", len);
			while ( j < m && Ev[j].x == i ){
				idx = Ev[j].idx;
				if ( Ev[j].close ){ // delete event
					S.erase( pii( val[idx], idx ) );
				}
				else {
					w = WE[ idx ];
					u = E[idx].first, v = E[idx].second;
					printf("event open: (%d, %d) ", u, v);					
					ru = V[ rep[u] ], rv = V [ rep[v] ];
					printf("ru = %d - rv = %d\n", ru, rv);
					d1 = d[u] - d[ru];
					d2 = d[v] - d[rv];
					d3 = min( d[ru] , d[rv] );
					printf("d1 = %d d2 = %d d3 = %d w = %d\n", d1, d2, d3, w);
					val[ idx ] = d1 + d2 + d3 + w - len;
					S.insert( pii( val[idx], idx ) );		
				}
				j++;
			}
			if ( !S.empty() ){
				res = max( res , S.rbegin()->first + len + d[V[0]] - d[V[i]] );	
			}
			else {
				res = INT_MAX;
			}
			len += d[ V[i] ] - d[ V[i+1] ];
		}
		if ( res < INT_MAX ) printf("%d\n", res);
		else puts("-1");
		
		if ( runs ){
			S.clear();
			for ( int i=0; i < N; ++i ) G[i].clear(), C[i].clear();
			W.clear(), inv.clear();
		}
	}
	return 0;
}

