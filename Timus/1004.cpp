#include<cstdio>
#include<climits>
using namespace std;
const int MAXN = 128;

int W[MAXN][MAXN];
int G[MAXN][MAXN];
int pre[MAXN][MAXN];
int path[MAXN];
int P;

void get_path( const int &u, const int &v ){
	if ( pre[u][v] == -1 ){
		if ( P == 0 || path[P - 1] != u )
			path[P++] = u;
		if ( P != 0 || path[P - 1] != v )
			path[P++] = v;
		return;
	}
	get_path( u, pre[u][v] );
	get_path( pre[u][v], v );
} 

void process(const int &N){
	int M;

	scanf("%d", &M);
	// Initialize cost matrix
	for ( int i=0; i < N; ++i ){
		G[i][i] = W[i][i] = 0;
		pre[i][i] = -1; 
		for ( int j=i + 1; j < N; ++j ){
			W[i][j] = W[j][i] = INT_MAX;
			G[i][j] = G[j][i] = INT_MAX;
			pre[i][j] = pre[j][i] = -1;
		}
	}
	// Read the graph
	int u, v, w;
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		if ( W[u][v] > w ){
			W[u][v] = W[v][u] = w;
			G[u][v] = G[v][u] = w;
		}
	}
	// Calculate the shortest cycle
	int best = INT_MAX;
	for ( int k=0; k < N; ++k ){
		// Find the shortest cycle where k is the largest vertex
		// W[i][j] = length of shortest path between i and j using vertices in {0, ...., k - 1}
		int bestKCycle = INT_MAX;
		int S, T;
		for ( int i=0; i < k; ++i ){
			for ( int j=i + 1; j < k; ++j ){
				if ( W[i][j] < INT_MAX && G[i][k] < INT_MAX && G[k][j] < INT_MAX ){
					int len = W[i][j] + G[i][k] + G[k][j];
					if ( bestKCycle > (W[i][j] + G[i][k] + G[k][j]) ){
						bestKCycle = W[i][j] + G[i][k] + G[k][j];
						S = i, T = j;
					}
				}
			}
		}
		if ( bestKCycle < best ){	// Save the answer
			P = 0;
			get_path( S, T );
			path[P++] = k;
			best = bestKCycle;
		}
		// Floyd-Warshall
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				if ( W[i][k] < INT_MAX && W[k][j] < INT_MAX ){
					if ( W[i][j] > (W[i][k] + W[k][j]) ){
						W[i][j] = W[i][k] + W[k][j];
						pre[i][j] = k;
					}
				}
	}

	if ( best < INT_MAX ){ // Print cycle
		for ( int i=0; i < P; ++i ){
			if (i) putchar(' ');
			printf("%d", path[i] + 1);
		}
		puts("");
	}
	else {
		puts("No solution.");
	}
}

int main(){
	int N;
	while ( scanf("%d", &N) && N > 0 ) process(N);
	return 0;
}
