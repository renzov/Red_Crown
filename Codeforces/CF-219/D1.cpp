#include<cstdio>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;
const int MAXN = 100005;

vector<int> T[MAXN];
int tsize[MAXN];
int N, K;

void dfs( const int &u, const int &p ){
	tsize[u]++;
	int v;
	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p ){
			dfs( v, u );
			tsize[u] += tsize[v];
		}
	}
}

int main(){
	scanf("%d %d", &N, &K);
	int u, v;
	for ( int i = 1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back( v );
		T[v].push_back( u );
	}
	dfs( u, -1 );
	return 0;
}
