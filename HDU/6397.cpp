#include<cstdio>
using namespace std;
const long long MOD = 998244353LL;
const int MAXM = 100001;

long long fact[2*MAXM];
long long inv[MAXM];

long long fexp( const long long &x, const long long &e ){
	if ( e == 0 ) return 1LL;
	else if ( e == 1 ) return x;
	if ( e & 1 ) return ( x * fexp( x, e - 1 ) ) % MOD;
	long long y = fexp( x, e >> 1 );
	return ( y * y ) % MOD; 
}

void preprocess(){
	fact[0] = inv[0] = 1LL;
	fact[1] = inv[1] = 1LL;

	for ( long long i=2; i < 2*MAXM; ++i )
		fact[i] = (fact[i - 1] * i) % MOD;

	for ( int i=2; i < MAXM; ++i )
		inv[i] = fexp( fact[i], MOD - 2 );
}

long long C( const long long &X, const long long &Y ){
	long long res = ( fact[X] * inv[Y] ) % MOD;
	res = ( res * inv[X - Y] ) % MOD;
	return res;
}

int main(){
	preprocess();
	
	int runs;
	long long res;
	long long A, B;
	long long N, M, K;
	long long P;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%lld %lld %lld", &N, &M, &K);
		res = C( K + M - 1, M - 1 );
		for ( long long i = 1; i <= M && i*N <= K; ++i ){
			A = C( M, i );
			B = C( K - N*i + M - 1, M - 1 );
			P = (A * B) % MOD;
			if ( i & 1 ) 
				res = (res - P + MOD) % MOD;
			else
				res = ( res + P ) % MOD;
		}
		printf("%lld\n", res);
	}
	return 0;
}
