#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int MAXN = 200005;
vector<int> G[MAXN];
int d[MAXN];
int dp[2][MAXN];
int ord[MAXN];

void bfs( const int &N ){
	int u, v;
	queue<int> Q;

	fill( d, d + N, -1 );
	d[0] = 0;
	Q.push( 0 );

	while ( !Q.empty() ){
		u = Q.front();
		Q.pop();

		for ( int i = 0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] == -1 ){
				d[v] = d[u] + 1;
				Q.push( v );
			}
		}
	}
}

void clean( const int &N ){
	for ( int i = 0; i < N; ++i )
		G[i].clear();
}

bool comp( const int &i, const int &j ){
	return d[i] > d[j];
}

void process(){
	int N, M;
	int u, v;

	scanf("%d %d", &N, &M);
	for ( int i = 0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v);
	}
	bfs( N );
	// initialize dp
	for ( int i = 0; i < N; ++i )
		dp[1][i] = d[i];

	for ( int i = 0; i < N; ++i )
		ord[i] = i;
	sort( ord, ord + N, comp );
	// process vertices in decreasing order of distance
	for ( int i = 0; i < N; ++i ){
		u = ord[i];
		dp[0][u] = d[u];
		for ( int j = 0; j < (int)G[u].size(); ++j ){
			v = G[u][j];
			if ( d[v] > d[u] ) dp[0][u] = min( dp[0][u], dp[0][v] );
			else dp[0][u] = min( dp[0][u], dp[1][v] );
		}
	}
	printf("%d", dp[0][0]);
	for ( int i = 1; i < N; ++i )
		printf(" %d", dp[0][i]);
	puts("");
	clean( N );
}

int main(){
	int T;

	scanf("%d", &T);
	while ( T-- )
		process();
	return 0;
}
