#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 16;
const int MAXV = 14000;

int S[MAXN];
int cost[1 << MAXN];
int dp[1 << MAXN];
// For finding primes
int P[MAXV];
bool isP[MAXV];
int M;
int L;

void sieve(){
	M = 0;
	P[M++] = 2;
	for ( int i=3; i <= L; i += 2 ){
		if ( !isP[i] ){ 
			P[M++] = i;
			for ( int j=i*i; j <= L; j += (i << 1) ){
				isP[j] = true;
			}
		}
	}
}

int main(){
	int N;
	scanf("%d", &N);

	L = 0;
	for ( int i=0; i < N; ++i ){
		scanf("%d", S + i );
		L += S[i];
	}

	sieve();

	int sum;

	cost[0] = 0;
	for ( int i=1; i < (1 << N); ++i ){
		sum = 0; 
		for ( int j=0; j < N; ++j ){
			if ( (i >> j) & 1 ) sum += S[j];
		}
		for ( int j=0; j < M && P[j] <= sum; ++j )
			if ( sum % P[j] == 0 ) cost[i]++;
	}

	dp[0] = 0;
	for ( int m=1; m < (1 << N); ++m ){
		for ( int s = m; s ; s = (s - 1)&m )
			dp[m] = max( dp[m], cost[s] + dp[m ^ s] );
	}
	printf("%d\n", dp[(1 << N) - 1]);
	return 0;
}
