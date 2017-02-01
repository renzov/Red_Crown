#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair<int,int> pii;
typedef pair< int , pii > event;

const int MAXN = 70005;
vector<int> G[MAXN];
int seg[4*MAXN];
event E[2*MAXN];
int start[MAXN];
int End[MAXN];
int depth[MAXN];
int res[MAXN];
int num;

void dfs(int u, int d){ // subtree goes from start[u] to end[u] - 1
	start[u] = num++;
	depth[u] = d;
	for ( int i=0;i < (int)G[u].size(); ++i )
		dfs( G[u][i], d + 1 );
	End[u] = num;
}

void build( int node, int L, int R ){
	seg[node] = -1;
	if ( L==R ) return;
	int M = ( L + R ) >> 1;
	build( node<<1, L, M );
	build( (node<<1)|1, M+1, R );
}

int query( int node, int L, int R, int l, int r ){
	if ( L==l && R==r ) return seg[node];
	int M = (L+R)>>1;
	if ( r <= M ) return query( node<<1, L, M, l, r );
	if ( l > M ) return query( (node<<1)|1, M+1, R, l, r );
	return max(query(node<<1,L,M,l,M),query((node<<1)|1,M+1,R,M+1,r));
}

void update( int node, int L, int R, int p, int v ){
	if ( L == R ){
		seg[node] = v;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( p <= M ) update(node<<1, L, M, p, v );
	else update((node<<1)|1, M+1, R, p, v );
	seg[node] = max(seg[node<<1], seg[(node<<1)|1]);
}

int main(){
	int runs;
	int u, b, e;
	int M; //number of events
	int d;
	int N;
	scanf("%d",&runs);
	while ( runs-- ){
		M = 0;
		scanf("%d", &N);
		for ( int v=0; v<N ; ++v ){
			scanf("%d %d %d", &u, &b, &e);
			if ( u >= 0 ) G[u].push_back(v);
			E[M++] = event( b, pii(-1,v) );
			E[M++] = event( e, pii(1,v) );
		}
		num = 0;
		dfs( 0, 0 );
		build( 1, 0, N - 1 );
		assert( num == N );
		sort( E, E + M );
		for ( int i=0; i < M ; ++i ){
			//printf("process year %d ",E[i].first);
			u = E[i].second.second;
			if ( E[i].second.first > 0 ){ // dead
				//printf("%d died\n", u);
				d = query( 1, 0, N - 1, start[u], End[u]-1 );
				if ( d <= depth[u] ) res[u] = 0;
				else res[u] = d - depth[u];
			}
			else { // born
				//printf("%d born\n", u);
				update( 1, 0, N-1, start[u], depth[u] );
			}
		}
		printf("%d", res[0]);
		for ( int i=1; i<N; ++i ) printf(" %d", res[i]);
		puts("");
		if ( runs ){
			for ( int i=0; i < N; ++i )
				G[i].clear();
		}
	}
	return 0;
}

