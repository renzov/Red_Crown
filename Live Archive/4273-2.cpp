#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 10005;
int N, K;
int P[MAXN];
int A[MAXN];
int B[MAXN];
int W[MAXN];
int SW[MAXN];
int C[MAXN];
long long dp[2][MAXN];

long long segX[4*MAXN];
long long segY[4*MAXN];
long long X[MAXN];
long long Y[MAXN];

inline int left( const int &x ){ return x<<1; }
inline int right( const int &x ){ return (x<<1)|1; }

void build( int node, int L, int R ){
	if ( L == R ){
		segX[node] = X[L], segY[node] = Y[L];
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M+1, R );
	segX[node] = min( segX[left(node)] , segX[right(node)] );
	segY[node] = min( segY[left(node)] , segY[right(node)] );
}

long long query( long long *seg, int node, int L, int R, int l, int r){
	if ( L==l && R==r ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( seg, left(node), L, M, l, r );
	if ( l > M ) return query( seg, right(node), M+1, R, l, r );
	return min( query(seg, left(node), L, M, l, M), query( seg, right(node), M+1, R, M+1, r ) );
}

int main(){
	int a, b, r;
	while ( scanf("%d %d", &N, &K) && N && K ){
		P[1] = 0;
		for ( int i=2; i <= N; ++i ) scanf("%d", P + i);
		for ( int i=1; i <= N; ++i ){
			scanf("%d", C +i);
			scanf("%d", &r);
			a = lower_bound( P + 1 , P + (N + 1), P[i] - r ) - P;
			b = lower_bound( P + 1 , P + (N + 1), P[i] + r ) - P;
			if ( b > N || P[b] > P[i] + r ) b--;
			A[i] = a, B[i] = b;
		}
		// initialize response to the option of pay all penalties
		long long res = 0;
		long long best, x, y;
		SW[0] = 0;
		for ( int i=1; i <= N; ++i ){ 
			scanf("%d", W+i);
			SW[i] = SW[i-1] + W[i];
		}
		res = SW[N];
		int last = 0;
		// find the value for M = 1
		for ( int i=1; i <= N; ++i ){
			dp[i][last] = C[i] + SW[ A[i] - 1 ];
			res = min( res, dp[i][last] + ( SW[N] - SW[ B[i] ] ) );
		}
		// Now we calculate the next row of dp
		for ( int j=2; j <= K; ++j ){
			// create vectors X and Y
			for ( int i=1; i <= N; ++i ) X[i] = Y[i] = LLONG_MAX;
			for ( int i=j-1; i <= N; ++i ){
				b = B[i];
				Y[b] = min( Y[b] , dp[last][i] );
				X[b] = min( X[b] , dp[last][i] + ( SW[N] - SW[b] )  );
			}
			build( 1, 1, N );
			// create the segment trees	
			for ( int i=j; i <= N; ++i ){
				a = A[i], b = B[i];
				x = ( a > 1 )? query(segX, 1, 1, N, 1, a - 1):LLONG_MAX; 
				y = query(segY, 1, 1, N, a, b);
				best = LLONG_MAX;
				if ( x != LLONG_MAX ) best = min( best, x - (SW[N] - SW[a])  );
				best = min( best, y );
				if ( best < LLONG_MAX )
					dp[1-last][i] = best + C[i];
				else 
					dp[1-last][i] = LLONG_MAX;
				res = min( res, res + SW[N] - SW[b] );
			}
		}
		printf("%lld\n", res);
	}

	return 0;
}

