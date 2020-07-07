#include<cstdio>
#include<cassert>
using namespace std;
const int MAXN = 100005;
const int MOD = 1000000007;
long long pow2[MAXN];
long long fact[2*MAXN];
long long memo[2*MAXN];

long long fastpow( const long long &x, const int &p ){
	if ( p == 0 ) return 1LL;
	if ( p == 1 ) return x % MOD;
	if ( p & 1 ) return ( x * fastpow( x, p - 1 ) ) % MOD;
	long long r = fastpow( x, p >> 1 );
	return (r * r) % MOD;
}

long long inverse( const int &x ){
	if ( memo[x] ) return memo[x];
	return memo[x] = fastpow( fact[x], MOD - 2 );
}

long long comb( const int &n, const int &k ){
	long long res = fact[n];
	res *= inverse( n - k ); res %= MOD;
	res *= inverse( k );	res %= MOD;
	return res;
}

long long f( const int &m, const int &n ){
	long long C;
	long long sum = 0;
	for ( int i=0; i <= n; ++i ){
		C = ( pow2[i] * comb( n, i ) ) % MOD;
		if ( i & 1 ){
			sum = (sum - C + MOD) % MOD;
			assert( sum >= 0 );	
		}
		else {
			sum = (sum + C) % MOD;
		}
	}
	return sum;
}

int main(){
	int N, M, L, K;
	long long tmp;
	scanf("%d %d %d %d", &M, &N, &K, &L);
	// precalc
	fact[0] = 1;
	for ( long long i=1; i <= (M + N); ++i )
		fact[i] = (fact[i - 1] * i) % MOD;
	for ( int i=0; i <= (N - L); ++i ){
		tmp = ( fastpow( 2, N - L - i ) - 1 + MOD ) % MOD;
		pow2[i] = fastpow( tmp, M - K );
	}
	long long res = comb( M, K );
	res *= comb( N, L ); 		res %= MOD;
	res *= f( M - K, N - L );	res %= MOD;
	printf("%lld\n", res);
	return 0;
}
