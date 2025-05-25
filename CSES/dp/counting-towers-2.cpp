#include<cstdio>
using namespace std;

const int MOD = 1000000007;
long long mat[8][8] = { {0, 1, 0, 1, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 0, 0, 0, 1}, {0, 1, 0, 1, 1, 1, 1, 1}, 
{0, 1, 0, 1, 1, 1, 1, 1}, {0, 1, 0, 1, 1, 1, 1, 1}, {0, 1, 0, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0} };

void mat_mul( long long A[8][8], long long B[8][8], long long C[8][8] ){
	
	for ( int i = 0; i < 8; ++i )
		for ( int j = 0; j < 8; ++j ){
			C[i][j] = 0;
			for ( int k = 0; k < 8; ++k ){
				C[i][j] += ( A[i][k] * B[k][j] );
				C[i][j] %= MOD;
			}
		}
}

void fast_exp( long long A[8][8], const int &n, long long R[8][8] ){
	if ( n == 0 ){
		for ( int i = 0; i < 8; ++i )
			for ( int j = 0; j < 8; ++j )
				R[i][j] = i == j;
	}
	else if ( n == 1 ){
		for ( int i = 0; i < 8; ++i )
			for ( int j = 0; j < 8; ++j )
				R[i][j] = A[i][j];
	}
	else {
		long long T[8][8];
		if ( n & 1 ){
			fast_exp( A, n - 1, T );
			mat_mul( T, A, R );
		}
		else {
			fast_exp( A, n >> 1, T );
			mat_mul( T, T, R );
		}
	}
}

long long solve( const int &N ){
	long long R[8][8];
	fast_exp( mat, N + 1, R );
	return R[0][7];
}

int main(){
	int N, T;
	
	scanf("%d", &T);
	while ( T-- ){
		scanf("%d", &N);
		printf("%lld\n", solve(N) );
	}
	return 0;
}
