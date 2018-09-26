#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXM = 16;

int flip[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768 };
int M[MAXM] = {0};
int T[MAXM];
int best[MAXM];
int moves[MAXM];
int R, C;

inline int bit( const int &x, const int &p ){
	return (x >> p)&1;
}

void copy_mat( int A[], int B[] ){
	for ( int i=0; i < R; ++i )
		B[i] = A[i];
}

void print_mat( int A[] ){
	for ( int i=0; i < R; ++i ){
		for ( int j=0; j < C; ++j ){
			if ( j ) putchar(' ');
			if ( bit( A[i] , j ) ) putchar('1');
			else putchar('0');
		}
		puts("");
	}
}

int main(){
	char c;

	scanf("%d %d", &R, &C);
	for ( int i=0; i < R; ++i )
		for ( int j=0; j < C; ++j ){
			scanf(" %c", &c);
			if ( c == '1' ) M[i] |= ( 1 << j );
		}
	int numop;
	int res = INT_MAX;
	for ( int mask=0; mask < (1 << C); ++mask ){
		copy_mat( M  , T );
		fill( moves, moves + R, 0 );
		// Apply mask
		numop = 0;
		moves[0] = mask;
		for ( int j=0; j < C; ++j ){
			if ( bit( mask, j ) ){
				T[0] ^= flip[j];
				if ( j > 0 ) T[0] ^= flip[j - 1];
				if ( j + 1 < C ) T[0] ^= flip[ j + 1 ];
				if ( R > 1 ) T[1] ^= flip[j]; 
				numop++;
			}
		}
		// Proceed to simulate
		for ( int i=1; i < R; ++i ){
			for ( int j=0; j < C; ++j ){
				if ( bit( T[i-1] , j ) ){
					T[i] ^= flip[ j ];
					if ( j > 0 ) T[i] ^= flip[j - 1];
					if ( j + 1 < C ) T[i] ^= flip[j + 1];
					if ( i + 1 < R ) T[ i  + 1 ] ^= flip[j];
					moves[i] ^= flip[j];
					numop++;
				}
			}
		}
		// Check if it is a solution
		if ( T[R-1] == 0 ){
			if ( res > numop ){
				res = numop;
				copy_mat( moves, best );
			}
		}
	}
	// Print the solution
	if ( res < INT_MAX )
		print_mat( best );
	else 
		puts("IMPOSSIBLE");
	return 0;
}

