#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 128;

char S[MAXN];
int N;
int period[MAXN][MAXN];
int dp[MAXN][MAXN];		// dp[i][len] = min # of chars after compression of S[i ... i  + len - 1]
int opt[MAXN][MAXN];	// if we print the whole string: opt[i][len] = 0
						// if we compress to the period: opt[i][len] = -K	(K is length of period >= 1)
						// if we break the string: opt[i][len] = length of left part
int p[MAXN];
int cost[MAXN];

void prefix_function( char *pattern ){
	p[0] = 0;
	int j;
	for ( int i = 1; pattern[i]; ++i ){
		j = p[i - 1];
		while ( j > 0 && pattern[j] != pattern[i] )
			j = p[j - 1];
		if ( pattern[i] == pattern[j] )
			j++;
		p[i] = j;
	}
}

void print_solution( const int &i, const int &len ){	
	if ( opt[i][len] == 0 ){
		for ( int k = i; k < (i + len); ++k )
			putchar( S[k] );
	}
	else if ( opt[i][len] < 0 ){
		int K = -opt[i][len];
		int t = len / K;
		printf("%d(", t);
		print_solution( i, K );
		putchar(')');
	}
	else {
		print_solution( i, opt[i][len] );
		print_solution( i + opt[i][len], len - opt[i][len] ); 
	}
}

int main(){
	freopen ("folding.in", "r", stdin);
	freopen ("folding.out", "w", stdout);

	scanf("%s", S);
	N = strlen(S);

	// precalculate printing 
	for ( int i = 0; i < 100; ++i )
		cost[i] = ( i < 10 )? 1:2;
	cost[100] = 3;

	// Precalculate the period for each substring
	int L, K, W, t;
	int left, right;
	for ( int i = 0; i < N; ++i ){
		prefix_function( S + i );
		period[i][i] = 1;
		for ( int j = i + 1; j < N; ++j ){
			L = j - i + 1;
			K = L - p[L - 1];
			if ( L % K ) period[i][j] = L;
			else period[i][j] = K;
		}	
	}
	// Initialize the dp table	
	for ( int i	= 0; i < N; ++i )
		dp[i][1] = 1, opt[i][1] = 0;
	// do dp to find the best way to compress the string
	for ( int len = 2; len <= N; ++len ){
		for ( int i = 0; i <= (N - len); ++i ){
			int j = i + len - 1;
			// calculate dp[i][len]
			dp[i][len] = len, opt[i][len] = 0;			// no compression
			if ( period[i][j] < len ){					// it is a periodic substring
				K = period[i][j];
				t = len / K;							// exponent of period
				W = dp[i][K] + cost[t] + 2;				// cost of compressing
				if ( dp[i][len] > W ){
					dp[i][len] = W, opt[i][len] = -K;	// it is better to compress to period
				}
			}
			// Test every possible way to break the string
			for ( int k = i + 1; k <= j; ++k ){
				left = k - i;
				right = len - left;
				if ( dp[i][len] > (dp[i][left] + dp[k][right]) ){
					dp[i][len] = dp[i][left] + dp[k][right];
					opt[i][len] = left;
				}
			}
		}
	}
	print_solution( 0, N ); 
	puts("");
	return 0;
}
