#include<cstdio>
#include<cmath>
#include<cassert>
#include<algorithm>
using namespace std;
typedef pair<int,int> edge;
const double INF = 1e10;
const double EPS = 1e-6;
const int MAXN = 128;
const int MAXE = 4048 + 4*MAXN;
int N, M;
int deg[MAXN];
edge E[MAXE];
// Flow structure
int m;
int size;
bool S[MAXN];
double cap[MAXE];
double flow[MAXE];
int nxt[MAXE];
int head[MAXN];
int from[MAXE];
int to[MAXE];
// Queue
int q[MAXN];
int qt, qf;
int prv[MAXN];
double bneck[MAXN];


int comp( const double &a, const double &b ){
	if ( fabs(a - b) < EPS ) return 0;
	return ( a < b )? -1:1;
}

void add_edge( const int &u, const int &v, const double &c ){
	from[m] = u, to[m] = v, cap[m] = c, flow[m] = 0, nxt[m] = head[u]; head[u] = m++;
	from[m] = v, to[m] = u, cap[m] = c, flow[m] = c, nxt[m] = head[v]; head[v] = m++;
}

void max_flow( const int &s, const int &t, const int &V ){
	double f;
	double res = 0.0;
	int u, v, e;

	do {
		// Initilialize 
		fill( bneck, bneck + V, INF );
		fill( prv, prv + V, -1 );
		fill( S, S + V, false );
		qf = qt = 0;
		q[qt++] = s;
		S[s] = true;
		// Find an augmenting path
		while ( qf < qt && prv[t] == -1 ){
			u = q[qf++];
			for ( e = head[u]; e != -1; e = nxt[e] ){
				v = to[e];
				if ( prv[v] != -1 ) continue;
				if ( comp( flow[e], cap[e] ) < 0 ){
					S[v] = true;
					bneck[v] = min( bneck[u], cap[e] - flow[e] );
					q[qt++] = v;
					prv[v] = e;
				}
			}
		}
		if ( prv[t] != -1 ){
			f = bneck[t];
			// update the flow
			v = t;
			while ( v != s ){
				e = prv[v];
				u = from[e];
				flow[e] += f;
				flow[e^1] -= f;
				v = u;
			}
			res += f;
		}
	}
	while ( prv[t] != -1 );
	// Calculate the size of the set that gives a mincut
	size = 0;
	for ( int i=0; i < N; ++i )	// Not consider s or t
		if ( S[i] ) size++;
}

void construct_network( const double &delta ){
	m = 0;
	fill( head, head + (N + 2), -1 );
	int u, v;
	
	for ( int i=0; i < M; ++i ){
		u = E[i].first, v = E[i].second;
		add_edge( u, v, 1.0 );
		add_edge( v, u, 1.0 );
	}
	int s = N;
	int t = N + 1;
	for ( int i=0; i < N; ++i ){
		add_edge( s, i, (double)M );
		add_edge( i, t, (double)M - deg[i] + 2*delta );
	}
}

void process(){
	int u, v;
	if ( M == 0 ){// Trivial graph.
		printf("1\n1\n");
		return;
	}
	// Initialize the network structure
	fill( deg, deg + N, 0 );
	// Create the base network
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		E[i] = edge( u, v );
		deg[u]++, deg[v]++;
	}
	// Do binary search (bisection)
	double l = 0;		// There is always a solution with 0 density
	double r = M;	// This bound is always imposible
	int res;
	bool best[MAXN];
	double delta;
	double bound = 1.0/(N*N);
	while ( r - l > bound ){
		delta = ( l + r ) / 2.0;
		construct_network( delta );
		max_flow( N, N + 1, N + 2);	// density delta is possible
		if ( size > 0 ){
			l = delta;
			// Save the answer
			res = size;
			copy( S, S + N, best );
		}
		else {
			r = delta;
		}
	}
	printf("%d\n", res);
	for ( int i=0; i < N; ++i ){
		if ( best[i] ) printf("%d\n", i + 1 );
	}
}

int main(){	
	int runs = 0;
	while ( scanf("%d %d", &N, &M) == 2 ){
		process();
		runs++;
		puts("");		
	}
	return 0;
}
