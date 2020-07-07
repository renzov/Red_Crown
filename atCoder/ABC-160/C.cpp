#include<cstdio>
using namespace std;
const int MAXN = 200005;
int A[MAXN];
int main(){

	int N, K;
	scanf("%d %d", &K, &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	A[N] = A[0] + K;
	int best = 0;
	for ( int i=0; i < N; ++i )
		if ( best < (A[i+1] - A[i]) )
			best = A[i + 1] - A[i];
	printf("%d\n", K - best);

	return 0;
}
