#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 5005;

int sz[MAXN];
int cnt[MAXN][MAXN];
int dp[MAXN][MAXN];
int best[MAXN][MAXN];
vector<int> V[MAXN];

int main(){
	int N, K, S;
	int A;

	scanf("%d %d %d", &N, &K, &S);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &A);
		sz[ i % K ]++;
		cnt[ i % K ][ A ]++;
		V[i % K].push_back( A );
	}
	// Erase duplicates per class
	for ( int i=0; i < K; ++i ){
		sort( V[i].begin(), V[i].end() );
		V[i].erase( unique( V[i].begin(), V[i].end() ), V[i].end() );
	}
		
	// Initialization
	for ( int j=0; j <= S; ++j ){
		dp[0][j] = sz[0] - cnt[0][j];
		if ( j > 0 )
			best[0][j] = min( dp[0][j] , best[0][j - 1] );
		else
			best[0][j] = dp[0][j];
	}

	int v;
	for ( int i=1; i < K; ++i ){
		for ( int j=0; j <= S; ++j ){
			dp[i][j] = best[i - 1][j] + sz[i]; 
			for ( int k=0; k < (int)V[i].size(); ++k ){
				v = V[i][k];
				if ( v <= j )
					dp[i][j] = min( dp[i][j], dp[i - 1][ j - v ] + sz[i] -  cnt[ i ][ v ] );
			}
			if ( j > 0 )
				best[i][j] = min( best[i][j - 1], dp[i][j] );
			else
				best[i][j] = dp[i][j];
		}
	}
	printf("%d\n", dp[K - 1][S]);
	return 0;
}
