#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
const int MAXQ = 200005;
typedef pair<int, int> point;
typedef pair<int, int> query;

point P[MAXQ];
query q[MAXQ];
set<point> S[MAXQ]; 
int V[MAXQ];
int seg[4*MAXQ];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

void build( const int &node, const int &L, const int &R ){
	seg[node] = 0;
	if ( L == R ) return;
	int M = (L + R) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
}

int binsearch( int node, int L, int R, const int &v ){
	int M;
	while ( L < R ){
		M = ( L + R ) >> 1;
		if ( seg[left(node)] >= v ) R = M, node = left(node);
		else L = M + 1, node = right(node);
	}
	return L;
}

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	seg[node] = max( seg[node], v );
	if ( L == R ){
		if ( seg[node] < v ) seg[node] = v;
		return;
	} 
	int M = ( L + R ) >> 1;
	if ( p <= M ) update( left(node), L, M, p, v );
	else update( right(node), M + 1, R, p, v );
}

int search( const int &node, const int &L, const int &R, const int &l, const int &r, const int &v ){
	if ( l == L && r == R ){
		return seg[node] >= v? binsearch(node, L, R, v):-1;
	}
	int M = ( L + R ) >> 1;
	if ( r <= M ) return search( left(node), L, M, l, r, v );
	else if ( l > M ) return search( right(node), M + 1, R, l, r, v );
	else {
		int res = search( left(node), L, M, l, M, v );
		if ( res != -1 ) return res;
		return search( right(node), M + 1, R, M + 1, r, v );
	}
}

int main(){
	int Q;
	int A, B, idx;
	int N = 0;
	int M;
	char op;
	int x; 

	scanf("%d", &Q);
	for ( int i=0; i < Q; ++i ){
		scanf(" %c", &op);
		if ( op == 'D' ){
			scanf("%d %d", &A, &B);
			P[N] = point( B, A );
			q[i] = query( 0, N );
			V[N] = B;
			N++;
		}
		else {
			scanf("%d", &idx);
			idx--;
			q[ i ] = query( 1, idx );
		}
	}
	sort( V, V + N );
	M = unique( V, V + N ) - V;
	// Compress the first coordinate
	for ( int i=0; i < N; ++i ){
		P[i].first = lower_bound( V, V + M, P[i].first ) - V;
		//printf("P[%d] = (%d, %d)\n", i + 1, P[i].first, P[i].second );
	}
	// Initialize the DS
	build( 1, 0, M - 1 );
	// Process the queries
	for ( int i=0; i < Q; ++i ){
		if ( q[i].first ){
			idx = q[i].second;
			A = P[idx].first, B = P[idx].second;
			if ( S[A].rbegin()->first > B ){
				printf("%d\n", S[A].upper_bound( point(B, idx) )->second + 1 );
			}
			else {
				x = -1;
				if ( A < M - 1 ){
					//printf("search [%d, %d] -> %d\n", A + 1, M - 1, B);
					x = search( 1, 0, M - 1, A + 1, M - 1, B );
				}
				if ( x == -1 ) puts("NE");
				else printf("%d\n", S[x].lower_bound( point( B, -1 ) )->second + 1 );
			}
		}
		else {
			idx = q[i].second;
			A = P[idx].first, B = P[idx].second;
			S[ A ].insert( point(B, idx) );
			update( 1, 0, M - 1, A, B );
		}
	}
	return 0;
}
