#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int,int> pii;
typedef pair<pii,int> event;
typedef pair<int,int> query;
const int MAXN = 500005;
const int Internal = 0;
const int Leaves = 1;
int N, Q;

vector<int> T[MAXN];
int dfsnum[MAXN];
int L[MAXN];
int last[MAXN];
int num = 0;
event E[2*MAXN];
query q[2*MAXN];
long long res[2*MAXN];
long long sum[2][4*MAXN];
long long lazy[2][4*MAXN];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; } 

void propagate( const int &t, const int &node, const int &L, const int &M, const int &R ){
	long long v = lazy[t][node];
	lazy[t][node] = 0;
	lazy[t][left(node)] += v; 
	lazy[t][right(node)] += v;
	sum[t][left(node)] += v;	// In this case it is Ok, since we do point queries
	sum[t][right(node)] += v;	// 
}

void Add( const int &t, const int &node, const int &L, const int &R, const int &l, const int &r, const int &v ){
	if ( l == L && r == R ){
		sum[t][node] += v;
		lazy[t][node] += v;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( lazy[t][node] != 0 ) propagate( t, node, L, M, R );	
	if ( r <= M ){
		Add( t, left(node), L, M, l, r, v );
	}
	else if ( l > M ){ 
		Add( t, right(node), M + 1, R, l, r, v );
	}
	else {	
		Add( t, left(node), L, M, l, M, v ); 
		Add( t, right(node), M + 1, R, M + 1, r, v );
	}
	sum[t][node] = sum[t][left(node)] + sum[t][right(node)];
}

long long Query( const int &t, const int &node, const int &L, const int &R, const int &v ){
	if ( L == R ) return sum[t][node];
	int M = ( L + R ) >> 1;
	if ( lazy[t][node] != 0 ) propagate( t, node, L, M, R );	
	if ( v <= M ) return Query( t, left(node), L, M, v );
	return Query( t, right(node), M + 1, R, v );
}

void dfs( const int &u, const int &p ){
	L[u] = ( p != -1 )? (L[p] + 1):0;
	last[u] = dfsnum[u] = num++;
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p ){
			dfs( v, u );
			last[u] = last[v];
		}
	}
}

int main(){
	int u, v, a;
	char c;

	scanf("%d %d", &N, &Q );
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v), T[v].push_back(u);
	}
	// Find distance to root and dfsnum for every vertex
	dfs( 0, -1 );
	for ( int i=0; i < N; ++i ){
		scanf("%d", &a);
		E[i] = event( pii( -L[i], 0 ) , i );
		q[i] = query( i , a );
	}
	for ( int i=1; i <= Q; ++i ){
		scanf(" %c", &c);
		if ( c == '+' ){
			scanf("%d %d", &u, &a); u--;
			E[N - 1 + i] = event( pii( i  - L[u] , 0 ), N - 1 + i );
			q[N - 1 + i] = query( u, a );
		}
		else {
			scanf("%d", &u); u--;
			E[N - 1 + i] = event( pii( i - L[u], 1 ), N - 1 + i );
			q[N - 1 + i] = query( -1, u );
		}
	}
	sort( E, E + (N + Q) );
	// process the events
	int idx;
	int beg = 0;	// signals the first event in a bucket
	for ( int i=0; i < (N + Q); ++i ){
		if ( i && E[i].first.first != E[i-1].first.first ){ // clean up the DS
			for ( int j=beg; j < i; ++j ){
				idx = E[j].second;
				if ( q[idx].first != -1 ){ // is an add query
					u = q[idx].first, a = q[idx].second; 
					if ( dfsnum[u] != last[u] ){	// is not a leaf
						Add( Internal, 1, 0, N-1, dfsnum[u], last[u], -a ); 
					}
				}
			}
			beg = i;	// Update the index of the new bucket
		}
		// process the query
		idx = E[i].second;
		if ( q[idx].first == -1 ){	// Query the value a vertex
			u = q[idx].second;
			res[idx] = ( last[u] == dfsnum[u] )? Query( Leaves, 1, 0, N-1, dfsnum[u] ):Query( Internal, 1, 0, N-1, dfsnum[u] ); 
		}
		else {
			u = q[idx].first, a = q[idx].second;
			Add( Leaves, 1, 0, N - 1, dfsnum[u], last[u], a );
			if ( dfsnum[u] != last[u] ){ 
				Add( Internal, 1, 0, N-1, dfsnum[u], last[u], a );
			}
		}
	}
	// print the answers
	for ( int i=0; i < (N + Q); ++i )
		if ( q[i].first == -1 )
			printf("%lld\n", res[i]);
	return 0;
}
