#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
const int MAXN = 100005;
int Q;
char P[MAXN];
int MinS[4*MAXN];
int MaxS[4*MAXN];
char T[8];
int len;
bool leaf[4*MAXN];
bool inv[4*MAXN];

struct chunck {
	int l, r;
	int v;
	chunck(){}
	void invert( const int &a, const int &b ){
		// a >= l && b <= r
		for ( int i=a; i <= b; ++i ){
			v ^= ( 1 << (i - l) );
		}
	}
	void invert(){
		invert(l , r);
	}
};

chunck V[MAXN];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1)|1; }

int match( const int &p ){
	int res = 0;
	for ( int i=0; T[i] ; ++i ){
		if ( tolower(T[i]) != tolower( P[p + i] ) )	return -1;
		if ( T[i] != P[p + i] ) res |= ( 1 << i );
	}
	return res;
}

void pushup( const int &node, const int &l, const int &r ){
	if ( MaxS[l] == -1 ){
		MaxS[node] = MaxS[r], MinS[node] = MinS[r]; 
	}
	else if ( MaxS[r] == -1 ){
		MaxS[node] = MaxS[l], MinS[node] = MinS[l]; 		
	}
	else {
		MaxS[node] = max( MaxS[l], MaxS[r] );
		MinS[node] = min( MinS[l], MinS[r] );
	}
}

void pushdown( const int &node, const int &l, const int &r, const int &L, const int &M, const int &R ){
	int minv, maxv;
	if ( MaxS[l] != -1 ){
		if ( leaf[l] ){
			V[L].invert();
			MaxS[l] = MinS[l] = __builtin_popcount( V[L].v );
		}
		else {
			inv[l] = not inv[l];
			minv = MinS[l], maxv = MaxS[l];
			MinS[l] = len - maxv;
			MaxS[l] = len - minv;
		}
	}
	if ( MaxS[r] != -1 ){
		if ( leaf[r] ){
			V[R].invert();
			MaxS[r] = MinS[r] = __builtin_popcount( V[R].v );
		}
		else {
			inv[r] = not inv[r];
			minv = MinS[r], maxv = MaxS[r];
			MinS[r] = len - maxv;
			MaxS[r] = len - minv;
		}
	}
	inv[node] = false;
}

void single_update( const int &node, const int &L, const int &R, const int &p, const int &ql, const int &qr ){
	if ( leaf[node] ){
		V[L].invert( ql, qr );
		MaxS[node] = MinS[node] = __builtin_popcount( V[L].v );
		return;
	}
	int M = ( L + R ) >> 1;
	if ( inv[node] ) pushdown( node, left(node), right(node), L, M, R );
	if ( p <= M ) single_update( left(node), L, M, p, ql, qr );
	else single_update( right(node), M + 1, R, p, ql, qr );
	pushup( node, left(node), right(node) );
}

void build( const int &node, const int &L, const int &R ){
	inv[node] = leaf[node] = false;
	if ( L == R ){
		leaf[node] = true;
		if ( V[L].v == -1 ){
			MaxS[node] = MinS[node] = -1;
		}
		else {
			MaxS[node] = MinS[node] = __builtin_popcount( V[L].v );
		}
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	pushup( node, left(node), right(node) );
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( MaxS[node] == -1 ) return -1;
	if ( l == L && r == R ) return MaxS[node];
	int M = ( L + R ) >> 1;
	if ( inv[node] ) pushdown( node, left(node), right(node), L, M, R );
	if ( r <= M ) return query( left(node), L, M, l, r);
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	return max( query( left(node), L, M, l, M ), query( right(node), M + 1, R, M + 1, r ) );
}

void update( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( MaxS[node] == -1 ) return;
	if ( l == L && R == r ){
		int maxv, minv;
		if ( leaf[node] ){
			V[L].invert();
			MaxS[node] = MinS[node] = __builtin_popcount( V[L].v );
		}
		else {	
			inv[node] = not inv[node];
			minv = MinS[node], maxv = MaxS[node];
			MinS[node] = len - maxv;
			MaxS[node] = len - minv;
		}
		return;
	}
	int M = ( L + R ) >> 1;
	if ( inv[node] ) pushdown( node, left(node), right(node), L, M, R );
	if ( r <= M ){
		update( left(node), L, M, l, r );
	}
	else if ( l > M ){
		update( right(node), M + 1, R, l, r );
	}
	else {
		update( left(node), L, M, l, M );
		update( right(node), M + 1, R, M + 1, r );		
	}
	pushup( node, left(node), right(node) );
}

void process(){
	scanf("%s", P);
	// initialize the array of chuncks
	int N = strlen(P);
	int M = strlen(T);
	len = M;

	for ( int i=0; i < N; ++i ){
		if ( (i + M - 1) < N ){
			V[i].v = match( i );
			V[i].l = i;
			V[i].r = i + M - 1;
		}
		else {
			V[i].v = -1;
			V[i].l = i;
			V[i].r = N - 1;
		}	
	}
	build( 1, 0, N - 1 );
	int l, r;
	int ql, qr;
	int res;
	while ( Q-- ){
		scanf("%d %d", &l, &r);
		l--, r--;
		if ( (r - l + 1) >= M ){
			res = query( 1, 0, N - 1, l, r - M + 1 );
			update( 1, 0, N - 1, l, r - M + 1 );
		}
		else {
			res = -1;
		}
		printf("%d\n", res);
		// right update
		int start = max( l, r - M + 2 );
		int end = r;
		for ( int i=start; i <= end; ++i )
			if ( V[i].v != -1 ) {
				ql = max( l, V[i].l );
				qr = min( r, V[i].r );
				if ( ql <= qr ) 
					single_update( 1, 0, N - 1, i, ql, qr );
			}
		// left update
		start = l - 1;
		end = max(l - M + 1, 0 );
		for ( int i=start;  i >= end; --i )
			if ( V[i].v != -1 ){
				ql = max( l, V[i].l );
				qr = min( r, V[i].r );
				if ( ql <= qr )
					single_update( 1, 0, N - 1, i, ql, qr );			
			}
	}
}

int main(){
	while ( scanf("%d %s", &Q, T) != EOF )
		process();
	return 0;
}
