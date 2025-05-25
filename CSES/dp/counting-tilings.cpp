#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 11;
const int MOD = 1000000007;

int cnt[1 << MAXN][1 << MAXN];
int dp[2][1 << MAXN];
vector<int> G[1 << MAXN];

inline int bit( const int &x, const int &p ){
	return (x >> p) & 1;
}

void backtrack( const int &p, const int &N, const int &state, const int &nxt ){
	if ( p >= N ){
		cnt[state][nxt]++;
		return;
	}

	if ( !bit( state, p ) ){	// cannot put a tile
		backtrack( p + 1, N, state, nxt );
	}
	else {
		backtrack( p + 1, N, state, nxt ^ ( 1 << p ) ); // put a tile 1 x 2
		if ( p + 1 < N && bit( state, p + 1 ) )	// put a tile 2 x 1
			backtrack( p + 2, N, state, nxt );
	}
}

void gen_transition_matrix(const int &N){
	for ( int mask = 0; mask < (1 << N); ++mask )
		backtrack( 0, N, mask, (1 << N) - 1 );
}

int main(){
	
	int N, M;
	
	scanf("%d %d", &N, &M);
	gen_transition_matrix(N);
	// compress the matrix -- graph is sparse
	for ( int state = 0; state < (1 << N); ++state )
		for ( int nxt = 0; nxt < (1 << N); ++nxt ){
			if ( cnt[state][nxt] )
				G[nxt].push_back( state );
		}

	int act = 1; 
	int prev = 0;
	int state;
	int val, s;

	dp[ prev ][ ( 1 << N ) - 1 ] = 1;
	for ( int j = 0; j < M; ++j ){
		for ( int nxt = 0; nxt < (1 << N); ++nxt ){
			s = 0;
			for ( int i = 0; i < (int)G[nxt].size(); ++i ){
				state = G[nxt][i];
				val = (1LL * cnt[state][nxt] * dp[prev][state]) % MOD;
				s += val;
				s %= MOD;
			}
			dp[act][nxt] = s;
		}
		act ^= 1;
		prev ^= 1;
	}
	printf("%d\n", dp[prev][ (1 << N) - 1 ]);
	return 0;
}
