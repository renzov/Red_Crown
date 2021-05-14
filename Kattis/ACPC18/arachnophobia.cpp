#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;
typedef pair<long long, int> pli;
const int MAXN = 100005;

vector<int> G[MAXN];
vector<int> W[MAXN];
int S[MAXN];
bool start[MAXN];
bool ends[MAXN];
bool forbid[MAXN];
long long d[MAXN];
long long dS[MAXN];

int N, T;
int K;

bool dijkstra( const long long &bound ){
	priority_queue< pli, vector<pli>, greater<pli> > q;
	fill( d, d + N, LLONG_MAX );

	for ( int i=0; i < N; ++i ) 
		if ( start[i] ){ 
			q.push( pli(0, i) );
			d[i] = 0;
		}
	
	int u, v, w, eps;
	
	while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( w > d[u] ) continue;
		if ( ends[u] ) return true;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i], eps = W[u][i];
			if ( forbid[v] || ((w + eps) > bound) ) continue;
			if ( d[v] > w + eps ){
				d[v] = w + eps;
				q.push( pli( d[v], v ) );
			}
		}
	}
	return false;
}

int main(){
	int M;
	int u, v, w;
	int s, t;

	scanf("%d %d %d", &N, &M, &T);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back( v );
		G[v].push_back( u );
		W[u].push_back( w );
		W[v].push_back( w );
	}
	scanf("%d %d", &s, &t);
	scanf("%d", &K);
	for ( int i=0; i < K; ++i )
		scanf("%d", S + i);

	fill( start, start + N, false );
	fill( ends, ends + N, false );
	fill( forbid, forbid + N, false );
	for ( int i=0; i < K; ++i ) start[ S[i] ] = true;
	// First calculate the minimum distance from S
	dijkstra( LLONG_MAX );
	for ( int i=0; i < N; ++i ) dS[i] = d[i];
	// do binary search
	long long L = 0;
	long long R = dS[s] + 1;
	long long bound;

	fill( start, start + N, false );
	fill( ends, ends + N, false );
	start[s] = true, ends[t] = true;
	while ( R - L > 1 ){
		
		bound = ( L + R ) >> 1;
		for ( int i=0;  i < N; ++i )
			if ( dS[i] < bound ) forbid[i] = true;
			else forbid[i] = false;

		if ( dijkstra( T ) ) 
			L = bound;
		else
			R = bound;
	}
	printf("%lld\n", L);
	return 0;
}
