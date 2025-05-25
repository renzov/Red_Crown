#include<cstdio>
#include<climits>
#include<vector>
using namespace std;

const int MAXN = 42;

int N, M;
long long NG[MAXN];		// N[u] = neighborhood of vertex u -- as bitset
vector<int> dpL, dpR;
vector<int> bestL, bestR;

inline long long inv( const int &X ){ return ((1LL << N) - 1) ^ X; }

void precalc( const int &b, const int &size, vector<int> &dp, vector<int> &best ){
	int complement, u, Nu, mask2;
	bool ok;

	// First find the subsets that are vertex cover	
	for ( int mask = 0; mask << (1 << size); ++mask ){
		complement = ((1 << size) - 1) ^ mask;
		ok = true;
		for ( u = 0; ok && u < size; ++u ){
			if ( (complement >> u) & 1 ){
				Nu = (int)( (NG[u + b] >> b) & (( 1 << size ) - 1) );	
				if ( Nu & complement ) ok = false;	// if u is adjacent to a vertex in the complement then mask is not VC
			}
		}
		if ( ok ){
			dp[mask] = __builtin_popcount(mask);
			best[mask] = mask;
		}
	}
	
	// Find the smallest VC containing a given set
	for ( int mask = (1 << size) - 1; mask >= 0; --mask ){
		if ( dp[mask] < INT_MAX ) continue;				// in this case mask is a vertex cover
		for ( u = 0; u < size; ++u ){
			if ( !((mask >> u) & 1) ){
				mask2 = mask | ( 1 << u );	
				if ( dp[mask2] < dp[mask] ){
					dp[mask] = dp[mask2];
					best[mask] = best[mask2];
				}
			}
		}
	}
}

int main(){
	int u, v;

	scanf("%d %d", &N, &M);

	for ( int i = 0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		NG[ u ] |= ( 1LL << v );
		NG[ v ] |= ( 1LL << u );
	}

	int n = N >> 1;
	int m = N - n;
	
	dpL = vector<int>( 1 << n, INT_MAX );
	bestL = vector<int>( 1 << n ); 
	dpR = vector<int>( 1 << m, INT_MAX );
	bestR = vector<int>( 1 << m );

	precalc( 0, n, dpL, bestL );
	precalc( n, m, dpR, bestR );

	int maskNeig;
	int ans = INT_MAX;
	int complement;

	long long best = 0;
	// Every subset in the left
	for ( int mask = 0; mask < (1 << n); ++mask ){
		// The complement of the mask inside the left side
		complement = ((1 << n) - 1)	^ mask;
		
		maskNeig = 0;
		for ( int i = 0; i < n; ++i )
			if ( (complement >> i) & 1 )
				maskNeig |= (int)( NG[i] >> n );	// just consider the neighbors in the right side
		
		if ( dpL[mask] + dpR[maskNeig] < ans ){		// when mask is not VC -- this formula gives upper bound
			ans = dpL[mask] + dpR[maskNeig];
			best = (long long)bestL[mask] | ( (long long)bestR[maskNeig] << n );
		}
	}

	// We print the complement of the solution = Max Independent Set
	bool first = true;
	printf("%d\n", N - ans );
	for ( int i = 0; i < N; ++i )
		if ( !((best >> i) & 1) ){
			if (first) first = false;
			else putchar(' ');
			printf("%d", i);
		}
	puts("");
	return 0;
}
