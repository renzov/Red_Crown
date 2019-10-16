#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 32;

int N;
int match[MAXN];
bool vis[MAXN];
int W[MAXN][MAXN];
int V[MAXN*MAXN];

bool alt_path( const int &u, const int &w ){
	if ( vis[u] ) return false;
	vis[u] = true;
	for ( int v=0; v < N; ++v ){
		if ( w > W[u][v] ) continue;
		if ( match[v] == -1 || alt_path( match[v], w ) ){
			match[v] = u;
			return true;
		}
	}
	return false;
}

bool max_matching( const int &w ){
	fill( match, match + N, -1 );
	for ( int i=0; i < N; ++i ){
		fill( vis, vis + N, false );
		if ( !alt_path(i, w) ) return false;
	}
	return true;
}

int main(){
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			scanf("%d", W[i]+ j);
			V[ i*N + j ] = W[i][j];
		}

	sort( V, V + N*N );
	int M = unique( V, V + N*N ) - V;
	
	int l = max_matching( V[M-1] )? (M - 1):0;
	int r = M - 1;
	int m;

	while ( r - l > 1 ){
		m = ( l + r ) >> 1;
		if ( max_matching( V[m] ) ) l = m;
		else r = m;
	}
	printf("%d\n", V[l]);
	return 0;
}
