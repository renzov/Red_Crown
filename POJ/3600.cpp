#include<cstdio>
using namespace std;
const int MAXN = 32;

int A[MAXN];
int B[MAXN];
int Z[MAXN];
int N, M;
int R, C;

int get_num( const int &n ){
	int res = 0;
	char c;
	for ( int i=0; i < n; ++i ){
		scanf(" %c", &c);
		res <<= 1;
		if ( c == '1' )
			res |= 1;
	}
	return res;
}

int num_bits( int x ){
	int res = 0;
	for ( int i=0; i < C; ++i ){
		if (x&1) res++;
		x >>= 1;
	}
	return res;
}

void get_submatrix( const int &mask ){
	int pos;
	for ( int i=0; i < R; ++i ){
		Z[i] = 0; pos = 0;
		for ( int j=0; j < C; ++j ){
			if ( (mask >> j) & 1 ){ 
				if ( (B[i] >> j)&1 )
					Z[i] |= ( 1 << pos );
				pos++;
			}
		}
	}
}

bool is_subseq(){
	int cnt = 0;
	for ( int i=0; i < R && cnt < N; ++i )
		if ( A[cnt] == Z[i] )
			cnt++;
	return cnt == N;
}

int main(){
	scanf("%d %d", &N, &M);
	// Read first matrix -- A
	for ( int i=0; i < N; ++i ) A[i] = get_num(M);
	// Read second matrix  -- B
	scanf("%d %d", &R, &C);
	for ( int i=0; i < R; ++i ) B[i] = get_num(C);

	bool ok = false;
	for ( int i=1; i < (1 << C) && !ok; ++i ){
		// Test if a subset of the columns of B has the same number as the columns of A
		if ( num_bits( i ) == M ){
			get_submatrix( i );
			if ( is_subseq() ) ok = true;
		}
	}
	puts( (ok)? "Yes":"No" );
	return 0;
}
