#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
const int MAXK = 105;
const int MOD = 1000000007;
int N, K;
long long A[MAXN];
long long Ai[MAXK];
long long C[MAXK];
long long binom[MAXK][MAXK] = {0};

int main(){
	
	int runs;
	/* Precalculate binomial coefficients */
	binom[0][0] = 1; 	
	for ( int i=1; i < MAXK; ++i )
		binom[i][0] = binom[i][i] = 1;
	
	for ( int i=2; i < MAXK; ++i ){
			for ( int j=1; j < i; ++j )
				binom[i][j] = ( binom[i-1][j-1] + binom[i-1][j] ) % MOD;

	}

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &K);
		for ( int i=0; i < N; ++i )
			scanf("%lld", A + i);
		
		sort( A, A + N );
		
		long long res = 0;
		long long temp;
		C[0] = 1;
		// C[i] = C[0][K-i]
		for ( int i=1; i <= K; ++i )
			C[i] = ( C[i-1]*( -A[0] ) ) % MOD;
		
		for ( int i=1; i < N; ++i ){
			
			Ai[0] = 1;
			for ( int j=1; j <= K; ++j )
				Ai[j] = ( Ai[j - 1] * A[i] ) % MOD;

			for ( int a=0; a <= K; ++a ){
				temp = ( C[a] * binom[K][a] ) % MOD; // binom[K][a] = binom[K][K-a]
				temp = ( temp * Ai[K-a] ) % MOD;
				res = ( res + temp ) % MOD;
				
				if ( a & 1 )
					C[a] = ( C[a] - Ai[a] ) % MOD;
				else 
					C[a] = ( C[a] + Ai[a] ) % MOD;

			}
		}
		res = (2*res) % MOD;
		res = ( res + MOD ) % MOD;
		printf("%lld\n", res);
	}
	return 0;
}
