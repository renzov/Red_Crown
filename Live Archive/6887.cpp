#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN = 10005;
vector<int> G[MAXN];
int N, M;
int t;	//time
int vis[MAXN];
int match[MAXN];

bool augment( const int &u ){
	if ( vis[u] >= t ) return false;	// already visited
	vis[u] = t;
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( match[v] == -1 || augment( match[v] ) ){
			match[v] = u;
			return true;
		}
	}
	return false;
}

void process(){
	int u, v;
	while ( M-- ){
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
	}
	fill( match, match + N, -1 );
	t = M = 0;
	for ( int i=0; i < N; ++i ){
		t++; 
		if ( augment(i) ) M++;
	}
	puts( M == N? "YES":"NO");
	// Clean memory
	for ( int i=0; i < N; ++i ){ 
		G[i].clear();
		vis[i] = 0;
	}
}

int main(){
	while ( scanf("%d %d", &N, &M) == 2 )
		process();
	return 0;
}
