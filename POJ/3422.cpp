#include<cstdio>
#include<climits>
#include<algorithm>
#include<queue>
#include<cstdlib>
using namespace std;
/* 
	Implementation tested in problems 
	LA 3987 - Finest Chef
	LA 3198 - Going Home
	LA 2927 - "Shortest pair of paths"
	SPOJ TOURS - Travelling Tours
	POJ 3422 - Kaka Travels
*/
const int MAXE = 20200; /*  MAXE < 2 x ((100 x 100) + 200) */
const int MAXV = 5000;

int E;
int N;
/* variables used in flow */
int from[MAXE];
int to[MAXE];
int cost[MAXE];
int cap[MAXE];
int flow[MAXE];
int nxt[MAXE];
int head[MAXV];
int pot[MAXV];
int W[55][55];

inline int in(int x){ return x << 1; }
inline int out(int x){ return (x << 1) | 1; }
inline int cell( int i, int j ){ return i*N + j; }

void add_edge(int u, int v, int c, int w){
	from[E] = u, to[E] = v, cost[E] = w, cap[E] = c, flow[E] = 0, nxt[E] = head[u], head[u] = E, E++;
	from[E] = v, to[E] = u, cost[E] = -w, cap[E] = c, flow[E] = c, nxt[E] = head[v], head[v] = E, E++;
}

void find_feasible_potential(){
	fill( pot, pot + 2*N*N, 1 );
	pot[ in(cell(0,0)) ] = 0;
	int c;
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			c = pot[ out(cell(i,j)) ] = pot[ in(cell(i,j)) ] - W[i][j];
			if ( j + 1 < N && pot[ in(cell(i,j+1)) ] > c ) pot[ in(cell(i,j+1)) ] = c;
			if ( i + 1 < N && pot[ in(cell(i+1,j)) ] > c ) pot[ in(cell(i+1,j)) ] = c;
		}
}

pair<int,int> mcmf( int s , int t, int V ){
	int d[MAXV];
	int arc[MAXV];

	int u, v, c, w, e;
	int F = 0, C = 0;
	
	find_feasible_potential();

	do {
		/* Find shortest path from s */
		fill( d , d + V, INT_MAX );
		d[s] = 0; arc[s] = -1; 
		priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > q;
		q.push( make_pair( 0 , s ) );
		
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
						q.push( make_pair(d[v], v) );
					}
				}
			}
		}
		if ( d[t] < INT_MAX ){
			/* update potentials */
			for ( int i=0; i < N; ++i ){
				if ( d[i] < INT_MAX ) pot[i] += d[i];
			}
			/* calculate bottleneck */						
			v = t;
			int eps = INT_MAX;
			while ( arc[v] >= 0 ){
				e = arc[v]; u = from[e];
				if ( eps > (cap[e] - flow[e]) ) eps = cap[e] - flow[e];
				v = u;
			}
			/* update flow and cost */
			v = t;
			while ( arc[v] >= 0 ){
				e = arc[v]; u = from[e];
				flow[e] += eps; flow[e^1] -= eps;
				C += cost[e] * eps;
				v = u;
			}
			F += eps;
		}
	}
	while ( d[t] < INT_MAX );

	return make_pair(F,C);
}

int main(){
	int K;

		scanf("%d %d", &N, &K);
		E = 0;
		fill( head, head + 2*N*N + 1, -1 );

		for ( int i=0; i < N; ++i ){
			for ( int j=0; j < N; ++j ){
				scanf("%d", &W[i][j]);
				if ( W[i][j] < 0 ) while(1);
				add_edge( in(cell(i,j)) , out(cell(i,j)), 1 , -W[i][j] );
				add_edge( in(cell(i,j)) , out(cell(i,j)), K - 1, 0 );
				if ( j + 1 < N ) add_edge( out(cell(i,j)) , in(cell(i,j+1)), K, 0 );
				if ( i + 1 < N ) add_edge( out(cell(i,j)) , in(cell(i+1,j)), K, 0 );
			}
		}
		
		pair<int,int> res = mcmf( in(cell(0,0)) , out(cell(N-1,N-1)), 2 * N * N );
		printf("%d\n", -res.second);
	
	return 0;
}

