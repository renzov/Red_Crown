#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 50005;
const char EMPTY = 0;
const char CLEAR = 1;
const char FULL = 2;

inline int left(const int &x){ return x << 1; }
inline int right(const int &x){ return (x<<1)|1; }
int N;

int Max[4*MAXN];
int LMax[4*MAXN];
int RMax[4*MAXN];
char lazy[4*MAXN]; // 0 - No lazy, 1 - clear, 2 - fill

void propagate( const int &node, const int &L, const int &M, const int &R ){
	if ( L != R ){
		lazy[ left(node) ] = lazy[ right(node) ] = lazy[node];
		if ( lazy[node] == CLEAR ){
			LMax[left(node)] = RMax[left(node)] = Max[left(node)] = M - L + 1;
			LMax[right(node)] = RMax[right(node)] = Max[right(node)] = R - M;
		}
		else {
			LMax[left(node)] = RMax[left(node)] = Max[left(node)] = 0;
			LMax[right(node)] = RMax[right(node)] = Max[right(node)] = 0;	
		}
		lazy[node] = EMPTY;		
	}
}

int query( const int &node, const int &L, const int &R, const int &S ){
	if ( LMax[node] >= S ) return L;
	int M = ( L + R ) >> 1;
	if ( lazy[ node ] != EMPTY ) propagate(node, L, M, R);
	if ( Max[left(node)] >= S ) return query( left(node), L, M, S );
	if ( RMax[left(node)] == 0 ) return query( right(node), M + 1, R, S );
	if ( RMax[ left(node) ] + LMax[ right(node) ] >= S ){
		return M - RMax[ left(node) ] + 1;
	}	
	return query( right(node), M + 1, R, S );
}

void update( const int &node, const int &L, const int &R, const int &l, const int &r, const char &t ){
	//printf("upt = [%d, %d]\n", L , R);	
	if ( l == L && r == R ){
		//printf("Lazy Update: [%d, %d]\n", L, R);
		if ( L != R ) lazy[ node ] = t;
		if ( t == CLEAR ){
			LMax[node] = RMax[node] = Max[node] = R - L + 1;
		}
		else {
			LMax[node] = RMax[node] = Max[node] = 0;
		}
		return;
	}
	int M = ( L + R ) >> 1;	
	if ( lazy[node] != EMPTY ) propagate( node, L, M, R );
	if ( r <= M ) update( left(node), L, M, l, r, t );
	else if ( l > M ) update( right(node), M + 1, R, l, r, t );
	else {
		update( left(node), L, M, l, M, t );
		update( right(node), M + 1, R, M + 1, r, t );
	}
	// Update the node
	Max[node] = max( max( Max[left(node)] , Max[right(node)] ) , RMax[ left(node) ] + LMax[right(node)] );
	LMax[node] = LMax[left(node)];
	RMax[node] = RMax[right(node)];
	if ( LMax[ left( node ) ] >= M - L + 1 ){ // Full Left interval
		LMax[node] += LMax[ right(node) ];
	}
	if ( RMax[ (node) ] >= R - M ){ // Full Right interval
		RMax[node] += RMax[ left(node) ];
	}
}

int main(){
	int M, op;
	int X, D;
	int l, r;

	scanf("%d %d", &N, &M);
	lazy[ 1 ] = CLEAR;
	Max[ 1 ] = LMax[ 1 ] = RMax[ 1 ] = N;
	while ( M-- ){
		scanf("%d", &op);
		if ( op == 1 ){
			scanf("%d", &D);
			if ( Max[ 1 ] >= D ){
				X = query( 1, 1, N, D );
				printf("%d\n", X);
				update( 1, 1, N, X, X + D - 1, FULL );
			}
			else {
				puts("0");
			}
		}
		else {
			scanf("%d %d", &X, &D);
			update( 1, 1, N, X, X + D - 1, CLEAR ); 
		}
	}
	return 0;
}

