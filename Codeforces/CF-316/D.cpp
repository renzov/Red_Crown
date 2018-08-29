#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 500005;
typedef pair<int,int> pii;
typedef pair< int , pii > event;

int seg[4*MAXN];

int N;
vector<int> T[MAXN];
int val[MAXN];
int dfsnum;
int L[MAXN];
int left[MAXN];
int right[MAXN];
bool res[MAXN];
// Number of events = 2*N + Q
event E[3*MAXN];
int M; // Number of events 
void dfs( const int &u ){
	int v;
	left[u] = right[u] = dfsnum++;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		L[v] = L[u] + 1;
		dfs( v );
		right[u] = right[v];
	}
}

void update( const int &node, const int &B, const int &R, const int &v, const int &p ){
	if ( B == R ){
		seg[ node ] = v;
		return;
	}
	int mid = ( B + R ) >> 1;
	if ( p <= mid ) update( node<<1 , B, mid, v, p );
	else update( (node<<1)|1, mid + 1, R, v, p );
	seg[node] = seg[node<<1] ^ seg[ (node<<1)|1 ];
}

int query( const int &node, const int &B, const int &R, const int &l, const int &r ){
	if ( l == B && r == R ) return seg[node];
	int mid = ( B + R ) >> 1;
	if ( r <= mid ) return query( node<<1, B, mid, l, r );
	if ( l > mid ) return query( (node<<1)|1, mid + 1, R, l, r );
	return query( node<<1, B, mid, l, mid) ^ query( (node<<1)|1, mid + 1, R, mid + 1, r );
}
	
int main(){	
	int Q;
	int u, h, t;
	int r;
	char c;
	
	scanf("%d %d", &N, &Q);
	for ( int i=2; i <= N; ++i ){
		scanf("%d", &u);
		T[u].push_back(i);
	}
	dfsnum = 1;
	L[1] = 1;
	dfs( 1 );
	for ( int i=1; i <= N; ++i ){
		scanf(" %c", &c);
		val[i] = 1 << (c - 'a');
		E[M++] = event( L[i] , pii( -1 , i )  );
		E[M++] = event( L[i] , pii( 1 + Q , i ) );
	}
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", &u, &h);
		E[M++] = event( h , pii( i , u ) );
	}
	sort( E, E + M );
	for ( int i=0; i < M; ){
		h = E[i].first;
		while ( i < M && E[i].first == h ){
			t = E[i].second.first;
			u = E[i].second.second;
			if ( t < 0 ){ // insertion
				update( 1, 1, N, val[u], left[u] );
			}
			else if ( t > Q ){ // deletion
				update( 1, 1, N, 0, left[u] );
			}
			else { // Query
				r = query( 1, 1, N, left[u], right[u] );
				res[ t ] = __builtin_popcount( r ) <= 1;
			}
			i++;
		} 
	}
	for ( int i=0; i < Q; ++i )
		puts( res[i]? "Yes":"No" );		
	return 0;
}
