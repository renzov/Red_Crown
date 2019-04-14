#include<cstdio>
using namespace std;
const int MAXK = 32;
long long MOD;
long long B[MAXK] = {0};
long long S[MAXK] = {0};
long long mat[MAXK][MAXK];
int K;

void matrix_mult( long long X[MAXK][MAXK], long long Y[MAXK][MAXK], long long Z[MAXK][MAXK] ){
	for ( int i=0; i <= K; ++i )
		for ( int j=0; j <= K; ++j ){
			Z[i][j] = 0LL;
			for ( int k=0; k <= K; ++k ){
				Z[i][j] += (X[i][k] * Y[k][j]);
				Z[i][j] %= MOD;
			}
		}
}

void matrix_expo( long long A[MAXK][MAXK], const long long &n, long long C[MAXK][MAXK] ){
	if ( n == 1 ){
		for (int i=0; i <= K; ++i)
			for ( int j=0; j <= K; ++j )
				C[i][j] = A[i][j];
		return;
	}
	long long T[MAXK][MAXK];
	if ( n & 1 ){ // odd
		matrix_expo( A, n - 1, T );
		matrix_mult( A, T, C );
	}
	else {
		matrix_expo( A, n >> 1, T );
		matrix_mult( T, T, C );
	}
}

long long find_sum( const long long &n ){
	if ( n <= K ) return S[n];
	long long res[MAXK][MAXK];
	matrix_expo( mat, n - K, res );
	long long sum = ( B[0]*res[0][0] ) % MOD;
	for ( int i=1; i <= K; ++i ){
		sum += B[K - i + 1]*res[0][i];
		sum %= MOD;
	}
	return sum;
}

void process(){
	long long N, M;

	scanf("%d", &K);
	for ( int i=1; i <= K; ++i ){
		scanf("%lld", B + i );
		S[i] = S[i - 1] + B[i];
	}
	for ( int i=1; i <= K; ++i ){
		scanf("%lld", &mat[0][i] );
		mat[1][i] = mat[0][i];
	}
	// Create the exponentiation matrix
	mat[0][0] = 1;
	B[0] = S[K];	
	for ( int i=2; i <= K; ++i ){
		for ( int j=1; j <= K; ++j )
			mat[i][j] = 0LL;
		mat[i][i - 1] = 1LL;
	}
	scanf("%lld %lld %lld", &M, &N, &MOD);
	printf("%lld\n", (find_sum(N) - find_sum(M - 1) + MOD) % MOD );
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
