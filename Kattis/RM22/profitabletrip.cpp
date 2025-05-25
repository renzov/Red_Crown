#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 1 << 11;
const int MAXCAP = 1 << 7;
int N, M, C;
vector<int> G[MAXN];
vector<int> W[MAXN];
bool vis[MAXCAP][MAXN];

inline int encode( const int &x, const int &y ){
	// x = capacity, y = vertex
	return (x << 11) | y;
}

int main(){

	int u, v, w, nw;

	scanf("%d %d %d", &N, &M, &C );
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back( v );
		W[u].push_back( w );
	}

	queue<int> Q;
	vis[0][0] = true;
	Q.push( encode(0, 0) );

	int state;
	while ( !Q.empty() ){
		state = Q.front();
		Q.pop();
		u = state & ( (1 << 11) - 1 );
		w = state >> 11;

		for ( int i = 0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			nw = min( C, W[u][i] + w );
			if ( nw < 0 ) continue;
			if ( !vis[nw][v] ){
				vis[nw][v] = true;
				Q.push( encode(nw, v) );
			}
		}
	}
	// Get the answer
	int ans = -1;
	for ( int i = C; i >= 0; i-- )
		if ( vis[i][N - 1] ){
			ans = i;
			break;
		}
	printf("%d\n", ans);
	return 0;
}
