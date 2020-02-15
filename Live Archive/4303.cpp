/*	AC in UVa - WA in Live Archive	*/
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1024;
int A[MAXN];
int ans[MAXN];
int mod;

void print( int a[], const int &N ){
	for ( int i=0; i < N; ++i ){
		if ( i ) putchar(' ');		
		printf("%d", a[i]);
	}
	puts("");
}

struct circMatrix {
	int row[MAXN];
	int col[MAXN];
	int size;
	circMatrix(){}
	void build(const int&, const int &,const int &);
	void copy(circMatrix &);
} base;

void circMatrix::build( const int &N, const int &L, const int &R ){
	fill( row, row + N, 0 );
	fill( col, col + N, 0 );
	row[0] = 1, row[1] = R, row[N - 1] = L;
	col[0] = 1, col[1] = L, col[N - 1] = R;
	size = N;
}

void circMatrix::copy( circMatrix &C ){
	size = C.size;
	for ( int i=0;  i < size; ++i )
		row[i] = C.row[i], col[i] = C.col[i];
}

int dot( int B[], const int &i, int C[], const int &j, const int &n ){
	long long ans = 0;
	for ( int k=0; k < n; ++k ){
		ans += (1LL * B[ ( i + k ) % n ] * C[ (j + k) % n ]);	// multiplication may cause overflow of integer
		ans %= mod;
	}
	return (int)ans;	// we now the answer fits in int data type
}

void multiply( circMatrix &B, circMatrix &C, circMatrix &R ){
	int n = B.size;
	R.size = n;
	// Calculate the values of the first row
	for ( int i=0, j=0; i < n; ++i ){
		R.row[i] = dot( B.row, 0, C.col, j, n );
		j = (j - 1 + n)%n;
	}
	// Calculate the values of the first column
	for( int i=0, j=0; i < n; ++i ){
		R.col[i] = dot( B.row, j, C.col, 0, n );
		j = (j - 1 + n)%n;	
	}
}

void fast_exp( circMatrix &M, const int &n, circMatrix &res ){
	if ( n == 1 ){
		res.copy(base);
		return;
	}
	circMatrix tmp;	
	if ( n & 1 ){
		fast_exp( M, n - 1, tmp );
		multiply( tmp, base, res );
	}
	else {
		fast_exp( M, n >> 1, tmp );
		multiply( tmp, tmp, res );
	}
}

void process(){
	int N, S, L, R, X;
	scanf("%d %d %d %d %d", &N, &S, &L, &R, &X);
	// Set the mod
	mod = 1;
	while ( X-- ) mod *= 10;
	// Read the values
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);
		A[i] %= mod;
	}
	// Fast exponentiation 	
	if ( S == 0 ){
		print(A, N);
	}
	else {
		circMatrix M;
		circMatrix res;
		M.build( N, L, R );
		base.copy(M);
		fast_exp( M, S, res );
		for ( int i=0, j=0; i < N; ++i ){
			ans[i] = dot( res.row, j, A, 0, N );
			j = ( j - 1 + N )%N; 
		}
		print( ans, N );
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
