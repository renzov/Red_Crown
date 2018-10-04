#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXM = 2005;
int dp[MAXM][MAXM] = {0};
int C[32];
char A[MAXM];

int main(){
	
	int N, M;
	int a, b;
	char c;
	
	scanf("%d %d", &N, &M);
	scanf("%s", A);
	
	for ( int i=0; i < N; ++i ){
		scanf(" %c %d %d", &c, &a, &b);
		C[ c - 'a' ] = min( a, b );
	}
	
	for ( int i=0; i < M; ++i ) 
		dp[i][i] = 0;
	
	int j;
	for ( int k=1; k < M; ++k ){
		for ( int i=0; (i + k) < M; ++i ){
			j = i + k;
			dp[i][j] = min( dp[i][j-1] + C[ A[j] - 'a' ] , dp[i + 1][j] + C[ A[i] - 'a' ] ); 
			if ( A[i] == A[j] )
				dp[i][j] = min( dp[i][j] , dp[i+1][j-1] );
		}
	}
	printf("%d\n", dp[0][M-1]);
	return 0;
}
