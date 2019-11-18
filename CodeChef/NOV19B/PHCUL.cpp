#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double INF = 1e20;
const int MAXN = 15005;

double X[MAXN];
double Y[MAXN];
double D[3][MAXN];

inline double dist( const int &i, const int &j ){
	return sqrt( (X[i] - X[j])*(X[i] - X[j]) + (Y[i] - Y[j])*(Y[i] - Y[j]) );
}

void process(){
	int N, M, K;
	double d;

	scanf("%lf %lf", &X[0], &Y[0]);

	scanf("%d %d %d", &N, &M, &K);
	for ( int i=1; i <= (N + M + K); ++i )
		scanf("%lf %lf", X + i, Y + i);
	
	// Distance from (x,y) to the points in N and M
	for ( int i=1; i <= (N+M); ++i )
		D[0][i] = dist( 0 , i );
	
	for ( int i=1; i <= (N + M); ++i ) D[1][i] = INF;
	for ( int i=1; i <= K; ++i ) D[2][N + M + i] = INF;

	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= M; ++j ){
			d = dist( i , N + j );
			D[1][j + N] = min( D[1][j + N] , D[0][i] + d );
			D[1][i] = min( D[1][i], D[0][j + N] + d );
		}
	
	for ( int i=1; i <= (N + M); ++i )
		for ( int k=1; k <= K; ++k )
			D[2][N + M + k] = min( D[2][N + M + k], D[1][i] + dist( i, N + M + k ) );
	
	double res = INF;
	for ( int k=1; k <= K; ++k )
		res = min( res, D[2][N + M + k] );

	printf("%.7f\n", res);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
