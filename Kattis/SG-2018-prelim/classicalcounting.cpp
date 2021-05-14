#include<cstdio>
using namespace std;
const int MAXN = 100005;

long long fact[40000];
long long inv[40000];

void preprocess( const int &MOD ){
	fact[0] = 1;
	for ( int i=1; i < MOD; ++i ){
		fact[i] = (fact[i - 1] * (long long)i) % MOD;
	}

	inv[1] = 1;
	for ( int i = 2; i < MOD; ++i ){
	    inv[i] = ( (MOD - MOD/i) * inv[MOD % i] ) % MOD;
	}
}

long long binom( const int &N, const int &K, const int &MOD ){
	if ( K < 0 || N < K ) return 0LL;
	if ( K == 0 || K == N ) return 1LL;
	if ( N >= MOD ){
		return ( binom( N/MOD, K/MOD, MOD ) * binom( N % MOD, K % MOD, MOD ) ) % MOD;
	}
	long long res = ( fact[N] * inv[ fact[N - K] ] ) % MOD;
	res = ( res * inv[ fact[K] ] ) % MOD;
	return res;
}

long long solve( const int &N, const int &M, const int &K, const int &MOD ){	
	long long res = 0;
	long long prod;
	
	preprocess( MOD );
	int bound = (N + K - 1) / (M + 1);
	for ( int i=0; i <= bound; ++i ){
		prod = binom( N , i, MOD ) * binom( N + K - 1 - (M + 1)*i , N - 1, MOD );
		prod %= MOD;
		if ( i & 1 )
			res = ( res - prod + MOD ) % MOD;
		else
			res = ( res + prod ) % MOD;
	}
	return res;
}

long long gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1LL;
        y = 0LL;
        return a;
    }
    long long x1, y1;
    long long d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int main(){
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	// 10^6 + 7 = 29 x 34483 -- we use CRT
	long long A1 = solve( N, M, K, 29 );
	long long A2 = solve( N, M, K, 34483 );
	long long M1, M2;
	int m = 1000007;
	
	gcd( 29 , 34483, M1, M2 );
	
	// Important!
	while ( M1 < 0 ) M1 += m;
	while ( M2 < 0 ) M2 += m; 
		
	long long X = (A1 * M2 * 34483LL) % m; 
	X += (A2 * M1 * 29LL) % m;
	X %= m;
	printf("%lld\n", X);
	return 0;
}
