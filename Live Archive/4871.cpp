#include<cstdio>
using namespace std;
const int MAXN = 1024;
const int MOD = 1000000;
int S[MAXN][MAXN];
int dp[MAXN][MAXN];
/*
	dp[i][j] = # number of (1,2,3)-avoiding permutations 
	in which we have i elements less than the minimum element chosen so far 
	and j elements that are greater than that minimum

	- S[i][j] is used to speedup the recurrence
	- Turns out that given N, the number of (1,2,3)-avoiding permutations of 
	  N elements is the N-th Catalan number 
*/

int main(){
	// Precalculate all the answers
	S[0][0] = 1;
	dp[0][0] = 1;
	int j;
	for ( int k=1; k <= 1000; ++k ){
		S[0][k] = dp[0][k] = 1;
		for ( int i=1; i < k; ++i ){
			j = k - i;
			dp[i][j] = S[i][j - 1];
			S[i][j] = (S[i - 1][j  + 1] + dp[i][j]) % MOD;
		}
		dp[k][0] = S[k - 1][0];
		S[k][0] = ( dp[k][0] + S[k - 1][1] ) % MOD;
	}
	int N;
	while ( scanf("%d", &N) && N ) printf("%d\n", dp[N][0]);
	return 0;
}
