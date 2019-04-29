#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int A[MAXN];
int L[MAXN];
int R[MAXN];

int main(){

	int N;

	scanf("%d", &N);
	for ( int i=1; i <= N; ++i ) scanf("%d", A + i);
	R[N] = 1;
	for ( int i=N-1; i > 0; --i )
		R[i] = ( A[i] < A[i+1] )? (R[i+1] + 1 ):1;
	L[1] = 1;
	for ( int i=2; i <= N; ++i )
		L[i] = ( A[i-1] < A[i] )? (L[i-1] + 1):1;

	int res = 0;
	for ( int i=1; i <= N; ++i ){
		res = max( res, max( R[i + 1], L[i - 1] ) + 1);
		if ( i > 1 && i < N ){
			if ( A[i + 1] - A[i - 1] > 1 )
				res = max( res, L[i-1] + R[i+1] + 1 );
		}
	}
	printf("%d\n", res);
	return 0;
}
