#include<cstdio>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;

int cost[1024][32][32];
int dp[1024][32];

void find_cost( const int &idx, const int &K, char *S ){
	int f[32];
	
	fill( f, f + 26, 0 );

	for ( int i=0; i < 26; ++i )
		fill( cost[idx][i], cost[idx][i] + 26, INT_MAX );

	for ( int i=0; i < K; ++i ) f[ S[i] ]++;

	int cnt = 0;
	for ( int i=0; i < 26; ++i ) 
		if ( f[i] ) cnt++;

	for ( int i=0; i < 26; ++i )
		if ( f[i] )
			for ( int j=i+1; j < 26; ++j )
				if ( f[j] )
					cost[idx][j][i] = cost[idx][i][j] = cnt;

	for ( int i=0; i < 26; ++i )
		if ( cnt == 1 ){
			if ( f[i] ) cost[idx][i][i] = 1;
		}
		else if ( f[i] > 1 ){
			cost[idx][i][i] = cnt + 1;
		}
}

void process(){
	char S[1042];
	int N, K, M;
	scanf("%d %s", &K, S);
	N = strlen(S);
	for ( int i=0; i < N; ++i ) S[i] = (char)(S[i] - 'a');	
	M = N / K;
	for ( int i=0; i < M; ++i )
		find_cost( i , K, S + i*K );
	
	// Initialize dp
	for ( int j=0; j < 26; ++j ){
		dp[0][j] = INT_MAX;
		for ( int i=0; i < 26; ++i )
			dp[0][j] = min( dp[0][j], cost[0][i][j] );
	}
	for ( int k=1; k < M; ++k ){
		for ( int j=0; j < 26; ++j ){
			dp[k][j] = INT_MAX;
			for ( int i=0; i < 26; ++i ){
				if ( cost[k][i][j] < INT_MAX ){
					for ( int l=0; l < 26; ++l ){
						if ( dp[k-1][l] < INT_MAX ){
							dp[k][j] = min( dp[k][j], dp[k-1][l] + cost[k][i][j] - (i == l) );
						}
					}
				}
			}
		}
	}
	printf("%d\n", *min_element( dp[M-1], dp[M-1] + 26 ));
}


int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
