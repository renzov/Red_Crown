#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
typedef pair<int,int> edge;
const int MAXN = 10005;

edge E[2*MAXN];
vector<int> G[MAXN];
int N, M;
int color[MAXN];
int dfsnum[MAXN];
int num = 0;

int totalOdd;
int cntOddCycles[2*MAXN];
int cntEvenCycles[2*MAXN];
int curOdd;
int curEven;

inline bool isvalid( const int &e ){
	return totalOdd == 0 || ( cntOddCycles[e] == totalOdd && 
							  cntEvenCycles[e] == 0 );
}

void dfs( const int &u, const int &p, const int &inedge ){
	int v;
	int idx;

	dfsnum[u] = ++num;
		
	int tmpOdd = curOdd;
	int tmpEven = curEven;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		idx = G[u][i];
		v = E[idx].first == u? E[idx].second:E[idx].first;
		if ( p == v ) continue;
		if ( dfsnum[v] == 0 ){
			color[v] = 1 - color[u];
			dfs( v, u, idx );
		}
		else if ( dfsnum[v] < dfsnum[u] ){	// Back edge
			if ( color[v] == color[u] ){	// odd cycle
				totalOdd++;
				curOdd++;
				// idx is not a tree edge -- will be contained in a unique cycle
				cntOddCycles[idx] = 1;
			}
			else { // even cycle
				curEven++;
				// idx is not a tree edge -- will be contained in a unique cycle
				cntEvenCycles[idx] = 1;
			}
		}
		else {	// We are "closing a cycle" (it does not affect inedge)
			if ( color[u] == color[v] ){
				curOdd--;
			}
			else {
				curEven--;
			}
		}
	}
	if ( inedge != -1 ){	
		cntOddCycles[inedge] = curOdd - tmpOdd;
		cntEvenCycles[inedge] = curEven - tmpEven;
	}
}

int main(){
	int u, v;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		E[i] = edge( min(u,v), max(u,v) );
		G[u].push_back(i), G[v].push_back(i);
	}

	totalOdd = curOdd = curEven = 0;
	for ( int i=1; i <= N; ++i )
		if ( dfsnum[i] == 0 ){
			assert( curOdd == 0 );
			assert( curEven == 0 );
			color[i] = 0;
			dfs( i, -1, -1 );
		}

	int res = 0;
	for ( int i=0; i < M; ++i )
		if ( isvalid(i) ) res++;
	
	printf("%d\n", res);
	for ( int i=0; i < M; ++i )
		if ( isvalid(i) )
			printf("%d\n", i + 1);
	return 0;
}
