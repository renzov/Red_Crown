#include<cstdio>
using namespace std;
const int MAXK = 16;
const long long MOD = 1000000000;
int K;

long long b[MAXK];
long long M[MAXK][MAXK];

void mat_mul( long long A[MAXK][MAXK], long long B[MAXK][MAXK], long long C[MAXK][MAXK] ){
	for ( int i=0; i < K; ++i )
		for ( int j=0; j < K; ++j ){
			C[i][j] = 0;
			for ( int k=0; k < K; ++k )
				C[i][j] += (A[i][k] * B[k][j]) % MOD;
				C[i][j] %= MOD;
		}
}

void mat_pow( int n, long long res[MAXK][MAXK] ){
	if ( n == 1 ){
		for ( int i=0; i < K; ++i )
			for ( int j=0; j < K; ++j )
				res[i][j] = M[i][j];
		return;
	}
	long long tmp[MAXK][MAXK];
	if ( n & 1 ){
		mat_pow( n - 1, tmp );
		mat_mul( tmp, M, res );
	}
	else {
		mat_pow( n >> 1, tmp );
		mat_mul( tmp, tmp, res );
	}
}

void process(){
	int N;
	scanf("%d", &K);
	for ( int i=0; i < K; ++i )
		scanf("%d", b + i);
	for ( int i=0; i < K; ++i )
		scanf("%lld", M[0] + i);
	scanf("%d", &N);
	N--;
	if ( N < K ) printf("%lld\n", b[N] );
	else {
		long long T[MAXK][MAXK];
		for ( int i=1;  i < K; ++i ){
			for ( int j=0; j < K; ++j )
				M[i][j] = 0;
			M[i][i-1] = 1;
		}
		mat_pow( N - K + 1, T );
		long long res = 0;
		for ( int i=0; i < K; ++i ){
			res += T[0][i] * b[ K - i - 1 ];
			res %= MOD;
		}
		printf("%lld\n", res);
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
