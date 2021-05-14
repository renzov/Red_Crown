#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> triple;
const int MAXN = 1024;
triple T[MAXN];

int N;
int V[MAXN];
int K[MAXN];
int C[MAXN];
int L[MAXN];
int dp[MAXN][16];

void process(){
	int v, k, c, l;
	
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d", &v, &k, &c, &l);
		T[i] = triple( pii(v, k), pii(c, l) );
	}
	sort( T, T + N );
	for ( int i=0; i < N; ++i ){
		V[i] = T[i].first.first;
		K[i] = T[i].first.second;
		C[i] = T[i].second.first;
		L[i] = T[i].second.second;
	}

	for ( int i=1; i <= 10; ++i )
		dp[N - 1][i] = INT_MAX;
	dp[ N - 1 ][ C[N - 1] ] = K[N - 1] + C[N - 1]*L[N - 1];

	for ( int i=N - 2; i >= 0; --i ){
		for ( int j=1; j <= 10; ++j ){
			if ( dp[i + 1][j] < INT_MAX ){
				dp[i][j] = dp[i + 1][j] + L[i] * j;
			}
			else {
				dp[i][j] = INT_MAX;
			}
		}
		c = C[i];
		for ( int j=c + 1; j <= 10 ; ++j ){
			if ( dp[i + 1][ j ] < INT_MAX ){
				dp[ i ][ c ] = min( dp[i][c] , dp[ i + 1 ][ j ] + K[ i ] + L[i] * c );
			}
		}
	}

	int res = INT_MAX;
	for ( int j=1; j <= 10; ++j )
		res = min( res, dp[0][j] );
	printf("%d\n", res);
}

int main(){
	while ( scanf("%d", &N) && N )
		process();
	return 0;
}
