#include<cstdio>
using namespace std;

const long long MOD = 1000000LL;
long long N, K, L;

void mat_mul( long long A[2][2], long long B[2][2], long long C[2][2] ){
	for ( int i = 0; i < 2; ++i )
		for ( int j = 0; j < 2; ++j ){
			C[i][j] = 0LL;
			for ( int k = 0; k < 2; ++k ){
				C[i][j] += (( A[i][k] * B[k][j] ) % MOD );
				C[i][j] %= MOD;
			}
		}
}

void fast_mul( long long M[2][2], const long long &n, long long R[2][2] ){
	long long T[2][2];

	if ( n == 0 ){
		R[0][0] = 1, R[0][1] = 0, R[1][0] = 0, R[1][1] = 1;	
	}
	else if ( n == 1 ){
		R[0][0] = M[0][0], R[0][1] = M[0][1], R[1][0] = M[1][0], R[1][1] = M[1][1];
	}
	else if ( n & 1 ){
		fast_mul( M, n - 1, T );
		mat_mul( M, T, R );
	}
	else {
		fast_mul( M, n >> 1, T );
		mat_mul( T, T, R );
	}
}

void process(){
	// N is multiple of 5
	N /= 5;
	K %= MOD;
	L %= MOD;

	long long mat[2][2];
	long long res[2][2];

	mat[0][0] = K, mat[0][1] = L;
	mat[1][0] = 1, mat[1][1] = 0;

	fast_mul( mat, N - 1, res );

	printf("%06lld\n", ( ((res[0][0] * K) % MOD) + res[0][1] ) % MOD  );
}

int main(){
	while ( scanf("%lld %lld %lld", &N, &K, &L) == 3 )
		process();
	return 0;
}
