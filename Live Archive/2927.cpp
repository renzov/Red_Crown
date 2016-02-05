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
*/
const int MAXE = 20200; /*  MAXE < 2 x ((100 x 100) + 200) */
const int MAXV = 150;

int E;
/* variables used in flow */
int from[MAXE];
int to[MAXE];
int cost[MAXE];
int cap[MAXE];
int flow[MAXE];
int nxt[MAXE];
int head[MAXV];
int pot[MAXV];


void add_edge(int u, int v, int c, int w){
	from[E] = u, to[E] = v, cost[E] = w, cap[E] = c, flow[E] = 0, nxt[E] = head[u], head[u] = E, E++;
	from[E] = v, to[E] = u, cost[E] = -w, cap[E] = c, flow[E] = c, nxt[E] = head[v], head[v] = E, E++;
}

pair<int,int> mcmf( int s , int t, int N ){
	int d[MAXV];
	int arc[MAXV];
	/* Find feasible potential */
	fill( pot, pot + N, 0 ); /* cost >= 0 for every arc */

	int u, v, c, w, e;
	int F = 0, C = 0;
	
	do {
		/* Find shortest path from s */
		fill( d , d + N, INT_MAX );
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

inline int in(int x){ return x << 1; }
inline int out(int x){ return (x << 1) | 1; }

int main(){
	int N, M;
	int u, v, w;
	int cases = 0;

	while ( scanf("%d %d",&N, &M) && (N || M) ){
		cases++;
		E = 0;
		fill( head, head + 2*N, -1 );

		if ( M > 10000 || N > 64 ) while(1);
		
		while ( M-- ){
			scanf("%d %d %d", &u, &v, &w);
			if ( w < 0 ) while (1);
			add_edge( out(u), in(v), 1 ,  w );
		}

		add_edge( in(0) , out(0) , 2 , 0 );
		for ( int i=1; i < (N-1); ++i ) add_edge( in(i) , out(i), 1, 0 );

		pair<int,int> res = mcmf( in(0) , in(N-1), 2 * N );

		printf("Instance #%d: ", cases);
		if (res.first < 2) puts("Not possible");
		else printf("%d\n", res.second);
	}
	return 0;
}

