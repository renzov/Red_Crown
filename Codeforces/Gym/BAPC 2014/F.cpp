#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <climits>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 10005;
vector<int> G[MAXN];
vector<int> T[MAXN];
int deg[MAXN];
int N;
bool B[MAXN];	// B[u] = is u part of the block
int root;
int num;
int dfsnum[MAXN];
int Right[MAXN];
int d[ MAXN ];
int f[ MAXN ];
int rev[ MAXN ]; //given the dfsnum, gives the vertex
int lazy[ 4*MAXN ];
int seg[ 4*MAXN ];
bool mark[ MAXN ];
int saved;	//number of designs we can save

void push( int node ){ // Lazy propagation to sons
	seg[node<<1] -= lazy[node];
	lazy[node<<1] += lazy[node];
	seg[(node<<1)|1] -= lazy[node];
	lazy[(node<<1)|1] += lazy[node];
	lazy[node] = 0;
}

void build_tree( int node, int l, int r ){
	lazy[node] = 0;
	if ( l==r ){
		seg[node] = d[l];
		return;
	}
	int m = ( l + r ) >> 1;
	build_tree( node<<1, l , m );
	build_tree( (node<<1)|1, m+1, r );
	seg[node] = max( seg[node<<1], seg[(node<<1)|1] );
}

pii find_max( int node, int l, int r ){
	if ( l==r ) return pii( l, seg[node] );
	int m = (l+r) >> 1;
	if ( lazy[node] ) push(node);
	if ( seg[node<<1] >= seg[(node<<1)|1] )
		return find_max(node<<1, l, m);
	else 
		return find_max((node<<1)|1, m+1, r);
}

void dec( int node, int L, int R, int l, int r ){
	if ( L == l && R == r ){
		lazy[node]++;
		seg[node]--;
		return;
	}
	int M = ( L + R ) >> 1; 
	if ( lazy[node] ) push(node);
	if ( r <= M ){
		dec( node<<1, L, M, l , r );	
	}
	else if ( l > M ){
		dec( (node<<1)|1, M+1, R, l, r);
	}
	else {
		dec( node<<1, L, M, l , M );	
		dec( (node<<1)|1, M+1, R, M+1, r);
	}
	seg[node] = max( seg[node<<1] , seg[(node<<1)|1] );
}

void find_block(){
	queue<int> q;
	bool link[MAXN]; // link[u] = is u linked to the root
	int u, v;
	for ( int i=0; i < N; ++i ){
		B[i] = true;
		link[i] = false;
		if ( deg[i] == 1 ) q.push( i );
	}
	// Similar to topsort
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		B[u] = false;
		// Take away u
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			deg[v]--;
			if ( deg[v] == 1 ){
				q.push(v);
			}
		}
	}
	// Find any vertex in block and name it root
	for ( int i=0; i < N; ++i ){
		if ( B[i] ){
			saved++;
			root = i;
		}
	}
	// Construct the tree
	for ( u=0; u < N; ++u ){
		for (int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			if ( B[u] && B[v] ) continue;
			if ( !B[u] && !B[v] ){ 
				T[u].push_back(v);
			}
			else if ( B[u] ){
				if ( !link[v] ){
					T[root].push_back(v);
					link[v] = true;
				}
			}
			else {
				if ( !link[u] ){
					T[root].push_back(u);
					link[u] = true;
				}
			}
		}
	}
}

void dfs( int u, int p ){
	int v;
	f[u] = p; // father of u in T
	dfsnum[u] = num;
	rev[num] = u;
	num++;
	// Calculate depth indexed by dfsnum
	if ( p != -1 ) d[dfsnum[u]] = d[dfsnum[p]] + 1;
	else d[dfsnum[u]] = 0;
	//Finding the intervals 
	Right[u] = dfsnum[u];
	for ( int i=0; i < T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p && dfsnum[v] == -1 ){
			dfs( v, u );
			Right[u] = Right[v];
		}
	}
}

int main(){
	int runs;
	int u, v;
	int	M, K;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d", &N, &M, &K);
		// Clearing memory
		for ( int i=0; i < N; ++i ){
			mark[i] = false;
			dfsnum[i] = -1;
			deg[i] = 0;
			G[i].clear();
			T[i].clear();
		}
		// Read the graph and construct
		for ( int i=0; i < M; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			deg[u]++, deg[v]++;
			G[u].push_back( v );
			G[v].push_back( u );
		}
		// Find the block and construct the tree
		saved = 0;
		find_block();
		// Enumerate the vertices and find the intervals and fathers and depth 
		num = 0;
		dfs( root , -1 );
		// Build a segment tree of the depths, indexed by dfsnum
		build_tree( 1, 0 , num - 1 );
		// Find the answer
		pii tmp;
		mark[root] = true;
		for ( int i=0; i < K && saved < N; ++i ){
			tmp = find_max( 1, 0 , num-1 );
			saved += tmp.second;
			u = rev[tmp.first];
			while ( !mark[u] ){
				mark[u] = true;	
				dec( 1, 0 , num-1, dfsnum[u] , Right[u] );
				u = f[u];
			}
		}
		printf("%d\n", N - saved);
	}
	return 0;
}

