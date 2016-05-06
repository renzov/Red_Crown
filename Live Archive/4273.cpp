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

long long dp[2][MAXN];

int main(){
	int N,M;
	int r, w;
	long long W;
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
		// init dp j = 0
		for ( int i=0; i <= N; ++i ) dp[0][i] = S[i];
		dp[1][0] = 0;
		bool last = false;
		for ( int j=1; j <= M; ++j ){
			for ( int i=1; i <= N; ++i ){
				long long &ref = dp[!last][i];
				ref = dp[last][i];
				for ( int k=0; k < i; ++k ){
					W = dp[last][k] + (R[k] >= L[i])? 0:( S[L[i] - 1] - S[R[k]] );
					if ( (C[i] + W) < ref ) ref = C[i] + W; 
				}
			}
			last = !last;
		}
		long long res = S[N];
		for ( int i=1; i <= N; ++i ){
			W = dp[last][i] + S[N] - S[R[i]];
			if ( W < res ) res = W;
		}
		printf("%lld\n", res);
	}
	return 0;
}
