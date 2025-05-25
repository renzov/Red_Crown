#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXM = 20005;
const int MAXK = 205;
const int MAXN = 20005;
int N, M, K, Q;

int from[MAXM];
int to[MAXM];
int d[MAXM];

int idx[MAXN];
long long D[MAXK][MAXK];
long long S[MAXK][MAXN];
long long E[MAXK][MAXN];


void floyd_warshall(){
	for ( int k=0; k < K; ++k )
		for ( int i=0; i < K; ++i )
			for ( int j=0; j < K; ++j )
				if ( D[i][k] < LLONG_MAX && D[k][j] < LLONG_MAX )
					D[i][j] = min( D[i][j] , D[i][k] + D[k][j] );
}


int main(){
	//freopen ("vacationgold.in", "r", stdin);
	//freopen ("vacationgold.out", "w", stdout);
	
	scanf("%d %d %d %d", &N, &M, &K, &Q);
	
	fill( idx, idx + N, -1 );

	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", from + i, to + i, d + i);
		// 0-index-based
		from[i]--, to[i]--; 
	}	
	// Read ids
	int u, v, w;
	for ( int i=0; i < K; ++i ){
		scanf("%d", &u); u--;
		idx[u] = i;
	}

	// create Dance matrix for hubs and from hubs to vertex and viceversa
	for ( int i=0; i < K; ++i ){
		D[i][i] = 0;
		for ( int j=i + 1; j < K; ++j )
			D[j][i] = D[i][j] = LLONG_MAX;
	}
	
	for ( int i=0; i < M; ++i ){
		u = from[i], v = to[i];
		if ( idx[u] != -1 && idx[v] != -1 )
			D[ idx[u] ][ idx[v] ] = d[i];
	}

	for ( int i=0; i < K; ++i )
		for ( int j=0; j < N; ++j )
			S[i][j] = E[i][j] = LLONG_MAX;

	// calculate Dance between hubs
	floyd_warshall();
	// Precalc going from vertex to hub and reverse
	for ( int i = 0; i < M; ++i ){
		u = from[i], v = to[i];
		if ( idx[u] != -1 && idx[v] != -1 ) continue;
		if ( idx[u] != -1 ){ // hub --> v
			w = idx[u];
			if ( E[w][v] > d[i] ){
				E[ w ][ v ] = d[i];
				for ( int k = 0; k < K; ++k ){
					if ( w != k ) continue;
					if ( D[ k ][ w ] < LLONG_MAX )
						E[ k ][ v ] = min( E[k][v], D[k][w] + E[w][v] );
				}
			}
		}
		else {  // u --> hub
			w = idx[ v ];
			if ( S[ w ][ u ] > d[i] ){	// Relax Dance matrix
				S[ w ][ u ] = d[i];
				for ( int k = 0; k < K; ++k ){
					if ( k == w ) continue;
					if ( D[w][k] < LLONG_MAX )
						S[ k ][ u ] = min( S[ k ][ u ], S[ w ][ u ] + D[ w ][ k ] );
				}
			}
		}
	}
	// Process the queries
	long long res;
	long long total = 0;
	int cnt = 0;
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		if ( idx[u] != -1 && idx[v] != -1 ){
			res = D[ idx[u] ][ idx[v] ];
		}
		else if ( idx[u] != -1 ){	// hub --> v
			res = E[ idx[u] ][ v ];
		}
		else if ( idx[v] != -1 ){	// u --> hub
			res = S[ idx[v] ][ u ];
		}
		else {
			res = LLONG_MAX;
			for ( int k = 0; k < K; ++k ){
				if ( S[k][u] < LLONG_MAX && E[k][v] < LLONG_MAX )
					res = min( S[k][u] + E[k][v], res );
			}
		}
		if ( res != LLONG_MAX ){
			cnt++;
			total += res;
			printf("%lld\n", res);
		}
		else {
			puts("-1");
		}
	}
	//printf("%d\n%lld\n", cnt, total);
	return 0;
}
