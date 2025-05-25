#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 5005;
long long A[MAXN];
long long f[2][MAXN];
long long g[2][MAXN];

inline long long add( const long long &a, const long long &b ){
	return ( a == LLONG_MIN || b == LLONG_MIN )? LLONG_MIN:(a + b);
}

int main(){
	int N, K;

	scanf("%d %d", &N, &K);

	for ( int i=0; i < N; ++i )
		scanf("%lld", A + i );

	int prev = 0;
	int act = 1;
	
	// Initialization
	for ( int j = 0; j < K; ++j ){
		g[prev][j] = f[prev][j] = LLONG_MIN;
		f[act][j] = g[act][j] = LLONG_MIN;
	}

	g[prev][0] = f[prev][0] = A[0];
	
	for ( int i = 1; i < N; ++i ){
		// consider j = 0
		g[act][0] = max( A[i], add( g[prev][0] , A[i] ) );
		f[act][0] = max( f[prev][0] , g[act][0] );
		
		for ( int j = 1; j < min(K, i + 1 ); ++j ){
			g[act][j] = max( add( g[prev][j] , A[i] ) , add( f[prev][j - 1] , A[i] ) );
			f[act][j] = max( f[prev][j] , g[act][j] );
		}
		swap( prev, act );
	}

	printf("%lld\n", f[prev][K - 1] );

	return 0;
}
