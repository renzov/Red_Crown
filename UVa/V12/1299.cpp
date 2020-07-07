#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXM = 1024;
const int MAXN = 64;
const double INF = 1e16;

int N, M;
int X[MAXN + MAXM];
int Y[MAXN + MAXM];
double W[MAXN][MAXN];

inline int area2( const int &i, const int &j, const int &k ){
	return ( X[j] - X[i] )*( Y[k] - Y[i] ) - ( X[k] - X[i] )*( Y[j] - Y[i] );
}

inline double dist( const int &i, const int &j ){
	return sqrt( 1.0*(X[i] - X[j])*(X[i] - X[j]) + 1.0*(Y[i] - Y[j])*(Y[i] - Y[j]) );
}

void process(){
	for ( int i=0; i < N + M; ++i )
		scanf("%d %d", X + i, Y + i);

	int left;
	int right;
	int val;

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			W[i][j] = INF;

	for ( int i=0; i < N; ++i )
		for ( int j = i + 1; j < N; ++j ){
			left = right = 0;		
			for ( int k=N; k < N + M; ++k ){
				val = area2( i , j , k );
				if ( val > 0 ) left++;
				else if ( val < 0 ) right++;
			}
			if ( left == M ) W[i][j] = dist( i , j );
			if ( right == M ) W[j][i] = dist( i, j );
		}
	
	double res = INF;
	if ( M > 0 ){	// find the shortest paths
		for ( int k=0; k < N; ++k )
			for ( int i=0; i < N; ++i )
				for ( int j=0; j < N; ++j )
					if ( W[i][k] < INF && W[k][j] < INF )
						W[i][j] = min( W[i][j], W[i][k] + W[k][j] );
	}

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			if ( i == j ) continue;
			for ( int k=0; k < N; ++k ){
				if ( i == k || j == k ) continue;
				if ( area2(i , j , k) == 0 ) continue;
				if ( W[i][j] < INF && W[j][k] < INF && W[k][i] < INF )
					res = min( res, W[i][j] + W[j][k] + W[k][i] );
			}
		}
	
	printf("%.2f\n", res);
}

int main(){
	while ( scanf("%d %d", &N, &M) != EOF )
		process();
	return 0;
}
