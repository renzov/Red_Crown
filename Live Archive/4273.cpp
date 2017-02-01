#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 10005;

long long P[MAXN];
int C[MAXN];
int L[MAXN];
int R[MAXN];
int S[MAXN];

long long segL[4*MAXN];
long long segR[4*MAXN];
long long dp[2][MAXN];

void build( int node , int L, int R ){
	segL[node] = segR[node] = LLONG_MAX; 
	if ( L < R ){
		build( node << 1, L , (L+R) >> 1 );
		build( (node << 1)|1, ((L+R) >> 1)+1, R );
	}
}

int main(){
	int N,M;
	int r, w;
	long long W;
	long long X,Y;
	while ( scanf("%d", &N) && N >= 2 ){
		scanf("%d", &M);
		P[1] = 0;
		for ( int i=2; i <= N; ++i ) scanf("%d", P+i);
		for ( int i=1; i <= N; ++i ) scanf("%d", C+i);
		for ( int i=1; i <= N; ++i ){
			scanf("%d", &r);
			L[i] = lower_bound( P + 1, P + N + 1, P[i] - r ) - P;
			R[i] = lower_bound( P + 1, P + N + 1, P[i] + r ) - P;
			if ( R[i] > N || P[R[i]] > (P[i] + r) ) R[i]--;
		}
		L[0] = R[0] = 0;
		S[0] = 0;
		for ( int i=1; i <= N; ++i ){
			scanf("%d", &w);
			S[i] = S[i-1] + w;
		}
		// init dp[j][i] = 0 (j = 1)
		for ( int i=1; i <= N; ++i ) dp[0][i] = S[N] - S[R[i]] + C[i];
		dp[1][1] = dp[0][1];
		bool last = false;
		for ( int j=2; j <= M; ++j ){
			// init segtree
			build( 1, 1, N );
			update1( 1, 1, N, R[1] , dp[last][1] );
			update2( 1 , 1 , N , R[1], dp[last][1] );
			for ( int i=2; i <= N; ++i ){
				Y = query1( 1 , 1, N , L[i] , N );
				X = query2( 1 , 1, N , 1 , L[i]-1 );
				best = LLONG_MAX;
				if ( best > Y ) best = Y;
				if ( best > X && X < LLONG_MAX ) best = X - (S[R[i]]-S[L[i]]);
				dp[!last][i] = min( best , dp[last][i] );
				update1( 1, 1, N, R[i], dp[last][i] );
				update2( 1 , 1, N, R[i], dp[last][i] + S[N] - S[R[i]] );
			}
			last = !last;
		}
	}
	res = S[N];
	for ( int i=1; i <= N; ++i ){
		res = min( res , dp[last][i] + S[N] - S[R[i]] );
	}
	printf("%lld\n", res);
	return 0;
}
