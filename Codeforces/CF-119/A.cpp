#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 4005;
int N, A, B, C;

int dp[MAXN]; 
int main(){

	scanf("%d %d %d %d", &N, &A, &B, &C);
	dp[0] = 1;
	for ( int i=1; i <= N; ++i ){
		if ( i - A >= 0 && dp[i-A] ) dp[i] = max(dp[i], dp[i-A] + 1);
		if ( i - B >= 0 && dp[i-B] ) dp[i] = max(dp[i], dp[i-B] + 1 );
		if ( i - C >= 0 && dp[i-C] ) dp[i] = max(dp[i], dp[i-C] + 1 );
	}  
	printf("%d\n", dp[N] - 1);
	return 0;
}
