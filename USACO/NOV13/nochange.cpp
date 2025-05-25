#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
const int MAXK = 17;

int C[MAXK]; 
int V[MAXN];

long long sum[1 << MAXK];
long long S[MAXN];
int idx[1 << MAXK];

int main(){
	freopen ("nochange.in", "r", stdin);	
	freopen ("nochange.out", "w", stdout);

	int K, N;
	long long total = 0;	
	
	// Read input
	scanf("%d %d", &K, &N);

	for ( int i=0; i < K; ++i ){
		scanf("%d", C + i );
		total += C[i];
	}

	// Also precalc prefix sum
	S[0] = 0; 
	for ( int i=1; i <= N; ++i ){
		scanf("%d", V + i );
		S[i] = S[i - 1] + V[i];
	}

	// Precalc the sum of each subset of coins
	sum[0] = 0;
	for ( int mask = 1; mask < (1 << K); ++mask ){
		sum[ mask ] = 0;
		for ( int i=0; i < K; ++i )
			if ( (mask >> i) & 1 )
				sum[mask] += C[i];
	}

	idx[ 0 ] = 0;
	for ( int mask = 1; mask < ( 1 << K ); ++mask ){
		// Consider using each available coin as last
		idx[ mask ] = 0;
		for ( int i=0; i < K; ++i ){
			if ( (mask >> i) & 1 ){
				int premask = mask ^ ( 1 << i ); 
				// Search for the prefix of itens we can buy with i-th coin
				int l = idx[ premask ];
				int r = N;
				int m;

				long long base = S[l];				
				
				if ( C[i] >= ( S[N] - S[l] ) ) 
					l = N;

				while ( r - l > 1 ){
					m = ( l + r ) >> 1;
					if ( C[i] >= ( S[m] - base ) )
						l = m;
					else 
						r = m;
				}
				idx[mask] = max( idx[mask], l );
			}
		}
	}
	
	long long res = LLONG_MAX;
	for ( int mask=0; mask < (1 << K); ++mask )
		if ( idx[mask] == N ){
			res = min( res, sum[mask] );
		}
	
	if ( res == LLONG_MAX )
		puts("-1");
	else 
		printf("%lld\n", total - res );
	return 0;
}
