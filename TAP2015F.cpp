#include<cstdio>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 50005;
const int MAXE = 55;

int dp[MAXN][MAXE];
int time[MAXN][MAXE] = {0};
int N,E;
int team[MAXN];
int D[MAXE][MAXE];
vector<int> T[MAXN];
int cases = 0;

int dfs( int u, int e, int p ){
	if ( time[u][e] == cases ) return dp[u][e];
	time[u][e] = cases;
	if ( (int)T[u].size() == 1 ) return dp[u][e] = 0;
	int &res = dp[u][e] = 0;
	int tmp, v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p ){
			if ( team[v] ){ 
				res += (D[e][team[v]] + dfs( v , team[v], u ));
			}
			else {
				tmp = INT_MAX;		
				for ( int c=1; c <= E; ++c ){
					tmp = min( tmp, D[e][c] + dfs(v, c, u) );
				}
				res += tmp;
			}
		}
	}
	return res;
}

int main(){
	int K, u , v;
	while ( scanf("%d %d", &N, &E) != EOF ){
		cases++;		
		for ( int i=1; i <= E ; ++i )
			for ( int j=1; j <= E; ++j )
				scanf("%d", &D[i][j]);
		
		fill( team, team + N + 1, 0 );
		for ( int i=1; i <= E; ++i ){
			scanf("%d", &K);
			while ( K ){
				scanf("%d", &u);
				team[u] = i;
				K--;
			}
		}
		for ( int i=1; i <= N; ++i ) T[i].clear();
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			T[u].push_back(v); T[v].push_back(u);
		}
		if ( team[1] ) printf("%d\n", dfs( 1 , team[1] , -1 ));
		else {
			int res = INT_MAX;
			for ( int i=1; i <= E; ++i ){
				res = min( res , dfs( 1 , i , -1 ) );
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
