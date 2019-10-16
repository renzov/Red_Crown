#include<cstdio>
using namespace std;
const int MAXN = 10005;
int A[4][MAXN];
int R[MAXN];

void process(){
	int N;
	long long K;

	scanf("%d %lld", &N, &K);

	for ( int i=0; i < N; ++i ) scanf("%d", &A[0][i]);
	// Special tricky case
	if ( (N & 1) && K >= N ){
		A[0][ N >> 1 ] = 0;
	}
	for ( int i=1; i < 3; ++i ){
		
		for ( int j=0; j < N; ++j ) A[i][j] = A[i-1][j];
		
		for ( int j=0; j < N; ++j )
			A[i][j] = A[i][j] ^ A[i][N - j - 1];
	}

	int q = (int)(( K / N ) % 3);

	int r = (int)( K % N );


	for ( int i=0; i < N; ++i ) R[i] = A[q][i];
	
	for ( int i=0; i < r; ++i )
		R[i] = R[i] ^ R[N - i - 1];
	
	for ( int i=0; i < N; ++i ){
		if ( i ) putchar(' ');
		printf("%d", R[i] );
	}
	puts("");
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
