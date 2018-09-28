#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 1024;

int F[MAXN];
int D[MAXN];
int dp[2][25*MAXN];

int main(){
	int maxF;  
	int N, K, L;
	
	while ( scanf("%d %d %d", &N, &K, &L) && N ){
		maxF = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", F + i , D + i);
			maxF += F[i];
		}
		fill( dp[0], dp[0] + maxF + 1, INT_MAX );
		fill( dp[1], dp[1] + maxF + 1, INT_MAX );
		dp[0][0] = 0;
		if ( D[0] <= L ) dp[0][ F[0] ] = D[0];
		int last = 0;
		for ( int i=1; i < N; ++i ){
			for ( int j=0; j < maxF; ++j ){
				if ( dp[last][j] == INT_MAX ) continue;
				if ( dp[last][j] + D[i] <= L ){
					dp[1-last][ j + F[i] ] = min( dp[1-last][ j + F[i] ] , dp[last][j] + D[i] );
				}
				dp[1-last][ j ] = min( dp[1-last][j] , max( 0, dp[last][j] - K ) );
			}
			last ^= 1;
		}
		for ( int j=maxF; j >= 0; j-- )
			if ( dp[last][j] != INT_MAX ){
				printf("%d\n", j);
				break;
			} 	
	}
	return 0;
}
