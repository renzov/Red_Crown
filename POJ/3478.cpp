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
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 256;
const int MAXM = 4005;
const int MAXE = 2*MAXM + 4*MAXN;
const int MAXCAP = 10000000; // > 200 * 2000 ( sum of B[i] )
int B[MAXN];
int C[MAXM];
int X[MAXM];
int Y[MAXM];
// Demands
int b[MAXN];
// Variables used in mincost flow
int E;
int from[MAXE];
int to[MAXE];
int cost[MAXE];
int cap[MAXE];
int flow[MAXE];
int nxt[MAXE];
int head[MAXN];
int pot[MAXN] = {0};

void add_edge(int u, int v, int c, int w){
	from[E] = u, to[E] = v, cost[E] = w, cap[E] = c, flow[E] = 0, nxt[E] = head[u], head[u] = E, E++;
	from[E] = v, to[E] = u, cost[E] = -w, cap[E] = c, flow[E] = c, nxt[E] = head[v], head[v] = E, E++;
}

long long mcmf( int s, int t, int N ){
	int d[MAXN];
	int arc[MAXN];
	int bneck[MAXN];

	int u, v, c, w, e;
	int F = 0;
	long long C = 0;

	do {
		/* Find shortest path from s */
		fill( d , d + N, INT_MAX );
		fill( bneck, bneck + N, INT_MAX );
		d[s] = 0; arc[s] = -1; 
		priority_queue< pii, vector<pii>, greater<pii> > q;
		q.push( pii( 0 , s ) );
		
		while ( !q.empty() ){
			u = q.top().second;
			w = q.top().first;
			q.pop();
			if ( w > d[u] ) continue;
			for ( e = head[u]; e >= 0 ; e = nxt[e] ){
				if ( flow[e] < cap[e] ){
					v = to[e];
					c = cost[e] + pot[u] - pot[v]; /* reduced cost */
					if ( d[v] > (w + c) ){
						d[v] = w + c;
						arc[v] = e;
						bneck[v] = min( bneck[u], cap[e] - flow[e] );
						q.push( pii(d[v], v) );
					}
				}
			}	
		}
		if ( d[t] < INT_MAX ){
			/* update potentials */
			for ( int i=0; i < N; ++i ){
				if ( d[i] < INT_MAX ) pot[i] += d[i];
			}
			/* update flow and cost */
			v = t;
			int eps = bneck[t];			
			while ( arc[v] >= 0 ){
				e = arc[v]; u = from[e];
				flow[e] += eps; flow[e^1] -= eps;
				C += 1LL * cost[e] * eps;
				v = u;
			}
			F += eps;
		}
	}
	while ( d[t] < INT_MAX );
	return C;
}

int main(){
	int s, t;	
	int N, M;

	scanf("%d %d", &M, &N);	
	// vertices 1 ... N + 1 are from the model	
	s = 0;
	t = N + 2;
	E = 0;
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", X + i, Y + i);
	}
	// Init for adding arcs
	fill( head, head + (N + 4), -1 );
	for ( int i=1; i <= N; ++i ) scanf("%d", B+i );
	B[N + 1] = 0;
	for ( int i=0; i < M; ++i ) scanf("%d", C+i );

	for ( int i=0; i < M; ++i ){
		add_edge( X[i] , Y[i] + 1, MAXCAP, C[i] );
	}
	// Adding arcs corresponding to slack variables
	for ( int i=N+1; i > 1; --i ){
		add_edge( i, i - 1, MAXCAP, 0 );
	}
	// Calculate the demands for each vertex
	b[1] = B[1];
	for ( int i=2; i <= N + 1; ++i ){
		b[i] = B[i] - B[i - 1];
	}
	// Adding arcs from s to supply nodes and from demand nodes to t
	for ( int i=1; i <= N + 1; ++i ){
		if ( b[i] < 0 ){
			add_edge( i , t, -b[i], 0 );
		}
		else if ( b[i] > 0 ){
			add_edge( s, i, b[i], 0 );
		}
	}
	printf("%lld\n", mcmf( s, t, N + 3 ));
	return 0;
}

