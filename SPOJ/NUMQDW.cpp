#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXSIZE = (1 << 6) + 2;
const int MOD = 4242;

int M;
int states;
char W[1 << 14];
bool invalid[8][8] = {0};
int mat[MAXSIZE][MAXSIZE] = {0};
int res[MAXSIZE][MAXSIZE];

inline int isset(const int &mask, const int &p){
	return (mask >> p) & 1; 
}

void find_invalid_pairs(){
	int mask = 0;
	int u, v;
	for ( int i=0; W[i]; ++i ){
		v = W[i] - 'A';
		for ( u = 0; u < M; ++u ){
			if ( isset(mask,u) ) invalid[u][v] = true;
		}
		mask |= ( 1 << v );
	}
}

void matrix_mult(int A[MAXSIZE][MAXSIZE], int B[MAXSIZE][MAXSIZE], int C[MAXSIZE][MAXSIZE]){
	for ( int i=0; i < states; ++i )
		for ( int j=0; j < states; ++j ){
			C[i][j] = 0;
			for ( int k=0; k < states; ++k ){
				C[i][j] += (A[i][k] * B[k][j]);
				C[i][j] %= MOD;
			}
		}
}

void fast_pow( int A[MAXSIZE][MAXSIZE], const int &N, int R[MAXSIZE][MAXSIZE] ){
	if ( N == 1 ){
		for ( int i=0; i < states; ++i )
			for ( int j=0; j < states; ++j )
				R[i][j] = A[i][j];
		return;
	} 
	int T[MAXSIZE][MAXSIZE];
	if ( N & 1 ){
		fast_pow( A, N - 1, T );
		matrix_mult( T, A, R );
	}
	else {
		fast_pow( A, N >> 1, T );
		matrix_mult( T, T, R );
	}
}

void process(){
	int N;
	int u, v;
	bool ok;
	int mask;

	scanf("%d %d %s", &N, &M, W);
	states = 1 << M;
	if ( N == 0 ){ // special case - empty word
		puts("1");
		return;
	} 
	find_invalid_pairs();
	// find transition matrix
	for ( u=0; u < states; ++u ){
		for ( int c=0; c < M; ++c ){ // try to add each character
			ok = true;	// test if is valid
			for ( int i=0; i < M && ok; ++i )
				if ( isset(u, i) && invalid[i][c] ) ok = false;
			if ( ok ){
				mask = u | ( 1 << c );
				mat[mask][u]++;
			}
		}
	}
	fast_pow( mat, N, res );
	int sum = 0;
	for ( int i=0; i < states; ++i ){
		sum += res[i][0];
		sum %= MOD;
	}
	printf("%d\n", sum);
	// Clean memory for next testcase
	for ( int i=0; i < M; ++i )
		fill( invalid[i], invalid[i] + M, false );
	
	for ( int i=0; i < states; ++i )
		fill( mat[i], mat[i] + states, 0 );
}

int main(){
	int runs;
	scanf("%d", &runs);
	
	while (runs--){
		process();
	}
	return 0;
}
