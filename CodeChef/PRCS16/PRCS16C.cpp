#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>
using namespace std;
typedef pair<int,int> state;
typedef pair<int, state> node;

const int MAXP = 10;
const int MAXN = 100005;
int N, M, P, K;
int s, t;
int W[MAXP + 6];
int WP[1 << MAXP];
int I[MAXP + 6];
int d[MAXN];
vector<int> G[MAXN];
int mask[MAXN];

void bfs( const int &st ){
	queue<int> q;
	q.push( st );
	d[st] = 0;

	int u, v;
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		if ( d[u] >= K ) continue;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] == -1 ){
				d[v] = d[u] + 1;
				q.push( v );
			}
		}
	}
}

bool reachable( const int &m ){
	queue<int> q;
	q.push(s);
	d[s] = 0;
	
	int u, v;
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		if ( u == t ) return true;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( mask[v] & ~m ) continue;
			if ( d[v] == -1 ){
				d[v] = d[u] + 1;
				q.push( v );
			}
		}
	}
	return false;
}

int main(){
	int u, v;
	scanf("%d %d %d %d", &N, &M, &P, &K);	
	for ( int i=0; i < P; ++i ){ scanf("%d", I + i); I[i]--; }
	for ( int i=0; i < P; ++i ) scanf("%d", W + i);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	scanf("%d %d", &s, &t);
	s--, t--;
	// Find the vertices that are reachable from each gang
	fill( d, d + N, -1 );
	for ( int i=0; i < P; ++i ){
		bfs( I[i] );
		for ( int j=0; j < N; ++j )
			if ( d[j] != -1 ){
				mask[j] |= ( 1 << i );
				d[j] = -1;	// for next iteration
			}
	}
	mask[s] = mask[t] = 0;	// You do not pay at s or t
	// Precalculate all the possible union of weights
	WP[0] = 0;
	for ( int i=1; i < (1 << P); ++i ){
		WP[i] = 0;
		for ( int j=0; j < P; ++j )
			if ( (i >> j) & 1 )
				WP[i] += W[j];
	}

	int res = INT_MAX;
	for ( int i=0; i < (1 << P); ++i ){
		if ( WP[i] >= res ) continue;
		if ( reachable( i ) )
			res = WP[i];
		fill( d, d + N, -1 );
	}
	printf("%d\n", res);
	return 0;
}
