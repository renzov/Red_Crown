#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 400005;

vector<int> T[MAXN];
int C[MAXN];
// For dfs numbering
int l[MAXN];
int rev[MAXN];
int r[MAXN];
int dfsnum = 0;
long long seg[4*MAXN];
long long lazy[4*MAXN];

void dfs( const int &u, const int &p ){
	int v;
	
	r[u] = l[u] = dfsnum;
	rev[dfsnum] = u;
	dfsnum++;

	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		dfs( v, u );
		r[u] = r[v];
	}
}

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return ( x << 1 ) | 1; }

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){
		int u = rev[L];
		seg[ node ] = 1LL << C[u];
		lazy[ node ] = 0;
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	seg[node] = seg[ left(node) ] | seg[ right(node) ];
}

void propagate( const int &node ){
	lazy[ left( node ) ] = lazy[node];
	lazy[ right( node ) ] = lazy[node];
	seg[ left( node ) ] = lazy[node];
	seg[ right( node ) ] = lazy[node];
	lazy[ node ] = 0;
}

void update( const int &node, const int &L, const int &R, const int &lf, const int &rt, const int &c ){
	if ( lf == L && rt == R ){
		seg[node] = lazy[node] = 1LL << c;
		return;
	}

	if ( lazy[node] ) propagate( node );
	
	int M = ( L + R ) >> 1;

	if ( rt <= M ){
		update( left(node), L , M, lf, rt, c );
	}
	else if ( lf > M ){
		update( right(node), M + 1, R, lf, rt, c );
	}
	else {
		update( left(node), L , M, lf, M, c );
		update( right(node), M + 1, R, M + 1, rt, c );
	}
	// update
	seg[node] = seg[ left(node) ] | seg[ right(node) ];
}

long long query( const int &node, const int &L, const int &R, const int &lf, const int &rt ){
	if ( lf == L && rt == R ) return seg[node];
	if ( lazy[node] ) propagate( node );
	int M = ( L + R ) >> 1;
	if ( rt <= M ) return query( left(node), L, M, lf, rt );
	if ( lf > M ) return query( right(node), M + 1, R, lf, rt );
	return query( left(node), L, M, lf, M ) | query( right(node), M + 1, R, M + 1, rt );
}

int main(){

	int N, Q;
	int u, v, c, t;

	scanf("%d %d", &N, &Q);

	for ( int i=0; i < N; ++i )
		scanf("%d", C + i);

	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v);
		T[v].push_back(u);
	}

	fill( l, l + N , -1 );
	dfs( 0, -1 );
	build( 1, 0, N - 1 );

	while ( Q-- ){
		scanf("%d", &t);	
		if ( t == 1 ){
			scanf("%d %d", &u, &c);
			u--;
			update( 1, 0, N - 1, l[u], r[u], c );
		}
		else {
			scanf("%d", &u);
			u--;
			printf("%d\n", __builtin_popcountll( query( 1, 0, N - 1, l[u], r[u] ) ) );
		}
	}
	return 0;
}
