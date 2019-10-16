#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 505;
int N, M, D, T;
long long W1[MAXN][MAXN];
long long W2[MAXN][MAXN];
int idx[MAXN];
bool spec[MAXN] ={0};

void clean( long long G[MAXN][MAXN], const int &n ){
	for ( int i=0; i < n; ++i ){
		G[i][i] = 0;
		for ( int j=i+1; j < n; ++j )
			G[i][j] = G[j][i] = LLONG_MAX;
	}
}

void floyd( long long G[MAXN][MAXN], const int &n ){
	for ( int k=0; k < n; ++k )
		for ( int i=0; i < n; ++i )
			for ( int j=0; j < n; ++j )
				if ( i != j && G[i][k] < LLONG_MAX && G[k][j] < LLONG_MAX )
					G[i][j] = min( G[i][j] , G[i][k] + G[k][j] );
}

int main(){
	int u, v, w;

	scanf("%d %d %d %d", &N, &M, &T, &D);
	clean( W1, N );
	spec[0] = spec[N - 1] = true;	
	for ( int i=0;  i < T; ++i ){
		scanf("%d", &u);
		u--;
		spec[u] = true;
	}
	T = 0; 
	for ( int i=0; i < N; ++i )
		if ( spec[i] ) idx[T++] = i;
	
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		W1[u][v] = W1[v][u] = w; 
	}
	
	floyd( W1, N );
	clean( W2, T );	
	
	for ( int i=0; i < T; ++i ){
		u = idx[i];
		for ( int j=i+1; j < T; ++j ){
			v = idx[j];
			if ( W1[u][v] <= D )
				W2[i][j] = W2[j][i] = W1[u][v];
		}
	}

	floyd( W2, T );
	
	if ( W2[0][T-1] < LLONG_MAX ) printf("%lld\n", W2[ 0 ][ T - 1 ]);
	else puts("stuck");
	return 0;
}
