#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MOD = 1000000007;
const int MAXN = 50005;
char S[MAXN];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

struct SegNode {
	long long cnt;
	long long f[10];
	long long g[10][10];
	long long h1[10][10];
	long long h2[10][10];
	
	SegNode(){}
};


SegNode seg[4*MAXN];

void setup( SegNode &root, const int &v ){
	for ( int x = 0; x < 10; ++x ){
		root.f[x] = 0;
		for ( int y = 0; y < 10; ++y )
			root.g[x][y] = root.h1[x][y] = root.h2[x][y] = 0;
	}
	root.f[v] = 1;
	root.cnt = 0;
}

void pushup( SegNode &root, const SegNode &L, const SegNode &R ){
	root.cnt = L.cnt + R.cnt; root.cnt %= MOD;	
	for ( int x = 0; x < 10; ++x  ){
		root.f[x] = L.f[x] + R.f[x];
		for ( int y = 0; y < 10; ++y ){
			// Calculate g[x][y]
			root.g[x][y] = L.g[x][y] + R.g[x][y]; root.g[x][y] %= MOD;
			root.g[x][y] += L.f[x] * R.f[y]; root.g[x][y] %= MOD;
			// Calculate h1
			root.h1[x][y] = L.h1[x][y] + R.h1[x][y]; root.h1[x][y] %= MOD;
			root.h1[x][y] += L.g[x][y] * R.f[y]; root.h1[x][y] %= MOD;
			root.h1[x][y] += L.f[x] * R.g[y][y]; root.h1[x][y] %= MOD;
			// Calculate h2
			root.h2[x][y] = L.h2[x][y] + R.h2[x][y]; root.h2[x][y] %= MOD;
			root.h2[x][y] += L.f[x] * R.g[x][y]; root.h2[x][y] %= MOD;
			root.h2[x][y] += L.g[x][x] * R.f[y]; root.h2[x][y] %= MOD;
			// sum up the values to the root
			root.cnt += L.f[x] * R.h2[y][x]; root.cnt %= MOD;
			root.cnt += L.g[x][y] * R.g[y][x]; root.cnt %= MOD;
			root.cnt += L.h1[x][y] * R.f[x]; root.cnt %= MOD;
		}
	}
}

SegNode query(const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && r == R )	return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	SegNode res;
	SegNode lf = query( left(node), L, M, l, M );
	SegNode	rg = query( right(node), M + 1, R, M + 1, r );
	pushup( res, lf, rg );
	return res;
}

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	if ( L == R ){
		setup( seg[node], v );
		return;
	}
	int M = (L + R) >> 1;
	if ( p <= M ) update( left(node), L, M, p, v );
	else update( right(node), M + 1, R, p, v );
	pushup( seg[node], seg[left(node)], seg[right(node)] );
}

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){
		setup( seg[node], (int)S[L] );
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	pushup( seg[node], seg[left(node)], seg[right(node)] );
}

int main(){
	int N, Q;

	scanf("%s", S);
	N = strlen(S);
	for ( int i=0; i < N; ++i )	
		S[i] -= '0';
	build( 1, 0, N - 1 );

	int op, l, r;
	SegNode res;
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d %d", &op, &l, &r);
		if ( op == 1 ){	// Query
			l--, r--;
			res = query( 1, 0, N - 1, l, r );
			printf("%lld\n", res.cnt);
		}
		else {	// Update
			l--;
			update( 1, 0, N - 1, l, r );
		}
	}
	return 0;
}

