#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 128;
const int MAXV = 4*MAXN;
const int MAXE = 60000;

int head[MAXV];
int from[MAXE];
int to[MAXE];
int cap[MAXE];
int flow[MAXE];
int nxt[MAXE];

int q[MAXV], qt, qf;
int pre[MAXV];
int bneck[MAXV];

// The flow network has 2N + F + D + 2 vertices
int N, F, D, M;
int V; // Number of vertices
inline int in( const int &i ){ return i << 1; }
inline int out( const int &i ){ return (i << 1) | 1; }
inline int food( const int &f ){ return 2*N + f; }
inline int drink( const int &d ){ return 2*N + F + d; }

void add_edge( const int &u, const int &v, const int &c ){
	from[M] = u, to[M] = v, cap[M] = c, flow[M] = 0, nxt[M] = head[u]; head[u] = M++;
	from[M] = v, to[M] = u, cap[M] = c, flow[M] = c, nxt[M] = head[v]; head[v] = M++;
}

int max_flow( const int &s, const int &t ){
	int res = 0;
	int f;
	int u, v, e;
	while ( 1 ){
		// find an augmenting path
		fill( pre, pre + V, -1 );
		bneck[s] = INT_MAX;
		qt = qf = 0;
		q[ qt++ ] = s;
		while ( qf < qt && pre[t] == -1 ){
			u = q[qf++];
			for ( e = head[u]; e >= 0 ; e = nxt[e] ){
				v = to[e];
				if ( cap[e] - flow[e] > 0 && pre[v] == -1 ){
					q[ qt++ ] = v;
					pre[v] = e;
					bneck[v] = min( bneck[u], cap[e] - flow[e] );
				}
			}
		}
		if ( pre[t] == -1 ) break; // No augmenting path
		// Update the residual network
		v = t;
		f = bneck[t];
		res += f;
		do {
			e = pre[v];
			u = from[e];
			flow[e] += f;
			flow[e^1] -= f;
			v = u;
		}
		while ( v != s );
	}
	return res;
}

int main(){
	int f, d;
	int nf, nd;
	int s, t;
	
	scanf("%d %d %d", &N, &F, &D);
	
	M = 0;
	V = 2*N + F + D + 2; 	// Number of vertices in the network
	fill( head, head + V, -1 );

	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &nf, &nd);
		for ( int j=0; j < nf; ++j ){
			scanf("%d", &f);
			f--;
			add_edge( food( f ) , in(i) , 1 );
		}
		for ( int j=0; j < nd; ++j ){
			scanf("%d", &d);
			d--;
			add_edge( out(i) , drink(d) , 1 );
		}
	}
	
	s = 2*N + F + D; // source
	t = 2*N + F + D + 1; // sink
	for ( int i=0; i < N; ++i ){
		add_edge( in(i), out(i) , 1 );
	}
	for ( int i=0; i < F; ++i ){
		add_edge( s , food(i), 1 );
	}
	for ( int i=0; i < D; ++i ){
		add_edge( drink(i) , t , 1 );
	}
	printf("%d\n", max_flow(s,t));
	return 0;
}

