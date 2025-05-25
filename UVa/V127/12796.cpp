#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;
const int MOD = 10000;

long long Adj[MAXN][MAXN];
int N;

void mat_mul( long long A[MAXN][MAXN], long long B[MAXN][MAXN], long long C[MAXN][MAXN] ){
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < N; ++j ){
			C[i][j] = 0LL;
			for ( int k = 0; k < N; ++k ){
				C[i][j] += A[i][k] * B[k][j];
				C[i][j] %= MOD;
			}
		}
}

void fast_mat_pow( long long A[MAXN][MAXN], const int &L, long long R[MAXN][MAXN] ){
	if ( L == 1 ){
		for ( int i = 0; i < N; ++i )
			copy( A[i], A[i] + N, R[i] );
	}
	else {
		long long T[MAXN][MAXN];
		if ( L & 1 ){
			fast_mat_pow( A, L - 1, T );
			mat_mul( A, T, R );
		}
		else {
			fast_mat_pow( A, L >> 1, T );
			mat_mul( T, T, R );
		}
	}
}

void process( const int &L ){
	int S, T;
	int v;

	scanf("%d %d", &S, &T);
	S--, T--;
	for ( int i = 0; i < N; ++i ){
		for ( int j = 0; j < 4; ++j ){
			scanf("%d", &v);
			v--;
			Adj[i][v]++;
		}
	}

	if ( L == 0 ){
		puts( S == T? "1":"0" );
	}
	else {
		long long R[MAXN][MAXN];
		fast_mat_pow( Adj, L, R );
		printf("%lld\n", R[S][T] );
	}
}

void clean(){
	for ( int i = 0; i < N; ++i )
		fill( Adj[i], Adj[i] + N, 0LL );
}

int main(){
	int L;
	while ( scanf("%d %d", &N, &L) == 2 ){
		process( L );
		clean();
	}
	return 0;
}
