#include<cstdio>
using namespace std;
const int MAXN = 32;

int M, N;
int mat[MAXN][MAXN];

void mat_mul( int A[MAXN][MAXN], int B[MAXN][MAXN], int C[MAXN][MAXN] ){
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			C[i][j] = 0;
			for ( int k=0; k < N; ++k ){
				C[i][j] += A[i][k] * B[k][j];
				C[i][j] %= M;
			}
		}
}

void solve( int k, int R[MAXN][MAXN], int A[MAXN][MAXN] ){
	if ( k == 1 ){
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				R[i][j] = A[i][j] = mat[i][j];
		return;
	}
	int m[MAXN][MAXN];
	int S[MAXN][MAXN];
	if ( k & 1 ){
		solve( k - 1, R, m );
		mat_mul( m, mat, A );		
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j ){
				R[i][j] += A[i][j];
				R[i][j] %= M;
			}
	}
	else {
		solve( k >> 1, S, m );
		mat_mul( m, m, A );
		for ( int i=0; i < N; ++i ){
			m[i][i]++;
			m[i][i] %= M;
		}
		mat_mul(S, m, R);
	}
}

int main(){
	int K;
	scanf("%d %d %d", &N, &K, &M);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			scanf("%d", mat[i] + j);
			mat[i][j] %= M;
		}

	int res[MAXN][MAXN];
	int A[MAXN][MAXN];
	solve( K , res , A );
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < N; ++j ){
			if (j) putchar(' ');
			printf("%d", res[i][j]);
		}
		puts("");
	}
	return 0;
}
