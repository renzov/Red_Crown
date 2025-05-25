#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 1000005;
int dp[MAXN]; 

int main(){
	
	int N;
	scanf("%d", &N);
	
	dp[0] = 0;
	for ( int i = 1; i < 10; ++i )
		dp[i] = 1;

	int num, d;
	for ( int i = 10; i <= N; ++i ){
		dp[i] = INT_MAX;
		num = i;
		while ( num != 0 ){
			d = num % 10;
			num /= 10;
			if ( d )
				dp[i] = min( dp[i], dp[i - d] + 1 );
		}
	}
	printf("%d\n", dp[N]);
	return 0;
}

