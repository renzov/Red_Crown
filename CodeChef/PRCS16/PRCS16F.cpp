#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 50005;
typedef pair<long long, long long> pLL;
int N;
vector<int> T[MAXN];
vector<int> W[MAXN];
int len[MAXN];		// length of the path from root to the vertex
int size[MAXN];		// size of the subtree rooted at a vertex
long long total;	// total cost of the initial tree
long long res;

pair<int, int> dfs( const int &u, const int &p ){
	int v, w;
	
	pLL best = pLL( 0, 0 );
	pLL bestSon;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		w = W[u][i];
		if ( v == p ) continue;
		bestSon = dfs(v, u);
		bestSon.second += w; // path length
		bestSon.first += 1LL * (size[u] - size[v]) * bestSon.second;
		bestSon.first -= size[v] * w;
		if ( bestSon < best )
			best = bestSon;
	}
	if ( p != -1 ){	// is not the root
		res = min ( res, total + best.first - 1LL * len[p] * size[u] );
	}
	return best;
}

void precalc( const int &u, const int &p ){
	int v;

	size[u] = 1;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		len[v] = len[u] + W[u][i];
		precalc(v, u);
		size[u] += size[v];
		total += W[u][i] * size[v];
	}
}

int main(){
	int u, v, w;

	scanf("%d", &N);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		T[u].push_back(v), T[v].push_back(u);
		W[u].push_back(w), W[v].push_back(w);
	}
	total = 0;
	len[0] = 0;
	precalc( 0, -1 );
	res = total;
	dfs( 0, -1 );
	

	return 0;
}
