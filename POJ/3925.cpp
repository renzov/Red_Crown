#include<cstdio>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;
typedef pair<int,int> pii;

const int MAXN = 16;

int N, M;
int W[MAXN];		// Weight of the vertices
int C[MAXN][MAXN];	// Weight of the edges
int V[MAXN];		// Vertices chosen to belong to the subset
int bestV;
int bestE;
int wvert;			// Weight of the subset of vertices
int wedge;
bool vis[MAXN];		// Mark if a vertex is already in the tree
int best[MAXN];		// Vertices in the best answer

int MST(){
	// Find MST of the vertices in V[] using Prim's algorithm
	int u, v, w;
	priority_queue< pii, vector<pii>, greater<pii> > q;
	u = V[0];
	vis[u] = true;
	for ( int i=1; i < M; ++i ){
		v = V[i];
		vis[ v ] = false;
		q.push( pii( C[u][v] , v ) );
	}
	int visited = 1;	// Number of vertices already in the tree
	int res = 0;
	while ( !q.empty() && visited < M ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( vis[u] ) continue;
		visited++;
		res += w;
		vis[u] = true;
		for ( int i=0; i < M; ++i ){
			v = V[i];
			if ( !vis[v] )
				q.push( pii( C[u][v] , v ) );
		}
	}
	return res;
}

void gen_all_subsets( int u, int left ){
	if ( left == 0 ){
		//printf("Testing subset:");
		//for ( int i=0; i < M; ++i ) printf(" %d", V[i]); puts("");
		wvert = 0;
		for ( int i=0;  i < M; ++i )
			wvert += W[ V[i] ];
		wedge = MST();
		// Check if we found a better answer
		if ( bestE == INT_MAX || wedge * bestV < bestE * wvert ){
			bestE = wedge, bestV = wvert;
			for ( int i=0; i < M; ++i )
				best[i] = V[i];
		}
		return;
	}
	// Generate in lexicografical order
	V[M  - left] = u;
	gen_all_subsets( u + 1, left - 1 );
	// Check if we can omit
	if ( N - u - 1 >= left ){
		gen_all_subsets( u + 1, left );
	}
}

void process(){
	bestE = bestV = INT_MAX;
	for ( int i=0; i < N; ++i ) scanf("%d", W + i);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			scanf("%d", &C[i][j]);
	
	gen_all_subsets( 0, M );
	printf("%d", best[0] + 1);
	for ( int i=1; i < M; ++i )
		printf(" %d", best[i] + 1);
	puts("");
}

int main(){
	while ( scanf("%d %d", &N, &M) && N )
		process();
	return 0;
}
