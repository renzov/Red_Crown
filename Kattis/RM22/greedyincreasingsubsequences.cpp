#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 200002;

int seg[4*MAXN];
int root = 1;
vector<int> S[MAXN];

inline int left( const int &node ){ return node << 1; }
inline int right( const int &node ){ return (node << 1) | 1; }

void build( const int &node, const int &L, const int &R ){
	seg[node] = INT_MAX;
	if ( L == R ) return; 
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
}

int search( const int &node, const int &L, const int &R, const int &val ){
	if ( L == R ) return L;
	int M = ( L + R ) >> 1;
	if ( seg[ left( node ) ] < val ) return search( left(node), L, M, val );
	else return search( right(node), M + 1, R, val );
} 

void update( const int &node, const int &L, const int &R, const int &p, const int &val ){
	if ( L == R ){
		seg[node] = val;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( p <= M ) update( left(node), L, M, p, val );
	else update( right(node), M + 1, R, p, val );
	// when we return from recursion
	seg[node] = min( seg[ left(node) ], seg[ right(node) ] );
}

int main(){
	int N, a;
	int size = 0;	// number of subsequences
	int idx;

	scanf("%d",&N);
	// Initialize segment tree
	build( root, 0, N - 1 );
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &a);
		if ( seg[root] >= a ){	// create a new sequence
			update( root, 0, N - 1, size, a );
			S[size].push_back( a );
			size++;
		}
		else {
			idx = search( root, 0, N - 1, a );
			S[idx].push_back( a );
			update( root, 0, N - 1, idx, a );
		}
	}
	// Print answer
	printf("%d\n", size );
	for ( int i = 0; i < size; ++i ){
		printf("%d", S[i][0]);
		for ( int j = 1; j < (int)S[i].size(); ++j )
			printf(" %d", S[i][j]);
		puts("");
	}
	return 0;
}
