#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 256;

int A, B;
bool G[MAXN][MAXN] = {0};
int match[MAXN];
int vis[MAXN] = {0};
int t;

bool alt_path( const int &u ){
	if ( vis[u] >= t ) return false;
	vis[u] = t;
	int v;
	for ( v = 1; v <= B; ++v ){
		if ( !G[u][v] ){ // Over the complement of G
			if ( match[v] == -1 || alt_path( match[v] ) ){
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main(){
	int M;
	int u, v;
	int cases = 0;
	while ( scanf("%d %d %d", &A, &B, &M) && (A+B+M) ){
		while ( M-- ){
			scanf("%d %d", &u, &v);
			G[u][v] = true;
		}
		int max_match = 0;
		fill( match, match + B + 1, -1 );
		for ( int i=1; i <= A; ++i ){
			t++;
			if ( alt_path( i ) ){
				max_match++;
			}
		}
		printf("Case %d: %d\n", ++cases,A + B - max_match);
		// Clean up the graph
		for ( int i=1; i <= A; ++i )
			for ( int j=1; j <= B; ++j )
				G[i][j] = false;
	}
	return 0;
}

