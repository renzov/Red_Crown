#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double INF = 1e18;	// one WA because of low INF (1e10) ...
const int MAXN = 2505;
const double EPS = 1e-6;

int N, K;
long long S[MAXN];
long long sum[MAXN];
long long sum2[MAXN];
double dp[MAXN];


double cost( const int &l, const int &r ){
	int L = r - l + 1;
	double X = 1.0 * (sum[r] - sum[l - 1]) / L;	// optimal value is given by the mean
	return (sum2[r] - sum2[l - 1]) - 2.0 * ( sum[r] - sum[l - 1] ) * X + L * X * X;
}

int cmp( const double &A, const double &B ){
	if ( fabs( A - B ) < EPS ) return 0;
	return A < B? -1:1;
}

int main(){
	
	scanf("%d %d", &N, &K);
	
	sum[0] = 0LL;
	for ( int i=1; i <= N; ++i ){
		scanf("%lld", S + i );
		sum[i] = sum[i - 1] + S[i];
		sum2[i] = sum2[i - 1] + S[i]*S[i];
	}
	
	// Init dp
	dp[ 0 ] = 0.0;
	for ( int i=1; i <= N; ++i )
		dp[ i ] = INF;
	
	for ( int i = K; i <= N; ++i ){
		for ( int j = i - K; j >= 0; --j ){
			if ( cmp( dp[j], INF ) < 0 )
				dp[i] = min( dp[i], dp[j] + cost( j + 1, i ) );
		}
	}
	printf("%lld\n", (long long) dp[N] );
	return 0;
}
