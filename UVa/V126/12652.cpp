#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 350;

int N, M;
bool ok;
int R[MAXN], C[MAXN];
bool visited[MAXN];

void set_val( int V[], const int &idx, const int &val ){
	if ( V[idx] == -1 ) V[idx] = val;
	else if ( V[idx] != val ) ok = false;
}

int min_swaps( int P[], const int &n ){
	fill( visited, visited + n, false );
	int ncycles = 0;	// # of cycles in the permutation

	for ( int i = 0; i < n; ++i ){
		if ( !visited[i] ){
			ncycles++;
			int idx = i;
			while ( !visited[idx] ){
				visited[idx] = true;
				idx = P[idx];
			}
		}
	}
	return n - ncycles;
}

void process(){
	// Init
	fill( R, R + N, -1 );
	fill( C, C + M, -1 );
	ok = true;
	// Read the input
	int X, r, c;
	for ( int i = 0; i < N; ++i ){
		for ( int j = 0; j < M; ++j ){
			scanf("%d", &X);
			X--;
			r = X / M;
			c = X % M;
			set_val( R, i, r );
			set_val( C, j, c );
		}
	}
	if ( !ok ) puts("*");
	else printf("%d\n", min_swaps( R, N ) + min_swaps( C, M ) );
}

int main(){

	while ( scanf("%d %d", &N, &M) == 2 )
		process();
	return 0;
}
