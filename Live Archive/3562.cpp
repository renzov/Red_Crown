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
	POJ 3422 - Kaka's Matrix Travels
	LA 3562 - Remember the A La Mode!
*/
const int MAXE = 6000; /*  MAXE >= 2 x ((50 x 50) + 100) */
const int MAXV = 110;
int X, Y;
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
int W[55][55];

void add_edge(int u, int v, int c, int w){
	from[E] = u, to[E] = v, cost[E] = w, cap[E] = c, flow[E] = 0, nxt[E] = head[u], head[u] = E, E++;
	from[E] = v, to[E] = u, cost[E] = -w, cap[E] = c, flow[E] = c, nxt[E] = head[v], head[v] = E, E++;
}

void find_feasible_potential(){
	fill( pot, pot + X + Y + 2, 0 );
	/* d[ source ] = 0 
	   d[ x ] = 0, for x in X, since W[source][x] = 0
	*/
	for ( int i=1; i <= X; ++i ){
		for ( int j=1; j <= Y; ++j ){
			if ( W[i][j] < 0 ) continue;
			pot[ X + j ] = min( pot[ X + j ] , pot[ i ] - W[i][j] );
		}
	}
	int sink = X + Y + 1;
	for ( int j=X+1; j <= X+Y; ++j ){
		pot[ sink ] = min( pot[ sink ] , pot[ j ] ); /* W[ j ][ sink ] = 0 */
	}
}


pair<int,int> mcmf( int s , int t, int N, bool p ){
	int d[MAXV];
	int arc[MAXV];
	/* Find feasible potential */
	if (!p)
		fill( pot, pot + N, 0 ); /* cost >= 0 for every arc */
	else 
		find_feasible_potential();

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

int read(){
	int res = 0;
	char s[25];
	int pos = -1;
	int len;

	scanf("%s", s);
	if ( s[0] == '-' ) return -1;

	for ( len = 0; s[len]; ++len ){
		if ( s[len] == '.' ) pos = len;
		else {
			res *= 10;
			res += (int)( s[len] - '0' );
		}
	}
	if ( pos < 0 ) return res * 100;
	if ( (len - pos) == 1 ) return res * 100;
	if ( (len - pos) == 2 ) return res * 10;
	if ( (len - pos) == 3 ) return res;
	while (1);
	return res;
}


int main(){
	int w;
	int cases = 0;

	while ( scanf("%d %d",&X, &Y) && (X || Y) ){
		cases++;
		E = 0;
		fill( head, head + (X + Y + 2), -1 );
		
		for ( int i=1; i <= X; ++i ){
			scanf("%d",&w);
			add_edge( 0 , i , w , 0 );
		}
		for ( int i=X+1; i <= X + Y; ++i ){
			scanf("%d", &w);
			add_edge( i , X + Y + 1, w , 0 );
		}
		
		for ( int i=1; i <= X; ++i ){
			for ( int j=X+1; j <= X+Y; ++j ){
				w = read();
				if ( w >= 0 ) add_edge( i , j , INT_MAX , w );
				W[i][j-X] = w;
			}
		}

		pair<int,int> res1 = mcmf( 0 , X + Y + 1 , X + Y + 2, false );
		/* Clear flow */
		for ( int e=0; e < E; e += 2 ){
			flow[e] = 0; 
			cost[e] *= -1;
			flow[e^1] = cap[e];
			cost[e^1] *= -1;
		}
		pair<int,int> res2 = mcmf( 0 , X + Y + 1 , X + Y + 2, true  );
		res2.second *= -1;

		printf("Problem %d: %d.%02d to %d.%02d\n", cases, res1.second/100, res1.second%100, res2.second/100, res2.second%100);
	}
	return 0;
}

