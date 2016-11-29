#include <cstdio>
#include <algorithm>
#include <climits>
#include <cassert>
#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 55;
const int MAXE = 100000; // > (3*N*N - N) 
const int MAXV = 2000;  // > N*(N+1) / 2 + 2

int from[MAXE];
int to[MAXE];
int nxt[MAXE];
int cap[MAXE];
int flow[MAXE];
int head[MAXV];
int q[MAXV];
int bneck[MAXV];
int p[MAXV];
int a[MAXN];
int E;

void add_edge( int u, int v, int c ){
	from[E] = u; to[E] = v; nxt[E] = head[u]; head[u] = E; cap[E] = c; flow[E] = 0; E++;
	from[E] = v; to[E] = u; nxt[E] = head[v]; head[v] = E; cap[E] = c; flow[E] = c; E++;
}

int augment_path( int s, int t, int n ){
	int qf, qt;
	qt = qf = 0;
	q[qt++] = s;
	fill( p, p + n, -1 );
	p[s] = s;
	bneck[s] = INT_MAX;
	int u, v;
	int f = 0;
	while ( qf < qt && p[t] == -1 ){
		u = q[qf++];
		for ( int e=head[u]; e >= 0 ; e=nxt[e] ){
			v = to[e];
			if ( p[v] == -1 && flow[e] < cap[e] ){
				q[qt++] = v;
				p[v] = e;
				bneck[v] = min( bneck[u] , cap[e] - flow[e] );
			}
		}
	}
	if ( p[t] != -1 ){
		f = bneck[t];
		u = t;
		int e;
		while ( u != s ){
			e = p[u];
			flow[e] += f;
			flow[e^1] -= f;
			u = from[e];
		}
	}
	return f;
}

int max_flow( int s, int t, int n ){
	int f;
	int res = 0;
	while ( f=augment_path( s, t, n ) ) res += f;
	return res;
}

int main(){
	int runs;
	int res;
	int N;
	scanf("%d", &runs);
	while ( runs-- ){
		res = 0;
		scanf("%d", &N);
		for ( int i=1; i <= N; ++i ){
			scanf("%d", a+i);
			res += a[i];
		}
		// Create the graph 
		// Total vertices = N*(N+1)/2 + 2
		int total = ((N*(N+1)) >> 1) + 2;
		fill( head, head + total, -1 );
		E = 0;
		int source = 0;
		for ( int i=1; i <= N; ++i ){
			add_edge( source, i, a[i] );
		}
		int V = N + 1;
		for ( int i=1; i < N; ++i )
			for ( int j=i+1; j <= N; ++j ){
				add_edge( i , V, 1 );
				add_edge( j , V, 1 );
				V++;
			}
		int sink = V;
		for ( int i=N+1; i < V; ++i ) 
			add_edge( i , sink, 1 );
		V++;
		res += ( N * (N-1) ) >> 1;
		res -= 2*max_flow( source, sink, V );
		printf("%d\n", res );
	}
	return 0;
}

