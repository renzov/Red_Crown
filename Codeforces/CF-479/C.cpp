#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 200005;
int A[MAXN];

int main(){

	int N, K;

	scanf("%d %d", &N, &K);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	
	sort( A, A + N );
	if ( K == 0 ){
		if ( A[0] > 1 )
			printf("%d\n", A[0] - 1);
		else 
			puts("-1");
	}
	else {
		if ( K == N || A[K] != A[K - 1] ) 
			printf("%d\n", A[K - 1]);
		else 
			puts("-1");
	}
	return 0;
}
