#include<cstdio>
#include<climits>
#include<vector>
using namespace std;

const int MAXN = 42;

int N, M;
long long NG[MAXN];		// N[u] = closed neighborhood of vertex u -- as bitset
vector<int> dpL, dpR;
vector<int> bestL, bestR;

inline long long inv( const int &X ){ return ((1LL << N) - 1) ^ X; }

void precalc( const int &b, const int &size, vector<int> &dp, vector<int> &best ){
	// The empty set
	dp[0] = 0; best[0] = 0;
	
	int u, Nu, mask2;
	for ( int mask = 1; mask < (1 << size); ++mask ){
		for ( u = 0; u < size; ++u ){
			if ( (mask >> u) & 1 ){
				// the maximum independet set that does not contain u
				mask2 = mask ^ ( 1 << u );
				dp[mask] = dp[mask2];
				best[mask] = best[mask2];
				// the maximum independet set in MASK that contains u 
				Nu = (int)( (NG[u + b] >> b) & (( 1 << size ) - 1) ); 
				mask2 = mask & ~Nu;
				if ( dp[mask2] >= dp[mask] ){
					dp[mask] = dp[mask2] + 1;
					best[mask] = best[mask2] | ( 1 << u );
				}
				break;
			}
		}
	}
}

int main(){
	int u, v;

	scanf("%d %d", &N, &M);

	for ( int i = 0; i < N; ++i )
		NG[ i ] = 1LL << i;

	for ( int i = 0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		NG[ u ] |= ( 1LL << v );
		NG[ v ] |= ( 1LL << u );
	}

	int n = N >> 1;
	int m = N - n;
	
	dpL = vector<int>( 1 << n, INT_MIN );
	bestL = vector<int>( 1 << n ); 
	dpR = vector<int>( 1 << m, INT_MIN );
	bestR = vector<int>( 1 << m );

	precalc( 0, n, dpL, bestL );
	precalc( n, m, dpR, bestR );

	int maskNeig;
	int ans = 0;
	long long best = 0;
	// Every subset in the left
	for ( int mask = 0; mask < (1 << n); ++mask ){
		maskNeig = 0;
		for ( int i = 0; i < n; ++i )
			if ( (mask >> i) & 1 )
				maskNeig |= (int)( NG[i] >> n );
		maskNeig ^= (( 1 << m ) - 1);		
		if ( dpL[mask] + dpR[maskNeig] > ans ){
			ans = dpL[mask] + dpR[maskNeig];
			best = (long long)bestL[mask] | ( (long long)bestR[maskNeig] << n );
		}
	}

	bool first = true;
	printf("%d\n", ans );
	for ( int i = 0; i < N; ++i )
		if ( (best >> i) & 1 ){
			if (first) first = false;
			else putchar(' ');
			printf("%d", i);
		}
	puts("");
	return 0;
}
