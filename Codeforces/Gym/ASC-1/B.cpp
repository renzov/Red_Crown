#include<cstdio>
#include<climits>
#include<cassert>
#include<algorithm>

using namespace std;
const int MAXE = 4 * 256 * 256;
const int MAXV = 256;
// data for network flow
int b[MAXV];
int flow[MAXE];
int cap[MAXE];
int from [MAXE];
int to[MAXE];
int nxt[MAXE];
int lb[MAXE];
int head[MAXV];
int E;
int bneck[MAXV];
int p[MAXV];

int q[MAXV];
int qt, qf;
// problem paramenters
int N, M;


void add_arc( const int &u, const int &v, const int &c, const int &l ){
	from[E] = u, to[E] = v, cap[E] = c - l, flow[E] = 0, lb[E] = l, nxt[E] = head[u], head[u] = E++;
	from [E] = v, to[E] = u, cap[E] = c - l, flow[E] = c - l, lb[E] = 0, nxt[E] = head[v], head[v] = E++;
	assert( E < MAXE );
}

void aug_path( const int &s, const int &t ){
	qt = qf = 0;
	fill( bneck, bneck + N + 2, INT_MAX );
	fill ( p, p + N + 2, -1 );

	int u, v;

	q[qt++] = s;
	while ( qf < qt && p[t] == -1 ){
		u = q[qf++];
		for ( int e = head[u]; e != -1; e = nxt[e] ){
			v = to[e];
			if ( p[v] == -1 && cap[e] > flow[e] ){
				p[v] = e;
				bneck[v] = min( bneck[u], cap[e] - flow[e] );
				q[ qt++ ] = v;
			}
		}
	}
}

void update_flow( const int &s, const int &t ){
	int u = t;
	int e;
	int eps = bneck[t];

	while ( u != s ){
		e = p[u];
		flow[e] += eps, flow[e^1] -= eps;
		u = from[e];
	}
}

int max_flow( const int &s, const int &t ){
	int res = 0;
	do {
		aug_path( s, t );
		if ( p[t] != -1 ){
			res += bneck[t];
			update_flow( s, t );
		}
	}
	while ( p[t] != -1 );
	return res;
}

int main(){
	freopen("cooling.in", "r", stdin);
	freopen("cooling.out", "w", stdout);

	int u, v, c, l;

	scanf("%d %d", &N, &M);
	// initialize linked lists
	fill( head, head + N + 2, -1 );
	for ( int i = 0; i < M; ++i ){
		scanf("%d %d %d %d", &u, &v, &l, &c);
		u--, v--;
		add_arc( u, v, c, l );
		b[u] -= l, b[v] += l;
	}

	// even arcs from 0 to 2M - 2 correspond to arcs of the graph
	// source = N -- sink = N + 1
	int s = N, t = N + 1;
	// we link every vertex u with b[u] > 0 to source and every v with b[v] < 0 to sink
	int pos = 0, neg = 0;
	for ( int i=0; i < N; ++i ){
		if ( b[i] > 0 ){
			add_arc( s, i, b[i], 0 );
			pos += b[i];
		}
		else if ( b[i] < 0 ){
			add_arc( i, t, -b[i], 0 );
			neg -= b[i];
		}
	}

	if ( pos != neg ||  max_flow(s, t) != pos ){	// necessary condition
		puts("NO");
	}
	else {
		puts("YES");
		for ( int i=0; i < 2*M; i += 2 )
			printf("%d\n", flow[i] + lb[i]);
	}
	return 0;
}
