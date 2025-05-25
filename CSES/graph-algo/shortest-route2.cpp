#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 612;

int N, M, Q;
long long D[MAXN][MAXN];

void floyd_warshall(){
	for ( int k=0; k < N; ++k )
		for ( int i=0; i < N; ++i )
			for ( int j=i + 1; j < N; ++j )
				if ( D[i][k] < LLONG_MAX && D[k][j] < LLONG_MAX )
					D[i][j] = D[j][i] = min( D[i][j], D[i][k] + D[k][j] );
			
}

int main(){
	int u, v, w;

	scanf("%d %d %d", &N, &M, &Q);

	for ( int i=0; i < N; i++ ){
		fill( D[i], D[i] + N, LLONG_MAX );
		D[i][i] = 0;
	}

	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		D[u][v] = D[v][u] = min( D[u][v], (long long)w );
	}

	floyd_warshall();
	
	while ( Q-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		if ( D[u][v] == LLONG_MAX ) puts("-1");
		else printf("%lld\n", D[u][v]);
	}
	return 0;
}
