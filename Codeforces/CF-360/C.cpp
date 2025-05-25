#include<cstdio>

const int MAXN = 505;

bool dp[2][MAXN][MAXN]; // dp[i][j][k] = there is a subset using the first i elements that has sun j and contains a subset 
						//               of sum k 
int C[MAXN];

int main(){
	int N, K;

	scanf("%d %d", &N, &K );
	for ( int i = 1; i <= N; ++i )
		scanf("%d", C + i );

	dp[0][0][0] = true;
	int prev = 0;
	int act = 1;

	for ( int i = 1; i <= N; ++i ){
		for ( int j = 0; j <= K; ++j )
			for ( int k = 0; k <= j; ++k ){
				dp[act][j][k] = dp[prev][j][k];
				if ( C[i] <= j ){
					dp[act][j][k] |= dp[prev][ j - C[i] ][k];
					if ( C[i] <= k )
						dp[act][j][k] |= dp[prev][ j - C[i] ][ k - C[i] ];
				}
			}
		act ^= 1;
		prev ^= 1;
	}

	int cnt = 0;
	for ( int j = 0; j <= K; ++j )
		if ( dp[prev][K][j] ) cnt++;
	
	bool first = true;
	printf("%d\n", cnt );
	for ( int j = 0; j <= K; ++j )
		if ( dp[prev][K][j] ){
			if ( !first ) putchar(' ');
			printf("%d", j);
			first = false;
		}
	puts("");
	return 0;
}
