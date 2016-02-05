#include<cstdio>
#include<climits>
#include<algorithm>
#include<queue>
using namespace std;
/* 
	Implementation tested in problems 
	LA 3987 - Finest Chef
*/
const int MAXE = 177000; /*  MAXE < 2 x ((350 x 250) + 350 + 250) */
const int MAXV = 605;
int X,Y;
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

pair<int,int> mcmf( int s , int t ){
	int d[MAXV];
	int arc[MAXV];
	int N = X + Y + 2;
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

int main(){
	int runs;
	int M;
	int u,v,w;

	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%d %d",&X, &Y);
		scanf("%d", &M);
		/* Chefs: 1 ... X - Facility: X+1 ... X+Y  */
		/* Source: 0 - Sink: X + Y + 1 */
		
		/* Init */
		fill( head, head + X + Y + 2, -1 );
		E = 0;

		while (M--){
			scanf("%d %d %d",&u, &v, &w);
			add_edge( u + 1 , v + X + 1, 1 , w );
		}
		
		/* Add edge from source to every chef */
		for ( int i=1; i <= X; ++i ) add_edge( 0 , i , 1 ,  0 );
		/* Add edge from every facility to sink */
		for ( int i=X+1; i <= (X + Y) ; ++i ) add_edge( i , X + Y + 1, 1 , 0 );
		
		/* Find MinCost Max Flow */
		pair<int,int> res = mcmf( 0 , X + Y + 1 );
		printf("%d\n", res.second);

		if (runs) puts("");
	}
	return 0;
}

