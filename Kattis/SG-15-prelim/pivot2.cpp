#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

int A[MAXN];
int M[MAXN];
int m[MAXN];

int main(){
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ) scanf("%d", A + i);
	M[0] = -INT_MAX;
	for ( int i=1; i < N; ++i ) M[i] = max( M[i-1], A[i-1] );
	m[N-1] = INT_MAX;
	for ( int i=N-2; i >= 0; --i ) m[i] = min( m[i+1], A[i+1] );

	int res = 0;
	for ( int i=0; i < N; ++i )
		if ( M[i] <= A[i] && m[i] > A[i] ) res++;
	printf("%d\n", res);
	return 0;
}
