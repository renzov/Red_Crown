#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN = 505;
const double INF = 1e9;
double dp[MAXN][MAXN];

double solve( const int &N, const int &M, double X[], double Y[] ){
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			dp[i][j] = INF;

	dp[N - 1][M - 1] = fabs( X[N - 1] - Y[M - 1] );
	for ( int j=M - 2; j >= N - 1; --j )
		dp[N - 1][j] = min( dp[N - 1][j + 1], fabs( X[N - 1] - Y[j] ) );
	
	for ( int i=N - 2, k = M - 2; i >= 0; --i, k-- ){
		dp[i][k] = fabs( X[i] - Y[k] ) + dp[i + 1][k + 1];
		for ( int j = k - 1; j >= i; --j ){
			dp[i][j] = min( dp[i][j + 1], fabs(X[i] - Y[j]) + dp[i + 1][j + 1] );
		}
	}
	return *min_element( dp[0], dp[0] + M );
}

void process(){
	double A[MAXN];
	double B[MAXN];
	int N, M;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		scanf("%lf", A + i );
	sort( A, A + N );

	for ( int i=0; i < M; ++i )
		scanf("%lf", B + i );
	sort( B, B + M );

	if ( N <= M ) printf("%.1f\n", solve( N, M, A, B ));
	else printf("%.1f\n", solve( M, N, B, A ));
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
