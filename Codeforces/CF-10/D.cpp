// Memory limit exceeded
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 512;
int A[MAXN];
int B[MAXN];
int H[MAXN];
int res[MAXN];

int dp[MAXN][MAXN][MAXN];
int opt[MAXN][MAXN][MAXN];

void print_sol( int N, int M, int S ){
	int m = 0; 
	while ( opt[N][M][S] ){
		switch ( opt[N][M][S] ){
			case 1: S--;	break;
			case 2: N--;	break;
			case 3: M--;	break;
			case 4: res[m++] = A[N - 1]; N--, M--, S--; break;
			case 5: N--, M--; break;
		}
	}
	reverse( res, res + m );
	for ( int i=0; i < m; ++i ){
		if (i) putchar(' ');
		printf("%d", H[ res[i] ]);
	}
	puts("");
}

int main(){
	int S;
	int N, M;
	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);
		H[i] = A[i];
	}
	sort( H, H + N );
	S = unique(H, H + N) - H;
	for ( int i=0; i < N; ++i )
		A[i] = lower_bound( H, H + S, A[i] ) - H;
	
	scanf("%d", &M);
	int m = 0, x;
	for ( int i=0; i < M; ++i ){
		scanf("%d", &x);
		int idx = lower_bound( H, H + S, x ) - H;	// Just store common elements with A[]
		if ( idx == S || H[idx] != x ) continue;
		B[m++] = idx;
	}
	M = m;
	// do the dp
	for ( int k=0; k < S; ++k ){
		for ( int i=1; i <= N; ++i ){
			for ( int j=1; j <= M; ++j ){
				if ( k ){ 
					dp[i][j][k] = dp[i][j][k - 1];
					opt[i][j][k] = 1; 
				}
				if ( A[i - 1] != B[j - 1] ){
					if ( dp[i][j][k] < dp[i - 1][j][k] ){
						dp[i][j][k] = dp[i - 1][j][k];
						opt[i][j][k] = 2; 
					}
					if ( dp[i][j][k] < dp[i][j - 1][k] ){
						dp[i][j][k] = dp[i][j - 1][k];
						opt[i][j][k] = 3;
					}
				}
				else if ( A[i - 1] <= k ){
					if ( dp[i][j][k] < dp[i - 1][j - 1][k - 1] + 1 ){
						dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
						opt[i][j][k] = 4; 				
					}
				}
				else {	// A[i] == B[j] > k
					if ( dp[i][j][k] < dp[i - 1][j - 1][k] ){
						dp[i][j][k] = dp[i - 1][j - 1][k];
						opt[i][j][k] = 5; 			
					}
				}
			}
		}
	}
	printf("%d\n", dp[N][M][S - 1]);
	print_sol( N, M, S - 1 );
	return 0;
}
