#include<cstdio>
using namespace std;
const int MOD = 1000000007;

long long M[2][2] = { {1, 1000000006}, {1, 0} };
long long f[2];

void mat_mul( long long A[2][2], long long B[2][2], long long C[2][2] ){
	for ( int i=0; i < 2; ++i )
		for ( int j=0; j < 2; ++j ){
			C[i][j] = 0;
			for ( int k=0; k < 2; ++k ){
				C[i][j] += ( A[i][k] * B[k][j] );
				C[i][j] %= MOD;
			}
		}
}

void fast_pow( long long A[2][2], const int &N, long long R[2][2] ){
	if ( N == 0 ){
		R[1][1] = R[0][0] = 1;
		R[0][1] = R[1][0] = 0;
		return;
	}
	if ( N == 1 ){
		for ( int i=0; i < 2; ++i )
			for ( int j=0; j < 2; ++j )
				R[i][j] = A[i][j];
		return;
	}

	long long T[2][2];

	if ( N & 1 ){
		fast_pow( A, N - 1, T );
		mat_mul( T, A, R );
	}
	else {
		fast_pow( A, N >> 1, T );
		mat_mul( T, T, R );
	}
}

void process(){
	int N;
	long long mat[2][2];
	long long res; 

	scanf("%lld %lld %d", f, f + 1, &N);
	N--;

	while ( f[0] < 0 )
		f[0] += MOD;

	while ( f[1] < 0 )
		f[1] += MOD;

	if ( N < 2 ) printf("%lld\n", f[N]);
	else {
		fast_pow( M, N - 1, mat );
		res = ( mat[0][0] * f[1] ) % MOD;
		res += ( mat[0][1] * f[0] ) % MOD;
		res %= MOD;
		printf("%lld\n", res );
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
