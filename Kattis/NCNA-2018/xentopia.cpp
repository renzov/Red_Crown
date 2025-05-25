#include<cstdio>
#include<climits>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXE = 1105;
const int MAXN = 455;

struct state {
	long long d;
	int vtx;
	int k1;
	int k2;
	
	state(){}
	state( const long long &d1, const int &u, const int &a, const int &b ){
		d = d1, vtx = u, k1 = a, k2 = b;
	}
	
	bool operator<( const state &S ) const {
		return d > S.d;	// reverse the comparison because priority_queue is max heap default
	}
};

int N, M; 
int K1, K2;
int X[MAXE], Y[MAXE], W[MAXE], T[MAXE];

vector<int> G[MAXN];
vector< vector<long long> > d[MAXN];

inline int get_vertex( const int &e, const int &u ){
	return X[e] == u? Y[e]:X[e]; 
}

long long dijkstra( const int &s, const int &t ){
	// Initialization
	for ( int i=0; i < N; ++i )
		d[i] = vector< vector<long long> > ( K1 + 1, vector<long long>( K2 + 1, LLONG_MAX ) );

	d[s][0][0] = 0;
	priority_queue< state > q;

	q.push( state( 0LL, s, 0, 0 ) );

	int u, v, e, r, b, nr, nb;
	state S;
	long long w, nw;

	while ( !q.empty() ){
		S = q.top();
		q.pop();
		u = S.vtx, w = S.d, r = S.k1, b = S.k2;

		if ( d[u][r][b] < w ) continue;
		if ( u == t && r == K1 && b == K2 ) return w; // reached optimal final state

		for ( int i=0; i < (int)G[u].size(); ++i ){
			e = G[u][i];
			v = get_vertex( e, u );
			
			nw = w + W[e];
			nr = r, nb = b;

			if ( T[e] == 1 ) nr++;
			if ( T[e] == 2 ) nb++;

			if ( nr > K1 || nb > K2 ) continue;

			if ( d[v][nr][nb] > nw ){
				d[v][nr][nb] = nw;
				q.push( state( nw, v, nr, nb ) );
			}	
		}
	}
	return -1;
}

int main(){
	int u, v;
	int s, t;

	scanf("%d %d %d %d", &N, &M, &K1, &K2);
	for ( int i = 0; i < M; ++i ){
		scanf("%d %d %d %d", X + i, Y + i, W + i, T + i );
		u = --X[i];
		v = --Y[i];
		G[ u ].push_back( i );
		G[ v ].push_back( i ); 
	}
	
	scanf("%d %d", &s, &t);
	s--, t--;

	printf("%lld\n", dijkstra( s, t ));
	return 0;
}


