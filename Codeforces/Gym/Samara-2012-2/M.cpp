#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 200005;

int C[MAXN];
int last[MAXN];
int dp[MAXN];

int main(){
	
	int N;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i )
		scanf("%d", C + i);
	
	fill( last, last + MAXN, -1 );
	dp[ N - 1 ] = 0;
	last[ C[N - 1] ] = N - 1;

	for ( int i = N - 2; i >= 0; --i ){
		dp[i] = 1 + dp[i + 1];
		if ( last[ C[i] ] != -1 )
			dp[i] = min( dp[i], dp[ last[ C[i] ] ] + 1 );
		last[ C[i] ] = i;
	}
	printf("%d\n", dp[0]);
	return 0;
}
