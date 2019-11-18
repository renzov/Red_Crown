#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 505;
const int INF = 5000005;
int N;

vector<int> T[MAXN];
vector<int> W[MAXN];
int indeg[MAXN];
int dp[MAXN][MAXN];
int full[MAXN][MAXN];

void dfs( const int &u ){
	if ( (int) T[u].size() == 0 ){ // u is a leaf
		full[u][1] = dp[u][1] = 0;
		for ( int i=2; i <= N; ++i )
			dp[u][i] = full[u][i] = INF;
		return;
	}
	// u is not a leaf
	int last = -1;
	int v, w;
	full[u][1] = dp[u][1] = 0;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		w = W[u][i];
		v = T[u][i];
		dfs( v );
		if ( last == -1 ){	// copy the dp tables from child
			for ( int k = 1; k < N; ++k ){
				dp[u][k + 1] = dp[v][k] + w;
				if ( dp[u][k + 1] >= INF ) dp[u][k + 1] = INF;
				full[u][k + 1] = full[v][k] + 2*w;
				if ( full[u][k + 1] >= INF ) full[u][k + 1] = INF;
			}
		}
		else {	
			for ( int k=N; k > 1; k-- ){
				// Iterate k in decreasing other to use the values of the table in prevoius iteration
				// and not mess up
				for ( int j=1; j < k; ++j ){
					full[u][k] = min( full[u][k], full[v][j] + full[u][k - j] + 2*w );
					dp[u][k] = min( dp[u][k], full[v][j] + dp[u][k - j] + 2*w );
					dp[u][k] = min( dp[u][k], dp[v][j] + full[u][k - j] + w );
				}	
			}
		}
		last = v;
	}
}


void process(){
	int u, v, w;
	for ( int i=1; i < N; ++i ){
		scanf("%d %d %d", &v, &u, &w);
		T[u].push_back(v), W[u].push_back(w);
		indeg[v]++;
	}
	int root;
	for ( int i=0; i < N; ++i )
		if ( indeg[i] == 0 ){
			root = i;
			break;
		}
	
	dfs( root );
	int Q;
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d", &w);
		for ( int i=N; i >= 1; --i ){
			if ( dp[root][i] <= w ){
				printf("%d\n", i);
				break;
			}
		}
	}
	// Clean up the memory used
	for ( int i=0; i < N; ++i ){
		indeg[i] = 0;
		T[i].clear();
		W[i].clear();
	}
}

int main(){
	int cases = 0;
	while ( scanf("%d", &N) == 1 && N ){
		printf("Case %d:\n", ++cases);
		process();
	}
	return 0;
}
