#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 1024;
vector<int> G[MAXN];
int N;
int M;
int cnt[MAXN];
int f[MAXN];

inline int find_set( const int &x ){ return f[x] == x? x:(f[x] = find_set( f[x] )); }

void process(){
	int u, v;
	for ( int i=0; i < N; ++i )
		f[i] = -1, cnt[i] = 0;
	f[0] = 0;	
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		if ( u == 0 ) f[v] = v;
		else G[v].push_back(u);	// Add reverse arc
	}
	// 0, 1, 2, ...., N - 1 is a topological order of the original graph
	for ( v=1; v < N; ++v ){
		for ( int i=0; i < (int) G[v].size() && f[v] != v; ++i ){
			u = G[v][i];
			if ( f[v] == -1 )
				f[v] = find_set( u );
			else if ( find_set(v) != find_set(u) ){
				f[v] = v;
			}
		}
	}
	
	for ( int i=1; i < N; ++i )
		cnt[ find_set(i) ]++;
	
	int res = 0;
	for ( int i=1; i < N; ++i )
		if ( f[i] == i )
			res += cnt[i] * ( N - 1 - cnt[i] );
	
	printf("%d\n", (res >> 1) + N - 1 );
}


int main(){
	while ( scanf("%d %d", &N, &M) == 2 ){
		process();
		for ( int i=0; i < N; ++i )	G[i].clear();
	}

	return 0;
}
