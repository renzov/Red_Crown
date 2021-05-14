#include<cstdio>
#include<algorithm>
using namespace std;
const int MOD = 1000007;
const int MAXN = 505;

long long C[MAXN][MAXN];

long long binom( const int &n, const int &k ){
	if ( n < k ) return 0;
	if ( k == 0 || n == k ) return 1;
	if ( C[n][k] >= 0 ) return C[n][k];
	return C[n][k] = ( binom( n - 1, k - 1 ) + binom( n - 1, k ) ) % MOD;
}

long long find_border( const int &N, const int &M, const int &K ){
	int T = 2*N + 2*M - 4;
	long long res = 0;
	int diff;
	for ( int m = 0; m < 16; ++m ){
		int cnt = 0;
		int sum = 0;
		int bits = 0;
		for ( int i=0; i < 4; ++i ){
			if ( (m >> i)&1 ){
				cnt++;
				sum += ( i & 1 )? N:M;
				bits += i;
			}
		}
		if ( cnt <= 1 ) diff = 0;
		else if ( cnt == 3 ) diff = 2;
		else if ( cnt == 4 ) diff = 4;
		else diff = (bits & 1)? 1:0;

		if ( cnt & 1 ){
			res -= binom( T - sum + diff, K );
			res += MOD;
			res %= MOD;
		}
		else {
			res += binom( T - sum + diff, K );
			res %= MOD;
		}
	}
	return res;
}

long long solve(){
	int N, M, K;
	int T, B;

	scanf("%d %d %d", &N, &M, &K);
	T = N * M;
	if ( K > T ) return 0;
	B = 2*N + 2*M - 4;

	long long res = 0;
	long long X, Y;
	for ( int n = 2; n <= min( K, B ); ++n ){
		X = find_border( N, M, n );
		Y = binom( T - B, K - n );
		res += ( X * Y );
		res %= MOD;
	}
	return res;
}

int main(){
	int runs;
	
	for ( int i=0; i < MAXN; ++i )
		for ( int j=0; j < MAXN; ++j )
			C[i][j] = -1;

	scanf("%d", &runs);
	for ( int i=1; i <= runs; ++i )
		printf("Case %d: %lld\n", i, solve() );
		

	return 0;
}
