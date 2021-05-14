#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef pair< int, int > event;
const int MAXN = 500005;

long long seg[8*MAXN];
long long total[8*MAXN];
bool lazy[8*MAXN];

int Y1[MAXN];
int Y2[MAXN];
vector<int> X;
int Y[2*MAXN];
int	V[2*MAXN];
map<int, int> idY;
vector<event> E;

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return ( x << 1 ) | 1; }

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){
		total[node] = V[L];
		seg[node] = 0;
		lazy[node] = false;
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	
	total[node] = total[ left(node) ] + total[ right(node) ];
	seg[node] = seg[ left(node) ] + seg[ right(node) ];
	lazy[node] = false;
}

void propagate( const int &node ){
	int l = left(node);
	int r = right(node);
	seg[l] = total[l] - seg[l];
	seg[r] = total[r] - seg[r];
	lazy[l] ^= true;
	lazy[r] ^= true;
	lazy[node] = false;
}

void invert( const int &node, const int &L, const int &R, const int &l, const int &r ){
	//printf("In node %d\n", node);
	if ( l == L && r == R ){
		seg[node] = total[node] - seg[node];
		lazy[node] ^= true;
		//printf("sum[%d] = %lld\n", node, seg[node]);
		return;
	}
	
	if ( lazy[node] ) propagate( node );

	int M = ( L + R ) >> 1;
	
	if ( r <= M ) invert( left(node), L, M, l, r );
	else if ( l > M ) invert( right(node), M + 1, R, l, r );
	else {
		invert( left(node), L, M, l, M );
		invert( right(node), M + 1, R, M + 1, r );
	}
	// build up the information
	//puts("Going up recursion");
	seg[node] = seg[ left(node) ] + seg[ right(node) ];	
	//printf("sum[%d] = %lld\n", node, seg[node]);
}

int main(){
	int x1, x2, y1, y2;
	int N;
	int m = 0;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		X.push_back(x1), X.push_back(x2);
		Y[m++] = y1, Y[m++] = y2;
		Y1[i] = y1, Y2[i] = y2;
		// Open event
		E.push_back( event( x1 , i ) );
		// Close event
		E.push_back( event( x2 , i ) );
	}
	
	sort( Y, Y + m );
	sort( E.begin(), E.end() );

	m = unique( Y, Y + m ) - Y;
	for ( int i = 0; i < m; ++i ) 
		idY[ Y[i] ] = i;

	//for ( int i=0; i < m; ++i )
	//	printf("%d ", Y[i]);
	//puts("");

	// The length between each point
	for ( int i=0;  i < m - 1; ++i )
		V[i] = Y[i + 1] - Y[i];

	//for ( int i=0; i < m - 1; ++i )
	//	printf("%d ", V[i]);
	//puts("");
	// Initialize segment tree
	build( 1, 0, m - 2 );

	long long res = 0;
	int x, idx;
	int lastX = -1;

	int M = (int) E.size();
	for ( int i=0; i < M; ){
		x = E[i].first;
		// find the answer until now
		if ( lastX >= 0 ){
			//printf("deltaX = %d - sum %lld\n", x - lastX, seg[1]);
			res += (( x - lastX ) * seg[1]); 
		}
		while ( i < M && E[i].first == x ){
			idx = E[i].second;
			y1 = idY[ Y1[ idx ] ];
			y2 = idY[ Y2[ idx ] ];
			//printf("invert [%d, %d]\n", y1, y2 - 1);
			invert( 1, 0, m - 2, y1, y2 - 1 );
			i++;
		}
		lastX = x;
		//puts("");
	}
	printf("%lld\n", res);
	return 0;
}
