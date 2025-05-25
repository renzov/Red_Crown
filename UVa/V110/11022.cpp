#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 128;
char S[MAXN];
int period[MAXN][MAXN];
int prefix[MAXN];
int dp[MAXN][MAXN];

void prefix_function( char *P, const int &len ){
	int j;

	prefix[0] = 0;	
	for ( int i = 1; i < len; ++i ){
		j = prefix[i - 1];
		while ( j > 0 && P[i] != P[j] )
			j = prefix[ j - 1 ];
		if ( P[i] == P[j] )
			j++;
		prefix[i] = j;
	}
}

void process(){
	int N = strlen( S );
	int K;
	int L;

	// Calculates for each substring the period of the string
	for ( int i = 0; i < N; ++i ){
		L = N - i;	// length of string S[ i ... N - 1 ]
		prefix_function( S + i, N - i );
		period[i][i] = 1;
		for ( int j = i + 1; j < N; ++j ){
			L = j - i + 1;
			K = L - prefix[ L - 1 ];
			if ( L % K ) period[i][j] = L;
			else period[i][j] = K;
		}
	}

	for ( int i = 0; i < N; ++i )
		dp[i][1] = 1;

	// Now de calculate the optimum for each substring
	for ( int len = 2; len <= N; ++len )
		for ( int i = 0; i <= (N - len); ++i ){
			// First we check whether the substring is periodic
			int j = i + len - 1;			
			if ( period[i][j] == len ) dp[i][len] = len;
			else dp[i][len] = dp[i][ period[i][j] ];
			
			for ( int k = i + 1; k <= j; ++k ){
				int left = k - i;
				int right = len - left;
				dp[i][len] = min( dp[i][len], dp[i][left] + dp[k][right] );
			}
		}

	printf("%d\n", dp[0][N]);
}

int main(){
	while ( scanf("%s", S) && S[0] != '*' )
		process();
	return 0;
}
