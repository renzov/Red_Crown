#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 128;
int idx[1024];
int A[MAXN], B[MAXN];

int main(){
	int N;
	int M = 0;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);
	}
	reverse( A , A + N);
	
	for ( int i=0; i < N; ++i ){
		if ( idx[ A[i] ] ) continue;
		idx[ A[i] ] = i + 1;
		B[M++] = A[i];
	}

	reverse( B, B + M );
	printf("%d\n", M);
	for ( int i=0; i < M; ++i ){
		if (i) putchar(' ');
		printf("%d", B[i]);
	}
	puts("");
	return 0;
}
