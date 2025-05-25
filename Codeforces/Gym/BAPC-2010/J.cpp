#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 1024;

int N, M;
bool vis[MAXN];
int match[MAXN];
int X[MAXN], Y[MAXN];
string W[MAXN];
vector<int> G[MAXN];

bool alt_path( const int &u ){
	if ( vis[u] ) return false;
	vis[u] = true;
	
	int v;
	for ( int i = 0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( match[v] == -1 || alt_path( match[v] ) ){
			match[v] = u;
			return true;
		}
	}
	return false;
}

int max_matching(){
	int res = 0;
	fill( match, match + (N + M), -1 );
	for ( int i = 0; i < N; ++i ){
		fill( vis, vis + N, false );
		if ( alt_path(i) )
			res++;
	}
	return res;
}

bool intersect( const int &a, const int &b ){
	// a is a horizontal word, b is a vertical word
	int x1 = X[a], x2 = X[a] + (int)W[a].size() - 1;
	int y1 = Y[b], y2 = Y[b] + (int)W[b].size() - 1;

	if ( X[b] >= x1 && X[b] <= x2 && Y[a] >= y1 && Y[a] <= y2 )
		return W[ a ][ abs( X[b] - X[a] ) ] != W[ b ][ abs( Y[a] - Y[b] ) ];
	return false;
}

void gen_graph(){
	for ( int i = 0; i < N; ++i )
		for ( int j = N; j < (N + M); ++j )
			if ( intersect( i, j ) )
				G[i].push_back( j );
}

void process(){
	cin >> N >> M;
	for ( int i = 0; i < (N + M); ++i )
		cin >> X[i] >> Y[i] >> W[i];
	gen_graph();
	cout << N + M - max_matching() << endl;
	return;
}

void clean(){
	for ( int i = 0; i < N; ++i )
		G[i].clear();
}

int main(){
	int runs;
	cin >> runs;
	while ( runs-- ){
		process();
		clean();
	}
	return 0;
}
