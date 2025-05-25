#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 9;

int N;
int M;
int X[MAXN * MAXN];
int Y[MAXN * MAXN];
int T[MAXN][MAXN];

int S[MAXN][MAXN];
bool B[3][3][MAXN];
bool R[MAXN][MAXN];
bool C[MAXN][MAXN];
bool ok;

void init(){
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < N; ++j )
			for ( int k = 0; k < N*N; ++k )
				B[i][j][k] = false;

	for ( int i = 0; i < N*N; ++i )
		for ( int j = 0; j < N*N; ++j )
			R[i][j] = C[i][j] = false;
	M = 0;
	ok = true;
}

void print_solution(){
	for ( int i = 0; i < N*N; ++i ){
		printf("%d", S[i][0] + 1);
		for ( int j = 1; j < N*N; ++j )
			printf(" %d", S[i][j] + 1);
		puts("");
	}
}

inline void flip( const int &i, const int &j, const int &v ){
	R[i][v] ^= true;
	C[j][v] ^= true;
	B[i/N][j/N][v] ^= true;
}

bool backtrack( const int &idx ){
	if ( idx >= M ) return true;
	
	int i = X[idx];
	int j = Y[idx];
	for ( int v = 0; v < N*N; ++v ){
		if ( R[i][v] || C[j][v] || B[i/N][j/N][v] )
			continue;
		// test value v
		flip(i, j, v);
		if ( backtrack( idx + 1 ) ){
			S[i][j] = v;
			return true;
		}
		flip(i, j, v);
		S[i][j] = -1; 
	}
	return false;
}

void process(){
	int v;
	
	init();
	for ( int i = 0; i < N*N; ++i )
		for ( int j = 0; j < N*N; ++j ){
			scanf("%d", &S[i][j]);
			v = --S[i][j];
			if ( v >= 0 ){ 
				if ( R[i][v] ) ok = false;
				R[i][ v ] = true;
				if ( C[j][v] ) ok = false;
				C[j][ v ] = true;
				if ( B[ i/N ][ j/N ][ v ] ) ok = false;
				B[i / N][j / N][ v ] = true;
			}
			else {
				X[M] = i, Y[M] = j;
				M++;
			}
		}
	ok = backtrack( 0 );
	if ( ok )
		print_solution();
	else 
		puts("NO SOLUTION");
}

int main(){
	int runs = 0;
	while ( scanf("%d", &N) == 1 ){
		if ( runs++ ) puts("");
		process();
	}
	return 0;
}
