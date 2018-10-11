#include<vector>
#include<queue>
#include<algorithm>
#include<cstdio>
#include<climits>
using namespace std;
const int MAXN = 128;
const int MAXK = 16; 
typedef pair<int,int> pii;
typedef pair< int, pii > piii;

vector<int> G[MAXN];
vector<int> W[MAXN];
int A, B, L;
int N, K;
int D[MAXN][MAXN];
int dist[MAXK][MAXN];

void dijkstra1( const int &s, int d[] ){
	fill( d, d + N, INT_MAX );
	priority_queue< pii, vector<pii>, greater<pii> > q;
	
	d[s] = 0;
	q.push( pii( 0, s ) );
	int u, v , w, c;
	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second;
		q.pop();
		if ( w > d[u] ) continue;
		if ( u != s && u >= A ) continue;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			c = W[u][i];
			if ( d[v] > w + c ){
				d[v] = w + c;
				q.push( pii( d[v], v ) );
			}
		}
	}
}

int dijksktra2( const int &s, const int &t ){
	for ( int i=0; i <= K; ++i )
		fill( dist[i], dist[i] + N, INT_MAX );
	priority_queue< piii, vector<piii>, greater<piii> > q;
	
	dist[K][s] = 0;
	q.push( piii( 0, pii( s, K ) ) );
	int u, v, w, c;
	int k;
	
	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second.first;
		k = q.top().second.second;
		q.pop();
		if ( w > dist[k][u] ) continue;
		if ( u == t ) return w;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			c = W[u][i];
			if ( c > 0 ){
				if ( dist[k][v] > w + c ){
					dist[k][v] = w + c;
					q.push( piii( w + c, pii( v, k ) ) );
				}
			}
			else if ( k > 0 && dist[k - 1][v] > w ){
				dist[k -1][v] = w + c;
				q.push( piii( w, pii( v, k - 1 ) ) );
			}  
		}
	}
	return INT_MAX;
}

void process(){
	int M;
	int u, v, w;
	scanf("%d %d %d %d %d", &A, &B, &M, &L, &K);		
	N = A + B;
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back( v ); W[u].push_back( w );
		G[v].push_back( u ); W[v].push_back( w );
	}
	// First calculate the distance between every pair of vertices such that 
	// every internal vertex is a village
	for ( int i=0; i < N; ++i )
		dijkstra1( i, D[i] );	
	// Add the zero weight edges 
	// Observe that normal edges have positive weight
	for ( u=0; u < N; ++u )
		for ( v=0; v < u; ++v )
			if ( D[u][v] <= L ){
				G[u].push_back(v); W[u].push_back(0);
				G[v].push_back(u); W[v].push_back(0);
			}
	printf("%d\n", dijksktra2( N - 1, 0 ) );
}


int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		if ( runs ){ //Clean memory up
			for ( int i=0; i < N; ++i ){
				G[i].clear();
				W[i].clear();
			}
		}
	}
	return 0;
}
