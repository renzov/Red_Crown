#include <cstdio>
#include <algorithm>
#include <vector>

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

const int INF = 100000000;
const int MAXV = 101005;

int T, N;
bool sink[ 1005 ];
vector<int> from;
vector<int> to;
vector<int> cap;
vector<int> flow;
vector<int> next;
int head[MAXV];
int E;
inline int vert( int i, int j ){ return i*(T+1) + j; }

int seen[MAXV];
int prev[MAXV];
int q[MAXV];
int bneck[MAXV];
int time;
int qf,qt;

void add_edge( int u, int v, int c ){
	from.push_back(u); to.push_back(v); next.push_back( head[u] ); flow.push_back(0); cap.push_back(c); head[u] = E++; 
	from.push_back(v); to.push_back(u); next.push_back( head[v] ); flow.push_back(c); cap.push_back(c); head[v] = E++;
}

int augment_path( int s, int t ){
	qt = qf = 0;
	q[ qt++ ] = s;
	bneck[s] = INF;
	int f = 0;
	int u, v;
	while ( qf < qt && seen[t] < time ){
		u = q[qf++];
		for ( int e=head[u]; e >= 0; e=next[e] ){
			v = to[e];
			if ( seen[v] < time && flow[e] < cap[e] ){
				seen[v] = time;
				prev[v] = e;
				q[qt++] = v;
				bneck[v] = min( bneck[u] , cap[e] - flow[e] );
			}
		}
	}
	if ( seen[t] == time ){ // path augmentation
		int e;
		f = bneck[t];
		v = t;
		while ( v != s ){
			e = prev[v];
			flow[e] += f;
			flow[e^1] -= f;
			v = from[e];
		}
	}
	return f;
}

int max_flow( int s, int t ){
	int res = 0;
	int f;
	fill( seen, seen + t + 2, -1 );
	time = 0;
	while ( f=augment_path(s,t) ){
		res += f;
		time++;
	}
	return res;
}

int main(){
	int runs;
	int g, start;
	int n, m;
	int u, v;
	int a, b, p, ti;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d %d %d", &n, &start, &g, &T, &m);
		start--;
		N = (T+1)*n;
		//Setting up structures
		E = 0;
		from.clear(); to.clear(); cap.clear(); next.clear(); flow.clear();
		fill( head, head + N + 4, -1 );
		fill( sink, sink + n, false );
		//
		for ( int i=0; i < m; ++i ){
			scanf("%d", &u);
			u--;
			sink[u] = true;
		}
		scanf("%d", &m);
		while ( m-- ){
			scanf("%d %d %d %d", &a, &b, &p, &ti);
			a--, b--;
			// adding all the possible edges
			for ( int k=0; k <= (T - ti); ++k ){
				add_edge( vert(a,k) , vert(b,k+ti), p );
			}
		}
		// adding the possibility of staying
		for ( int i=0; i < n; ++i )
			for ( int k=0; k < T; ++k ){
				add_edge( vert(i,k) , vert(i,k+1) , INF );
			}
		// source = N, sink = N + 1
		int s = N, t = N + 1;
		add_edge( s , vert(start, 0), g );
		for ( int i=0; i < n; ++i )
			if ( sink[i] ) add_edge( vert(i,T), t, INF );

		printf("%d\n", max_flow(s,t));
	}
	return 0;
}

