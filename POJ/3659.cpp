#include<cstdio>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 10005;
vector<int> T[MAXN];
int dp[MAXN][2][2];
int mini[MAXN][2];

void dfs( const int &u, const int &p ){
	int v;
	if ( (int)T[u].size() == 1 && p != -1 ){
		dp[u][0][0] = INT_MAX;
		dp[u][0][1] = 0;
		dp[u][1][0] = 1;
		dp[u][1][1] = 1;
		return;
	}
	int sum;
	int best;
	
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p ){
			dfs( v, u );
		}
	}
	
	for ( int take=0; take < 2; ++take  )
		for ( int cov=0; cov < 2; ++cov ){
			sum = 0;
			best = INT_MAX;
			for ( int i=0; i < (int)T[u].size(); ++i ){
				v = T[u][i];
				if ( v != p ){
					mini[v][take] = min( dp[v][0][take] , dp[v][1][take] );									
					sum += mini[v][take];
					best = min( best , dp[v][1][take] - mini[v][take] );
				}
			}
		
			if ( take || cov ){
				dp[u][take][cov] = sum + take;
			}
			else {
				dp[u][take][cov] = sum + best + take;
			}
		}
}


int main(){
	int N;
	int u, v;
	scanf("%d", &N);
	for ( int i=1; i < N ; ++i ){
		scanf("%d %d", &u, &v);
		T[u].push_back(v); 
		T[v].push_back(u);
	}
	if ( N == 1 ) {
		puts("1");
	}
	else {
		dfs(1,-1);
		printf("%d\n", min( dp[1][1][0], dp[1][0][0] ));
	}
	return 0;
}
