#include<cstdio>
#include<algorithm>
#include<vector>
#include<climits>
#include<cstdlib>
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 128;

vector<pii> P[MAXN * MAXN];
vector<int> dp[MAXN * MAXN];
int N, K;

inline int dist( const pii &A, const pii &B ){
	return abs( A.first - B.first ) + abs( A.second - B.second );
}

void clean(){
	for ( int i=0; i < K; ++i ){
		dp[i].clear();
		P[i].clear();	
	}
}

void process(){
	int H;

	scanf("%d %d", &N, &K);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			scanf("%d", &H);
			H--;
			P[ H ].push_back( pii( i, j ) );
			dp[ H ].push_back( INT_MAX );
		}
	
	for ( int i=0; i < (int)dp[K - 1].size(); ++i )
		dp[K - 1][i] = 0;
	
	for ( int i=K - 2; i >= 0; --i )
		for ( int j=0; j < (int)P[i].size(); ++j )
			for ( int k=0; k < (int)P[i + 1].size(); ++k )
				dp[i][j] = min( dp[i][j], dp[i + 1][k] + dist( P[i][j], P[i + 1][k] ) );
	
	printf("%d\n", *min_element( dp[0].begin(), dp[0].end() ));
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		if ( runs ) clean();
	}
	return 0;
}
