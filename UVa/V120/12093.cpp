#include<cstdio>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;
const int MAXN = 10005;
int C[3] = {0};
vector<int> T[MAXN];
int dp[MAXN][4];
/*
	dp[u][0] = subtree T_u is covered unless some edges to childs of u
	dp[u][1] = subtree T_u is covered
	dp[u][2] = subtree T_u is covered and also the edge from u to parent(u)
	dp[u][3] = subtree T_u is covered and also the edges until grandparent(u)
*/
inline bool isleaf( const int &u ){ return (int)T[u].size() == 1; }

void dfs( int u, int p ){
	if ( isleaf(u) && p != -1 ){
		dp[u][1] = dp[u][0] = 0;
		dp[u][2] = min(C[1], C[2]);
		dp[u][3] = C[2];
		return;
	}
	int v;
	int sum1 = 0;
	int minTerm = INT_MAX;
	int minV;
	int atLeast0, atLeast1, atLeast2;
	dp[u][0] = dp[u][1] = 0;
	dp[u][3] = C[2];
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		dfs( v, u );
		atLeast2 = min( dp[v][2], dp[v][3] );		
		atLeast1 = min( dp[v][1], atLeast2 );
		atLeast0 = min( dp[v][0], atLeast1 );
		dp[u][0] += atLeast1;
		dp[u][1] += atLeast2;
		dp[u][3] += atLeast0;
		sum1 += atLeast1;
		minTerm = min( minTerm, dp[v][3] - atLeast1 );
	}
	dp[u][2] = min( C[1] + sum1, sum1 + minTerm );
}

int main(){
	int N;
	int u, v;
	while ( scanf("%d %d %d", &N, C + 1, C + 2) && N ){
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			T[u].push_back( v );
			T[v].push_back( u );
		}
		dfs(1, -1);
		printf("%d\n", min(dp[1][1], min(dp[1][2], dp[1][3])) );
		// Clean up memory
		for ( int i=1; i <= N; ++i ) T[i].clear();
	}
	return 0;
}
