#include<cstdio>
#include<cstdlib>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 40005;
const int FF = 3;
const int OF = 1;
const int FO = 2;
const int OO = 0;

int N, D;
int A[MAXN];
long long seg[4*MAXN][4];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1)|1; }

inline long long get_Max(){
	return max( max( seg[1][FF], seg[1][OO] ), max( seg[1][OF], seg[1][FO] ) );
}

inline int add( const long long &X, const long long &Y ){
	return ( X == LLONG_MIN || Y == LLONG_MIN )? LLONG_MIN:( X + Y );
}

void set_node( const int &node, const int &p ){
		seg[node][OO] = 0;
		seg[node][FF] = A[p];
		seg[node][OF] = LLONG_MIN;
		seg[node][FO] = LLONG_MIN;
}

void merge( const int &node, const int &L, const int &R ){
	seg[node][FF] = max( add( seg[L][FF], seg[R][OF] ), add( seg[L][FO], max( seg[R][FF], seg[R][OF] ) ) );
	seg[node][FO] = max( add( seg[L][FF], seg[R][OO] ), add( seg[L][FO], max( seg[R][FO], seg[R][OO] ) ) );
	seg[node][OF] = max( add( seg[L][OF], seg[R][OF] ), add( seg[L][OO], max( seg[R][FF], seg[R][OF] ) ) );
	seg[node][OO] = max( add( seg[L][OF], seg[R][OO] ), add( seg[L][OO], max( seg[R][OO], seg[R][FO] ) ) );
}

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){
		set_node( node, L );
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	merge( node, left(node), right(node) );	
}

void update( const int &node, const int &L, const int &R, const int &p, const int &val ){
	if ( L == R ){
		A[L] = val;
		set_node( node, L );
		return;
	}
	int M = ( L + R ) >> 1;
	if ( p > M ) update( right(node), M + 1, R, p, val );
	else update( left(node), L, M, p, val );
	merge( node, left(node), right(node) );
}

int main(){
	freopen("optmilk.in", "r", stdin);	
	freopen("optmilk.out", "w", stdout);
	
	scanf("%d %d", &N, &D);
	for ( int i = 0; i < N; ++i )
		scanf("%d", A + i);

	build( 1, 0, N - 1 );
	
	long long ans = 0LL;
	int p, val;
	
	int i = 0;
	while ( D-- ){
		i++;
		scanf("%d %d", &p, &val);
		p--;
		update( 1, 0, N - 1, p, val );
		ans += get_Max();
	}
	printf("%lld\n", ans);
	return 0;
}
