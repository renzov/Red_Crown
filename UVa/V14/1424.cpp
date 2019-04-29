#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 128;
vector<int> G[MAXN];
int P[2*MAXN];
int dp[MAXN][2*MAXN];

void process(){
	int N, M;
	int u, v, c;	
	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	scanf("%d", &M);
	for ( int i=0; i < M; ++i )
		scanf("%d", P + i);

	for ( int i=1; i <= N; ++i )
		dp[i][M-1] = ( P[M-1] == i )? 0:1;
	for ( int i=M-2; i >= 0; --i ){
		for ( u=1; u <= N; ++u ){
			c = (P[i] == u)? 0:1;
			dp[u][i] = dp[u][i+1] + c;
			for ( int j=0; j < (int)G[u].size(); ++j ){
				v = G[u][j];
				dp[u][i] = min( dp[u][i], dp[v][i+1] + c );
			}
		}
	}
	int res = M + 1;
	for ( u=1; u <= N; ++u )
		res = min(res, dp[u][0]);
	printf("%d\n", res);
	// Clean up memory
	for ( int i=1; i <= N; ++i ) G[i].clear();
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
	}
	return 0;
}
