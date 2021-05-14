#include<cstdio>
#include<algorithm>
using namespace std;
const int MOD = 2004;
const int MAXN = 11;

int N, A, B;
int V[MAXN];
int S[1 << MAXN];
int sgn[1 << MAXN];
int primes[] = {2, 3, 5, 7};
int coef[4];
int E[4];

int C( const int &X ){
	int T;
	int res = 1;
	
	if ( X == 0 ) return res;

	copy( coef, coef + 4, E );
	for ( int i=1; i <= N; ++i ){
		T = X + i;
		for ( int j=0; j < 4; ++j ){
			while ( E[j] > 0 && T % primes[j] == 0 )
				T /= primes[j], E[j]--;
		}
		T %= MOD;
		res *= T;
		res %= MOD;
	}
	return res;
}

int f( const int &X ){
	if ( X < 0 ) return 0;
	if ( X == 0 ) return 1;
	int res = 0;
	for ( int m=0; m < ( 1 << N ); ++m ){
		if ( S[m] <= X ){
			res += sgn[m] * C( X - S[m] );
			res += MOD;
			res %= MOD;
		}
	}
	return res;
}

int main(){

	scanf("%d %d %d", &N, &A, &B);	
	for ( int i=0; i < N; ++i ){
		scanf("%d", V + i);
		V[i]++;
	}
	
	// Precalc the sum of the subsets and sign
	for ( int i=0; i < (1 << N); ++i ){
		sgn[i] = 1;
		for ( int j = 0; j < N; ++j )
			if ( (i >> j)&1 ) S[i] += V[j], sgn[i] *= -1;
		//printf("sgn[%d] = %d --- S[%d] = %d\n", i, sgn[i], i, S[i]);
	}
	// Precalc the factorization of N!
	int T;
	for ( int i=2; i <= N; ++i  ){
		T = i;
		for ( int j=0; j < 4; ++j )
			while ( T % primes[j] == 0 ){
				coef[j]++;
				T /= primes[j];
			}
	}
	printf("%d\n", (f(B) - f(A - 1) + MOD) % MOD );
	return 0;
}
