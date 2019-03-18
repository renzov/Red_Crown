#include<cstdio>
using namespace std;

const int MAXN = 100005;
int N, M;
int pos[MAXN];
int seg[8*MAXN];
inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; } 

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){
		seg[node] = ( L < M )? 0:1;
		return;
	}
	int Mid = ( L  + R ) >> 1;
	build( left(node), L, Mid );
	build( right(node), Mid + 1, R );
	seg[node] = seg[left(node)] + seg[right(node)];
}

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	if ( L == R ){
		seg[node] += v;
		return;
	}
	int Mid = ( L + R ) >> 1;
	if ( p > Mid ) update( right(node), Mid + 1, R, p, v );
	else update( left(node), L, Mid, p, v );
	seg[node] = seg[left(node)] + seg[right(node)];
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && R == r ) return seg[node];
	int Mid = ( L + R ) >> 1;
	if ( r <= Mid ) return query( left(node), L, Mid, l, r );
	if ( l > Mid ) return query( right(node), Mid + 1, R, l, r );
	return query( left(node), L, Mid, l, Mid ) + query( right(node), Mid + 1, R, Mid + 1, r );
}

void process(){
	int a;
	scanf("%d %d", &N, &M);
	build(1, 0, M + N - 1);
	for ( int i=0; i < N; ++i ) pos[i] = i + M;
	int R = N + M - 1;
	while ( M-- ){
		scanf("%d", &a);
		a--;
		update(1, 0, R, pos[a], -1 );
		printf("%d", query(1, 0, R, M, pos[a]));
		update(1, 0, R, M, 1 );
		pos[a] = M;
		if ( M ) putchar(' ');
	}
	puts("");
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
	}

	return 0;
}
