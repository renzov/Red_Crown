#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 16;

int A[MAXN];
int B[MAXN];
int M;

bool backtrack( int A[], int N ){
	if ( N < M ) return false;
	if ( N == M ){
		bool ok = true;
		for ( int i = 0; i < N && ok; ++i )
			ok &= (A[i] == B[i]);
		if ( ok ) return true;
		ok = true;
		for ( int i = 0; i < N && ok; ++i )
			ok &= (A[N - i - 1] == B[i]);
		return ok;
	}

	int C[16];
	int K;
	// Test each possible position
	for ( int i = 1; i < N; ++i ){
		K = N - min( i, N - i );
		int l, r;
		for ( l = i - 1, r = i; l >= 0 && r < N; l--, r++ )
			C[--K] = A[l] + A[r];
		while ( r < N ) C[--K] = A[r++];
		while ( l >= 0 ) C[--K] = A[l--];
		K = N - min( i, N - i );
		if ( backtrack( C, K ) ) return true;
	}
	return false;
} 

int main(){
	
	int sumA;
	int sumB;
	int N;

	while ( scanf("%d", &N) == 1 ){
		sumA = 0;
		for ( int i = 0; i < N; ++i ){
			scanf("%d", A + i );
			sumA += A[i];
		}
		scanf("%d", &M);
		sumB = 0;
		for ( int i = 0; i < M; ++i ){
			scanf("%d", B + i );
			sumB += B[i];
		}
		if ( sumA != sumB || !backtrack( A, N ) ) puts("N");
		else puts("S");
	}
	return 0;
}
