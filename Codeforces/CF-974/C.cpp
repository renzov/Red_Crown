#include<cstdio>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 200005;
int A[MAXN];

void process(){
	int N; 
	long long sum = 0;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d", A + i );
		sum += A[i];
	}
	if ( N <= 2 ) puts("-1");
	else {
		sort( A, A + N );
		int idx = N >> 1;
		long long X = 2LL * N * A[idx] - sum;
		X++;
		X = max( X, 0LL );
		printf("%lld\n", X);
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while ( t-- )
		process();
	return 0;
}
