#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 128;
int N, M, K;
int W[MAXN][MAXN];
int match[MAXN];
int d[MAXN];
bool vis[MAXN];
int idx[MAXN];
int S[MAXN]; //Stack
int top;

bool augment( int u ){
	S[top++] = u;
	if ( vis[u] ) return true;
	vis[u] = true;
	for ( int i=0; i < K; ++i ){
		if ( i != u && i != match[u] && !vis[i] ){
			int v = match[i];
			if ( d[v] < d[u] + W[u][i] - W[i][v] ){
				d[v] = d[u] + W[u][i] - W[i][v];
				if ( augment(v) ) return true;
			}				
		}
	}
	top--;
	vis[u] = false;
	return false;
}


int rndMaxMatch(){
	for ( int i=0; i < K; ++i ) idx[i] = i;
	for ( int i=0; i < K; i += 2 ) match[i] = i + 1, match[i+1] = i;
	
	for ( int t = 0; t < 3; ){
		fill( d, d + K, 0 );
		fill( vis, vis + K, false );			
		bool flag = false;
		top = 0;
		
		for ( int i=0; i < K; ++i ){
			if ( augment( idx[i] ) ){
				flag = true;
				// Change matching along augmenting path
				int v = match[ S[top - 1] ];
				int j = top - 2;
				while ( S[j] != S[top - 1] ){
					match[v] = S[ j ];
					swap( v , match[ S[j] ] );
					--j;
				} 
				match[ v ] = S[j];
				match[ S[j] ] = v;
				break;
 			}			
		}
		if ( !flag ) t++;
		if ( !flag ) random_shuffle( idx, idx + K );
	}

	int res = 0;
	for ( int i=0; i < K; ++i )
		if ( i < match[i] ) res += W[ i ][ match[i] ];

	return res;
}


int main(){
	int runs;
	int cases = 0;

	int u, v, w;

	scanf("%d", &runs);	
	while ( runs-- ){
		scanf("%d %d %d", &N, &M, &K);
		// Init weight matrix
		for ( int i=0; i < N; ++i ){
			fill( W[i], W[i] + N, INT_MAX );
			W[i][i] = 0;	
		}

		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &u, &v, &w );
			u--, v--;
			W[u][v] = W[v][u] = w;		
		}

		if ( K & 1 ){
			printf("Case %d: Impossible\n", ++cases);
			continue;
		}

		// Floy Warshall
		for ( int k=0; k < N; ++k )
			for ( int i=0; i < N; ++i )
				for ( int j=0; j < N; ++j )
					if ( W[i][k] < INT_MAX && W[k][j] < INT_MAX )
						W[i][j] = min( W[i][j] , W[i][k] + W[k][j] );
		
		
		for ( int i=0; i < K; ++i ){
			for ( int j=0; j < K; ++j )
				W[i][j] = -W[i][j];		
			W[i][i] = -INT_MAX;		
		}				
		
		printf("Case %d: %d\n", ++cases, -rndMaxMatch());
	}
	return 0;
}
