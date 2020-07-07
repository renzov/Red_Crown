#include<cstdio>
#include<algorithm>
#include<set>
#include<cassert>
#include<climits>
using namespace std;
const int MAXN = 200005;
typedef pair<int,int> pii;
typedef pair<int, pii> piii;

int X[MAXN];
int Y[MAXN];
int Q[MAXN];
int H[MAXN];
int seg[4*MAXN];
set< int > S[MAXN];

pii noAns = pii(INT_MAX, INT_MAX);

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1)|1; }

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	if ( L == R ){
		seg[node] = v;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( p > M ) update( right(node), M + 1, R, p, v );
	else update( left(node), L, M, p, v );
	seg[node] = max( seg[left(node)], seg[right(node)] );
}

void build(const int &node, const int &L, const int &R){
	seg[node] = INT_MIN;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
}

pii bin_search( int node, int L, int R, const int &y ){
	int M;
	while ( L < R ){
		M = ( L + R ) >> 1;
		if ( seg[left(node)] > y ){
			R = M;
			node = left(node);
		}
		else {
			L = M + 1;
			node = right(node);
		}
	}
	return pii( H[L], *S[L].upper_bound( y ) );
}

pii find_point( const int &node, const int &L, const int &R, const int &l, const int &r, const int &y ){
	if ( L == l && r == R ){
		if ( seg[node] <= y ) return noAns;
		return bin_search( node, L, R, y );
	}
	int M = ( L + R ) >> 1;
	if ( r <= M ) return find_point( left(node), L, M, l, r, y );
	else if ( l > M ) return find_point( right(node), M + 1, R, l, r, y );
	else {
		pii leftAns = find_point( left(node), L, M, l, M, y );
		if ( leftAns.first != INT_MAX ) return leftAns;
		return find_point( right(node), M + 1, R, M + 1, r, y );
	}
}

int main(){
	int N;
	int M;
	char type[10];
	int val, idx;
	scanf("%d", &N);
	M = 0;
	for ( int i=0; i < N; ++i ){
		scanf("%s %d %d", type, X + i, Y + i);
		if ( type[0] == 'a' ){
			Q[i] = 0;
			H[M++] = X[i];
		}
		else if ( type[0] == 'r' ){
			Q[i] = 1;
		}
		else {
			Q[i] = 2; 
		}
	}
	H[M++] = INT_MIN;
	H[M++] = INT_MAX;
	sort( H, H + M );
	M = unique( H, H + M ) - H;
	// build segment tree
	build( 1, 0, M - 1 );
	// process every query
	for ( int i=0; i < N; ++i ){
		if ( Q[i] == 0 ){
			idx = lower_bound( H, H + M, X[i] ) - H;
			assert( H[idx] == X[i] );			
			S[idx].insert( Y[i] );
			update( 1, 0, M - 1, idx, *S[idx].rbegin() );
		}
		else if ( Q[i] == 1 ){
			idx = lower_bound( H, H + M, X[i] ) - H;
			assert( H[idx] == X[i] );
			S[idx].erase( Y[i] );
			val = ( S[idx].empty() )? INT_MIN:*S[idx].rbegin();
			update( 1, 0, M - 1, idx, val );
		}
		else {
			idx = upper_bound( H, H + M, X[i] ) - H;
			if ( idx == M ){ puts("-1"); continue; }
			pii res = find_point( 1, 0, M - 1, idx, M - 1, Y[i] );
			if ( res.first == INT_MAX )
				puts("-1");
			else 
				printf("%d %d\n", res.first, res.second);
		}
	}
	return 0;
}

