#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 132;
const int MAXM = 12;

int A[MAXN];
int T[MAXN];

void process(const int &M, const int &N){
	char S[16];
	// Read the input
	for ( int i=0; i < N; ++i ){
		scanf("%s", S);
		A[i] = 0;
		for ( int j=0; j < M; ++j ){
			if ( S[j] == '1' ) A[i] |= ( 1 << j );
		}
	}
	
	int res = M;
	for ( int mask = 0; mask < (1 << M); ++mask ){
		for ( int i=0; i < N; ++i ){
		 	T[i] = A[i] & mask;
		}
		sort( T, T + N );
		int len = unique( T, T + N ) - T;
		if ( len == N ){
			res = min( res, __builtin_popcount(mask) );
		}
	}
	printf("%d\n", res);
}

int main(){
	int N, M;
	while ( scanf("%d %d", &M, &N) && N && M )
		process( M, N );
	return 0;
}
