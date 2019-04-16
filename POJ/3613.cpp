#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXT = 1024;
const int MAXN = 256;
int idx[MAXT]; 
int W[MAXN][MAXN] = {0}; // initialize with zero, since lengths are positive, latar zero = infinity
int n;

inline int get_id(const int &x){
	return idx[x] == -1? (idx[x] = n++):idx[x];
}

void relax( int A[MAXN][MAXN], int B[MAXN][MAXN], int C[MAXN][MAXN] ){
	for ( int i=0; i < n; ++i )
		for ( int j=0; j < n; ++j ){
			C[i][j] = INT_MAX;
			for ( int k=0; k < n; ++k ){
				if ( A[i][k] < INT_MAX && B[k][j] < INT_MAX )
					C[i][j] = min( C[i][j] , A[i][k] + B[k][j] );
			}
		}
}

void matrix_expo( int A[MAXN][MAXN], const int &N, int R[MAXN][MAXN] ){
	if ( N == 1 ){
		for (int i=0; i < n; ++i )
			for ( int j=0; j < n; ++j )
				R[i][j] = A[i][j];
		return;
	}

	int T[MAXN][MAXN];
	if ( N & 1 ){
		matrix_expo( A, N - 1, T );
		relax( T, A, R );
	}
	else {
		matrix_expo( A, N >> 1, T );
		relax( T, T, R );
	}
}

int main(){
	int N, M;
	int s, e;
	int w, u, v;
	int R[MAXN][MAXN];

	fill( idx, idx + MAXT, -1 );
	n = 0;

	scanf("%d %d %d %d", &N, &M, &s, &e);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &w, &u, &v);
		u = get_id( u );
		v = get_id( v );
		W[v][u] = W[u][v] = w;
	}
	// set every zero to infinity
	for ( int i=0; i < n; ++i )
		for ( int j=0; j < n; ++j )
			if ( W[i][j] == 0 )	W[i][j] = INT_MAX;
	
	matrix_expo( W, N, R );
	printf("%d\n", R[ idx[s] ][ idx[e] ]);
	return 0;
}
