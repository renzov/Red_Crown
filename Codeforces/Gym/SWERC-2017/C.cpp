#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 9;
const int MOD = 1000000000;

int cnt[1 << MAXN][1 << MAXN];
int N; 

inline int bit( const int &x, const int &p ){
	return (x >> p) & 1;
}

void backtrack( const int &p, const int &state, const int &nxt ){
	if ( p >= N ){
		cnt[state][nxt]++;
		return;
	}

	if ( !bit( state, p ) ){	// cannot put a tile
		backtrack( p + 1, state, nxt );
	}
	else {
		backtrack( p + 1, state, nxt );	// put a tile 1 x 1
		backtrack( p + 1, state, nxt ^ ( 1 << p ) ); // put a tile 1 x 2
		if ( p + 1 < N && bit( state, p + 1 ) )	// put a tile 2 x 1
			backtrack( p + 2, state, nxt );
	}
}

void gen_transition_matrix(){
	for ( int mask = 0; mask < (1 << N); ++mask )
		backtrack( 0, mask, (1 << N) - 1 );
}

void mat_mul( int A[1 << MAXN][1 << MAXN], int B[1 << MAXN][1 << MAXN], int C[1 << MAXN][1 << MAXN] ){
	for ( int i = 0; i < (1 << N); ++i )
		for ( int j = 0; j < (1 << N); ++j ){
			C[i][j] = 0LL;
			for ( int k = 0; k < (1 << N); ++k ){
				int val = 1LL * A[i][k] * B[k][j] % MOD;
				C[i][j] += val;
				C[i][j] %= MOD;
			}
		}
}

void copy_mat( int A[1 << MAXN][1 << MAXN], int B[1 << MAXN][1 << MAXN] ){
	for ( int i = 0; i < (1 << N); ++i )
		for ( int j = 0; j < (1 << N); ++j )
			B[i][j] = A[i][j];
}

void fast_exp( int A[1 << MAXN][1 << MAXN], long long m, int R[1 << MAXN][1 << MAXN] ){
	// Initialize response to identity matrix
	for ( int i = 0; i < (1 << N); ++i )
		for ( int j = 0; j < (1 << N); ++j )
			R[i][j] = (i == j)? 1:0;
	
	int T[1 << MAXN][1 << MAXN];

	while ( m > 0 ){
		if ( m & 1 ){
			copy_mat( R, T );
			mat_mul( T, A, R );
		}
		copy_mat( A, T );
		mat_mul( T, T, A );
		m >>= 1;
	}
}

int main(){
	long long M;
	
	scanf("%d %lld", &N, &M);
	gen_transition_matrix();
	int R[1 << MAXN][1 << MAXN];
	fast_exp( cnt, M, R );
	printf("%d\n", R[(1 << N) - 1][(1 << N) - 1]);
	return 0;
}

