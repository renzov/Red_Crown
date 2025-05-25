#include<cstdio>
using namespace std;
const int MOD = 1000000007;
int dp[63000];

inline bool div4( const int &x ){
	return !(x & 1) && !(( x >> 1 ) & 1 );
}

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main(){
	int N;

	scanf("%d", &N);
	if ( !div4(N) && !div4(N + 1) ){
		puts("0");
		return 0;
	}
	
	int S = (N * (N + 1)) >> 2;
	dp[1] = dp[0] = 1;
	for ( int i = 2; i <= N; ++i ){
		for ( int j = S - i; j >= 0; --j )
			if ( dp[ j ] ){
				dp[ j + i ] += dp[j];
				dp[ j + i ] %= MOD;
			}
	}
	long long inv2 = binpow(2 , MOD - 2 );
	printf("%lld\n", dp[S] * inv2 % MOD );
	return 0;
}
