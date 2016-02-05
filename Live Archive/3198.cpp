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
*/
const int MAXE = 30000; /*  MAXE < 2 x ((100 x 100) + 200) */
const int MAXV = 205;
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

int manhattan( const pair<int,int> &A, const pair<int,int> &B ){
	return abs( A.first - B.first ) + abs( A.second - B.second );
}

int main(){
	int N, M;
	char line[35];
	
	pair<int,int> H[105];
	pair<int,int> m[105];

	while ( scanf("%d %d",&N, &M) && N && M ){
		X = Y = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%s", line);
			for ( int j=0; line[j]; ++j ){
				if ( line[j] == 'H' ){
					H[Y++] = make_pair( i , j );
				}
				else if ( line[j] == 'm' ){
					m[X++] = make_pair( i , j );
				}
			}
		}

		E = 0;
		fill( head, head + X + Y + 2, -1 );

		for ( int i=0; i < X; ++i )
			for ( int j=0; j < Y; ++j ){
				add_edge( i + 1, X + j + 1, 1 , manhattan( m[i] , H[j] ) );
			}
		for ( int i=1; i <= X; ++i ) add_edge( 0 , i , 1, 0 );
		for ( int i=(X+1); i <= (X+Y); ++i ) add_edge( i , X+Y+1, 1, 0 );
		pair<int,int> res = mcmf( 0 , X + Y + 1 );
		printf("%d\n", res.second);
	}
	return 0;
}

