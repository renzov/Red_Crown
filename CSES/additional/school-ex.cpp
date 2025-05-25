#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> G[MAXN];
int vis[MAXN];
int f[MAXN];
bool reach[2][MAXN];

int dfs( const int &u, const int &p ){
	int sz = 1;
	int v;

	vis[u] = true;
	for ( int i = 0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p || vis[v] ) continue;
		sz += dfs( v, u );
	}
	return sz;
}

int main(){
	int N, M;
	int u, v;
	int sz;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for ( int i = 0; i < N; ++i )
		if ( !vis[i] ){
			sz = dfs( i, -1 );
			f[sz]++;
		}
	// decompose the frequency
	vector<int> V;
	int p;
	for ( int i = 1; i <= N; ++i ){
		if ( f[i] > 0 ){
			p = 0;
			while ( (1 << p) < f[i] ) p++;
			p--;
			while ( p >= 0 ){
				V.push_back(i * (1 << p));
				f[i] -= (1 << p);
				p--;
			}
			if ( f[i] > 0 ){
				V.push_back( i * f[i] );
				f[i] = 0;
			}
		}
	}
	int last = 0;
	int act = 1;
	// subset sum dp
	// base case:
	for ( int i = 1; i <= N; ++i )
		reach[last][i] = false;
	reach[last][0] = true;
	// general case
	for ( int k = 0; k < (int)V.size(); ++k ){
		for ( int i = 0; i <= N; ++i ){
			reach[act][i] = reach[last][i];
			if ( i >= V[k] ){
				reach[act][i] |= reach[last][i - V[k]];
			}
		}
		swap(last, act);
	}
	for ( int i = 1; i <= N; ++i )
		putchar( reach[last][i]? '1':'0' );
	puts("");		
	return 0;
}
