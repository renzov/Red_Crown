#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXCOORD = 2000000;
const int BASE = 1000000;
const int MAXN = 100005;

typedef pair<int,int> pii;
typedef pair< pii, int > event;

int Y1[MAXN];
int Y2[MAXN];
int W[MAXN];
event E[2*MAXN];

int maxSeg[4*MAXCOORD + 10];
int len[4*MAXCOORD + 10];
int lazy[4*MAXCOORD + 10];


inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

void build( const int &node, const int &L, const int &R ){
	len[node] =  R - L  + 1;
	lazy[node] = maxSeg[node] = 0;
	if ( L != R ){
		int M = ( L + R ) >> 1;
		build( left(node), L, M );
		build( right(node), M + 1, R );
	}
}

void propagate( const int &node ){
	int x = lazy[node];
	lazy[left(node)] += x;
	lazy[right(node)] += x;
	maxSeg[left(node)] += x;
	maxSeg[right(node)] += x;
	lazy[node] = 0;
}

void add( const int &node, const int &L, const int &R, const int &l, const int &r, const int &w ){
	if ( L == l && r == R ){
		maxSeg[node] += w;
		lazy[node] += w;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( lazy[node] ) propagate( node );
	if ( r <= M ) add( left(node), L, M, l, r, w );
	else if ( l > M ) add( right(node), M + 1, R, l, r, w );
	else {
		add( left(node), L, M, l, M, w );
		add( right(node), M + 1, R, M + 1, r, w );
	}
	// Update the value at the node
	int diff = maxSeg[left(node)] - maxSeg[right(node)];
	if ( diff > 0 ){
		maxSeg[node] = maxSeg[ left(node) ];
		len[node] = len[ left(node) ];
	}
	else if ( diff < 0 ){
		maxSeg[node] = maxSeg[ right(node) ];
		len[node] = len[ right(node) ];
	}
	else {
		maxSeg[node] = maxSeg[left(node)];
		len[node] = len[ left(node) ] + len[ right(node) ];
	}
}

void process(){
	int N;
	int x1, x2, y1, y2, w;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
		Y1[i] = y1, Y2[i] = y2, W[i] = w;
		E[ left(i) ] = event( pii( x1, 1 ), i );
		E[ right(i) ] = event( pii( x2, -1 ), i );
	}
	sort( E, E + 2*N );
	long long maxArea = 0;
	long long maxSignal = 0;
	int idx;
	int dx;
	x1 = E[0].first.first;
	for ( int i=0; i < 2*N;  ){
		idx = E[i].second;
		x2 = E[i].first.first;
		dx = x2 - x1;
		if ( dx > 0 ){
			if ( maxSeg[1] > maxSignal ){
				maxSignal = maxSeg[1];
				maxArea = 1LL * dx * len[1];
			}
			else if ( maxSeg[1] == maxSignal ){
				maxArea += ( 1LL * dx * len[1] ); 
			}
		}
		while ( i < 2*N && x2 == E[i].first.first ){
			idx = E[i].second;
			if ( Y1[idx] < Y2[idx] )
				add( 1, 0, MAXCOORD, Y1[idx] + BASE, Y2[idx] - 1 + BASE, E[i].first.second * W[idx] );
			i++;
		}
		x1 = x2;
	}
	printf("%lld %lld\n", maxSignal, maxArea);
}


int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		build( 1, 0, MAXCOORD );
		process();
	}
	return 0;
}
