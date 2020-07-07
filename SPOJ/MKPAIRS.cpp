#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<climits>
using namespace std;
const int MAXN = 1024;
const double EPS = 1e-6;
typedef pair<long long, long long> line;
int N;
long long A[MAXN];
long long B[MAXN];
long long SA[MAXN];
long long SB[MAXN];
long long dp[MAXN][MAXN];

bool cmp( const line &L2, const line &L1, const line &L ){
	double x1 = (double)(L1.second - L.second) / ( L.first - L1.first );
	double x2 = (double)(L1.second - L2.second ) / ( L2.first - L1.first );
	return x1 < x2 || fabs(x1 - x2) < EPS;
}

inline long long eval( const line &L, const long long &x ){
	return L.first * x + L.second;
}

struct ConvexHull {
	deque<line> H;
	long long query( const long long &x ){
		if ( H.empty() ) return 0;
		while ( (int)H.size() > 1 && eval( H[0], x ) <= eval(H[1], x) )
			H.pop_front();
		return eval( H.front(), x );
	}
	void insert( const line &L ){
		if ( !H.empty() && L.first == H.back().first ){
			if  ( H.back().second > L.second ) // Parallel line (not optimal)
				return;
			else
				H.pop_back();	// No more parallel lines
		}
		int size = (int)H.size();
		while ( (int)H.size() > 1 && cmp( H[size - 2], H[size - 1], L ) )
			H.pop_back(), size--;
		H.push_back( L );
	}
	void clear(){
		while ( !H.empty() ) H.pop_back();
	}
};

ConvexHull CHT[MAXN];

int main(){

	scanf("%d", &N);
	for ( int i=1; i <= N; ++i )
		scanf("%lld", A + i);
	for ( int i=1; i <= N; ++i )
		scanf("%lld", B + i);
	// Find partial sums	
	SA[0] = SB[0] = 0;
	for ( int i=1; i <= N; ++i )
		SA[i] = SA[i - 1] + A[i], SB[i] = SB[i - 1] + B[i];
	
	long long bestA;
	long long bestB;
	for ( int j=1; j <= N; ++j ){
		dp[1][j] = A[1]*B[j] - SB[j - 1]*SB[j - 1];
		CHT[j].insert( line( SA[1] , dp[1][j] - SA[1]*SA[1] ) );
	}
	for ( int i=2; i <= N; ++i ){
		dp[i][1] = A[i]*B[1] - SA[i - 1]*SA[i - 1];	
		CHT[0].insert( line( SB[1] , dp[i - 1][1] - SB[1]*SB[1] ) );
		for ( int j=2; j <= N; ++j ){
			dp[i][j] = A[i]*B[j] - SA[i - 1]*SA[i - 1] - SB[j - 1]*SB[j - 1];
			bestB = CHT[0].query( 2*SB[j - 1] ) - SB[j - 1]*SB[j - 1];
			bestA = CHT[j - 1].query( 2*SA[i - 1] ) - SA[i - 1]*SA[i - 1];
			dp[i][j] = max( dp[i][j], max( bestA, bestB ) + A[i]*B[j] );
			CHT[0].insert( line( SB[j], dp[i - 1][j] - SB[j]*SB[j] ) );
		}
		CHT[0].clear();
		for ( int j=1; j <= N; ++j )
			CHT[j].insert( line( SA[i], dp[i][j] - SA[i]*SA[i] ) );
	}
	long long res = LLONG_MIN;
	for ( int i=1; i <= N; ++i ){
		res = max( res, dp[i][N] - (SA[N] - SA[i])*(SA[N] - SA[i]) );
		res = max( res, dp[N][i] - (SB[N] - SB[i])*(SB[N] - SB[i]) );
	}
	printf("%lld\n", res);
	return 0;
}
