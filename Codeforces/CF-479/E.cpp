#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 200005;
vector<int> G[MAXN];
int dfsnum[MAXN];
int cmp[MAXN];
int size;
int num;

void dfs( const int &u, const int &p ){
	cmp[size++] = u;
	int v;
	dfsnum[u] = num++;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( dfsnum[v] == -1 )
			dfs( v, u );
	}
}

int main(){
	int u, v;
	int N, M;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	fill( dfsnum, dfsnum + N, -1 );
	int res = 0; 
	bool ok;
	for ( int i=0; i < N; ++i ){
		if ( dfsnum[i] == -1 ){
			size = 0;
			dfs( i, -1 );
			ok = true;
			for ( int j=0; ok && j < size; ++j ){
				u = cmp[j];
				if ( (int)G[u].size() != 2 ) ok = false;
			}
			if (ok) res++;
		}
	}
	printf("%d\n", res);
	return 0;
}
