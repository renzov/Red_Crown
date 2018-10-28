#include<cstdio>
using namespace std;
const int MOD = 10000;
int len[16] = {0, 8, 90, 900, 9000, 90000, 900000, 9000000, 90000000, 900000000}; // Length of subinterval
int len2[16] = {0, 9, 90, 900, 9000, 90000, 900000, 9000000, 90000000, 900000000};
int M[2][2] = { {2, 1}, {0, 2} }; // for matrix exponentiation

int fastpow( const int &E ){
	if ( E == 0 ) return 1;
	if ( E == 1 ) return 2;
	if ( E & 1 ) return (fastpow( E - 1 ) * 2) % MOD;
	int ret = fastpow( E >> 1 );
	return ( ret * ret ) % MOD;
}

void matmult( int A[2][2], int B[2][2], int C[2][2] ){
	for ( int i=0; i < 2; ++i ){
		for ( int j=0; j < 2; ++j ){
			C[i][j] = 0;
			for ( int k=0; k < 2; ++k ){
				C[i][j] += (( A[i][k] * B[k][j] ) % MOD );
				C[i][j] %= MOD;
			}
		}
	}
}

void matpow( const int &E, int T[2][2] ){
	if ( E == 1 ){
		for ( int i=0; i < 2; ++i )
			for ( int j=0; j < 2; ++j )
				T[i][j] = M[i][j];
		return;
	}
	int C[2][2];
	if ( E & 1 ){
		matpow( E - 1 , C );
		matmult( C, M, T );
	}
	else {
		matpow( E >> 1, C );
		matmult( C, C, T );
	}
}

int solve( const int &N ){
	int X = N % MOD;				// Number of X's
	int par = (2*(N - 1)) % MOD; 	// Number of parentheses 
	int expo = 0;
	int j;
	int add;
	int T[2][2];
	// count the number of digits in exponents
	if ( N > 1 ){
		for ( long long i=1, j = 1; i <= N; i*=10, j++ ){
			if ( N >= (i*10) ){
				add = ( len[j] * j ) % MOD;
				expo = ( expo + add ) % MOD;
			}
			else {
				if ( j > 1 )
					add = ( ( (N - i + 1) % MOD ) * j ) % MOD;
				else 
					add = ( ( (N - 1) % MOD ) * j ) % MOD;
				expo = ( expo + add ) % MOD;
			}
		}
	}
	int pot1 = fastpow( N - 1 );
	int pot2 = (pot1 * 2) % MOD;
	int plus = (pot2 + MOD - 1) % MOD;	// Number of +'s
	int subindex = 0; 				// Number of subindices
	for ( long long i=1, j=1; i <= N; i*=10,++j ){
		if ( N >= (i * 10) ){
			add = ( ( ( len2[j] * j ) % MOD ) * pot1 ) % MOD;
			subindex = ( subindex + add ) % MOD;
		}
		else {
			add = ( ( (((N - i + 1) % MOD) * j ) % MOD ) * pot1 ) % MOD;
			subindex = ( subindex + add ) % MOD;
		}
	}
	int A;
	if ( N == 1 ) A = 1;
	else {
		matpow( N - 1, T );
		A = ( T[0][0] + T[0][1] * 2 ) % MOD;
	}
	return  (X + par + expo + plus + subindex + A) % MOD;
}

int main(){
	int N;
	int cases = 0;

	for ( int i=1; i < 10; ++i )
		len[i] %= MOD, len2[i] %= MOD;

	while ( scanf("%d", &N) && N ){
		printf("Case %d: %d\n", ++cases ,solve(N) );
	}
	return 0;
}
