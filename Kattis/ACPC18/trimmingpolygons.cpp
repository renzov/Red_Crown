#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<algorithm>
using namespace std;
const int MAXN = 256;
int N;

long long X[2*MAXN];
long long Y[2*MAXN];
long long V[2*MAXN];
long long S[2*MAXN];
long long dp[2*MAXN][2*MAXN];

long long sum( const int &i, const int &j ){
	if ( i > 0 ) return S[j] - S[i - 1];
	else return S[j];
}

inline long long area2( const int &i, const int &j, const int &k ){
	return llabs( (X[j] - X[i])*(Y[k] - Y[i]) - (X[k] - X[i])*(Y[j] - Y[i]) );
}

int main(){

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%lld %lld %lld", X + i, Y + i, V + i);
		X[i + N] = X[i], Y[i + N] = Y[i], V[i + N] = V[i];
	}

	S[0] = V[0];
	for ( int i=1; i < 2*N; ++i )
		S[i] = S[i - 1] + V[i];
	
	// Initialization
	for ( int i=0; i < N; ++i ){
		dp[i][i + 1] = 0;
	}

	long long res = S[N - 1];
	int j;

	for ( int len = 3; len <= N; ++len ){
		for ( int i=0; i < N; ++i ){
			j = i + len - 1;
			
			dp[ i ][ j ] = sum( i + 1, j - 1 );
			for ( int k = i + 1; k < j; ++k ){
				dp[ i ][ j ] = max( dp[ i ][ j ], dp[i][k] + dp[k][j] + area2(i, k, j) );
			}
		}
	}


	long long left;
	for ( int i=0; i < N; ++i )
		for ( int j=i + 1; j < N; ++j ){
			left = S[N - 1] - sum(i, j);
			res = max( res, dp[i][j] + left );
			left = S[N - 1] - sum(j, i + N);			
			res = max( res, dp[j][i + N] + left );
		}
	
	printf("%lld\n", res);
	return 0;
}
