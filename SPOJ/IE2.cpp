#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 32;
const int MOD = 1000000009;
long long G[MAXN][MAXN] = {0};
int N;

long long sum( long long mat[MAXN][MAXN] ){
	long long res = 0;
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			res += mat[i][j];
			res %= MOD;
		}
	return res;
}

void copy_mat( long long O[MAXN][MAXN], long long C[MAXN][MAXN] ){
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			C[i][j] = O[i][j];
}

void clear_rowcol( long long mat[MAXN][MAXN], const int &i ){
	for ( int j=0; j < N; ++j ){
		mat[i][j] = 0;
		mat[j][i] = 0;
	}
}

void undo_rowcol( long long mat[MAXN][MAXN], const int &i ){
	for ( int j=0; j < N; ++j ){
		mat[i][j] = G[i][j];
		mat[j][i] = G[j][i];
	}
}

void mat_mul( long long A[MAXN][MAXN], long long B[MAXN][MAXN], long long C[MAXN][MAXN] ){
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < N; ++j ){
			C[i][j] = 0;
			for ( int k = 0; k < N; ++k ){
				C[i][j] += A[i][k]*B[k][j];
				C[i][j] %= MOD;
			}
		}
}

void fast_mul( long long mat[MAXN][MAXN], long long R[MAXN][MAXN], const int &x ){
	if ( x <= 1 ){
		copy_mat( mat, R );
		return;
	}
	long long temp[MAXN][MAXN];
	if ( x & 1 ){
		fast_mul( mat, temp, x - 1 );
		mat_mul( temp, mat, R );
	}
	else {
		fast_mul( mat, temp, x >> 1 );
		mat_mul( temp, temp, R );
	}
}

int main(){
	int M, K, D;
	int u, v;

	scanf("%d %d %d %d", &N, &M, &K, &D);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u][v]++;
		G[v][u]++;
	}

	if ( D == 1 ){
		if ( K == 1 ) puts("1");
		else puts("0");
		return 0;
	}


	long long T[MAXN][MAXN];
	long long R[MAXN][MAXN];
	copy_mat( G, T );
	
	fast_mul( T, R, D - 1 );
	int res = sum( R );
	int cnt;
	for ( M=1; M < (1 << K); ++M ){
		// set to zero
		cnt = 0;
		for ( int i=0; i < K; ++i ){
			if ( (M >> i)&1 ){
				clear_rowcol( T, i );
				cnt ^=1;
			}
		}
		fast_mul( T, R, D - 1 );
		if ( cnt ){
			res -= sum( R );
			res += MOD;
			res %= MOD;
		}
		else {
			res += sum( R );
			res %= MOD;
		}
		// Undo the changes
		for ( int i=0; i < K; ++i )
			if ( (M >> i)&1 ) undo_rowcol( T, i );
	}
	printf("%d\n", res);
	return 0;
}
