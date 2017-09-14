#include<cstdio>
using namespace std;
const int MAXN = 1005;
const int MOD = 10000000;
int t[MAXN];
long long dp[20*MAXN][2];
int sum;

inline int get( const int &i ){
	if ( i == 0 ) return 0;
	if ( i > 0 ) return 2*i;
	return -2*i + 1;
}

long long get_val( const int &i, const int &last ){
	if ( i < -sum || i > sum ) return 0LL;
	return dp[ get(i) ][ last ];
}

int main(){
	int runs;
	int N;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		sum = 0;
		
		for ( int i=0; i < N ; ++i ){
			scanf("%d", t + i);
			sum += t[i];		
		}
		// Initialize dp
		// 2 * i is i
		// 2 * i + 1 is -i
		for ( int i=2; i <= 2*sum + 1; ++i )
			dp[i][0] = 0;
		dp[0][0] = 1;
		
		int last = 0;
		int idx;
		for ( int i=0; i < N; ++i ){
			for ( int j = -sum; j <= sum; ++j ){
				idx = get(j);
				dp[idx][1 - last] = (get_val( j - t[i] , last ) + get_val( j + t[i], last )) % MOD;
			}
			last = 1 - last;
		}
		long long res = 0;		
		for ( int i=2; i <= 2*sum + 1; ++i ){
			res += (i >> 1)*dp[i][last];
			res %= MOD;
		}
		printf("%lld\n", res);
	}
	return 0;
}
