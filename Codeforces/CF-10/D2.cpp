#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 512;
int A[MAXN];
int B[MAXN];
int H[MAXN];
int res[MAXN];

int dp[MAXN][MAXN];		/* dp[i][j] - LCIS of arrays A[0..i-1] and B[0..j-1] that ends at A[i-1]  */
int opt[MAXN][MAXN];

void print_sol( int N, int M ){
	int m = 0; 
	while ( N > 0 && M > 0 ){
		if ( opt[N][M] == -1 ){
			M--;
		}
		else {
			res[ m++ ] = H[ A[N - 1] ];
			N = opt[N][M];
			M--;
		}
	}
	reverse( res, res + m );
	for ( int i=0; i < m; ++i ){
		if (i) putchar(' ');
		printf("%d", res[i]);
	}
	puts("");
}

int main(){
	int S;
	int N, M;
	int idx, best;

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
		idx = lower_bound( H, H + S, x ) - H;	// Just store common elements with A[]
		if ( idx == S || H[idx] != x ) continue;
		B[m++] = idx;
	}
	M = m;
	// do the dp
	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= M; ++j ){
			if ( A[i - 1] != B[j - 1] ){
				dp[i][j] = dp[i][j - 1];
				opt[i][j] = -1;
			}
			else {
				best = 0;
				idx = 0;
				for ( int k=i - 1; k > 0; --k ){
					if ( A[k - 1] < A[i - 1] && dp[k][j - 1] > best ){
						best = dp[k][j - 1];
						idx = k;
					}
				} 
				dp[i][j] = best + 1;
				opt[i][j] = idx;
			}
		}
	
	best = 0;
	int n = 0;
	m = 0;
	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= M; ++j )
			if ( dp[i][j] > best ){
				best = dp[i][j];
				n = i, m = j;
			}
	printf("%d\n", best);
	print_sol( n, m );
	return 0;
}
