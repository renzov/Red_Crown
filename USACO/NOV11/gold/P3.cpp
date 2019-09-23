#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 256;

int U, W;

int X1[MAXN];
int X2[MAXN];
int Y1[MAXN];
int Y2[MAXN];
int idxV[MAXN];
int idxH[MAXN];
vector<int> G[MAXN];

int match[MAXN];
bool vis[MAXN];

bool aug_path( const int &u ){
	if ( vis[u] ) return false;
	vis[u] = true;
	int w;
	for ( int i=0; i < G[u].size(); ++i ){
		w = G[u][i];
		if ( match[w] == -1 || aug_path( match[w] ) ){
			match[w] = u;
			return true;
		}
	}
	return false;
}

int main(){
	int N;

	U = 0, W = 0;	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d", X1+i, Y1+i, X2+i, Y2+i);
		
		if ( X1[i] > X2[i] ) swap( X1[i], X2[i] );
		if ( Y1[i] > Y2[i] ) swap( Y1[i], Y2[i] );

		if ( Y1[i] == Y2[i] )
			idxH[ U++ ] = i;	
		else 
			idxV[ W++ ] = i;
	}
	// Create the intersection graph
	int u, w;

	for ( int i=0; i < U; ++i ){	// Horizontal
		u = idxH[i];
		for ( int j=0; j < W; ++j ){	// Vertical
			w = idxV[j];
			if ( Y1[u] >= Y1[w] && Y1[u] <= Y2[w] && 
				 X1[w] >= X1[u] && X1[w] <= X2[u] ){	// Segments intersect
					G[ i ].push_back( j );	
			}
		}
	}
	// Find the maximum matching
	int M = 0;	// Size of maximum matching
	fill( match, match + W, -1 );
	for ( int i=0; i < U; ++i ){
		fill( vis, vis + U, false );
		if ( aug_path( i ) )
			M++;
	}
	printf("%d\n", N - M);	// num. vert. - min. vert. cover (Konig theorem) 
	return 0;
}
