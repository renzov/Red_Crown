#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char S[1024];
bool ispalin[1024][1024]; // ispalin[i][j] = 1 iff S[i..j] is palindrome
int dp[1024];		// dp[i] = minimum-size partition of S[i..N-1]

void process(){
	int N;
	int j;
	scanf("%s", S);
	N = strlen(S);
	// Initialize array
	for ( int i=0; i < N; ++i )
		for ( j=0; j < N; ++j )
			ispalin[i][j] = true;
	// Precalc for each substring if its palindrome
	for ( int i=0; i < N; ++i ) ispalin[i][i] = true;
	for ( int len = 2; len <= N; ++len ){
		for ( int i=0; (i + len) <= N; ++i ){
			j = i + len - 1;
			ispalin[i][j] = (S[i] == S[j]) && ispalin[i + 1][j - 1];
		}
	}
	// Find the minimum-size partition
	dp[N] = 0;
	for ( int i=N-1; i >= 0; --i ){
		dp[i] = N;
		for ( int j=i; j < N; ++j )
			if ( ispalin[i][j] )
				dp[i] = min( dp[i], dp[j + 1] + 1 );
	}
	printf("%d\n", dp[0]); 
}

int main(){
	int runs;
	scanf("%d", &runs);
	while (runs--)
		process();
	return 0;
}
