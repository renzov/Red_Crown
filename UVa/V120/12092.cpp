#include<cstdio>
#include<algorithm>
#include<queue>
#include<climits>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 50;
const int MAXE = 5000; // > 2 * 2000 + 2*MAXN

inline int in(const int &v){ return v << 1; }
inline int out(const int &v){ return (v << 1) | 1; }
int s, t;

int flow[MAXE];
int cap[MAXE];
int cost[MAXE];
int from[MAXE];
int to[MAXE];
int nxt[MAXE];
int E;

int head[2*MAXN];
int pot[2*MAXN];
int d[2*MAXN];
int pre[2*MAXN];
int bneck[2*MAXN];

void add_edge( const int &u, const int &v, const int &c, const int &w ){
	from[E] = u, to[E] = v, flow[E] = 0, cap[E] = c, cost[E] = w, nxt[E] = head[u]; head[u] = E++;
	from[E] = v, to[E] = u, flow[E] = c, cap[E] = c, cost[E] = -w, nxt[E] = head[v]; head[v] = E++;
}

void mcmf( const int &s, const int &t, int n, int &resF, int &resC ){
	priority_queue< pii, vector<pii>, greater<pii> > q;
	int u, v, w, c, e, eps;
	resF = resC = 0;
	fill( pot, pot + n, 0 ); 
	do {
		// Find a shortest st-path 
		fill( d , d + n, INT_MAX );
		fill( bneck, bneck + n, INT_MAX );
		d[s] = 0; pre[s] = -1;
		q.push( pii( 0 , s ) );
		// Find augmenting shortest path
		while ( !q.empty() ){
			w = q.top().first;
			u = q.top().second;
			q.pop();
			if ( w > d[u] ) continue;
			for ( e = head[u]; e != -1 ; e = nxt[e] ){
				if ( flow[e] < cap[e] ){
					v = to[e];
					c = cost[e] + pot[u] - pot[v];
					if ( d[v] > w + c ){
						d[v] = w + c;
						pre[v] = e;
						bneck[v] = min( bneck[u] , cap[e] - flow[e] );
						q.push( pii( d[v] , v ) );
					}
				}
			}
		}
		if ( d[t] < INT_MAX ){ // Path found
			// Update potentials
			for ( int i=0; i < n; ++i )
				if ( d[i] < INT_MAX ) pot[i] += d[i];
			// Update residual network
			v = t;
			eps = bneck[t];
			resF += eps;
			do {
				e = pre[v];
				u = from[e]; 
				flow[e] += eps;
				flow[e^1] -= eps;
				resC += (cost[e] * eps);
				v = u;
			}
			while ( v != s );
		}
	}
	while ( d[t] < INT_MAX );
}

void process(){
	int N, M, K;
	int u, v, w;
	int f, c;

	E = 0;
	scanf("%d %d %d", &N, &M, &K );
	s = 2*N;
	t = s + 1;
	fill( head, head + (t + 1), -1 );
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		add_edge( out(u), in(v), 1, w );
	}
	for ( int i=0; i < N; ++i ){
		add_edge( s, out(i), K, 0 );
		add_edge( in(i), t, K, 0 );
	}
	mcmf( s, t, 2*N + 2, f, c );
	if ( f < N*K ) puts("-1");
	else printf("%d\n", c);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
	}
	return 0;
}
