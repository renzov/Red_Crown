#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

int N, M;
vector<int> G[MAXN];
int dfsnum[MAXN];
int pre[MAXN];
int L[MAXN];
int num;
int s, t;

void dfs( const int &u, const int &p ){
	int v;

	dfsnum[u] = num++;

	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;

		if ( dfsnum[v] == -1 ){
			L[v] = L[u] + 1;
			pre[v] = u;
			dfs( v, u );
		}
		else if ( dfsnum[v] < dfsnum[u] ){
			s = u, t = v;
		}
	}
}

int main(){
	scanf("%d %d", &N, &M);
	
	int u, v;
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	
	fill( dfsnum, dfsnum + N, -1 );
	fill( pre, pre + N, -1 );
	fill( L, L + N, -1 );

	s = t = -1;

	for ( int i=0; i < N; ++i ){
		if ( s != -1 ) break;	// cycle found
		if ( dfsnum[i] == -1 ){
			L[i] = 0;
			dfs( i, -1 );
		}
	}

	if ( s == -1 ){
		puts("IMPOSSIBLE");
	}
	else {
		printf("%d\n", L[s] - L[t] + 2 );
		u = s;
		printf("%d", u + 1);
		do {
			u = pre[u];
			printf(" %d", u + 1);		
		}
		while ( u != t );
		printf(" %d", s + 1);
		puts("");
	}
	return 0;
}
