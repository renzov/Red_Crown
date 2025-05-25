#include<cstdio>
#include<climits>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 1024;

int W[MAXN];
int d[2][MAXN];	// dp[l][i] = max cost of a walk using l arcs from 0 to i
vector<int> G[MAXN];

int main(){
	freopen("time.in", "r", stdin);
	freopen("time.out", "w", stdout);

	int N, M, C;

	scanf("%d %d %d", &N, &M, &C);
	for ( int i = 0; i < N; ++i )
		scanf("%d", W + i );

	int u, v;
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[v].push_back(u);	// storing the reverse graph
	}
	
	int T = *max_element( W, W + N ) / C;
	int ans = 0;
	
	int prev = 0;
	int act = 1;
	int val;

	fill( d[prev], d[prev] + N, INT_MIN );
	d[prev][0] = 0;

	for ( int l = 1; l <= T; ++l ){
		for ( u = 0; u < N; ++u ){
			val = INT_MIN;
			for ( int i = 0; i < (int)G[u].size(); ++i ){
				v = G[u][i];
				if ( d[prev][v] == INT_MIN ) continue;
				val = max( val, d[prev][v] + W[u] );
			}
			d[act][u] = val;
		}
		if ( d[act][0] != INT_MIN )
			ans = max( ans, d[act][0] - C * l * l );
		act ^= 1;
		prev ^= 1;
	}
	printf("%d\n", ans );
	return 0;
}
