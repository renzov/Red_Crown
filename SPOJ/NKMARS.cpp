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
#include <numeric>

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
typedef pair< int , int > pii;

const int MAXC = 30000;
const int MAXN = 10005;
int cnt[4*MAXC] = {0};
int len[4*MAXC] = {0};
int Y1[MAXN];
int Y2[MAXN];

struct event {
	int x, idx, val;
	event(){}
	event(int X, int I, int V){
		x = X, idx = I, val = V;
	}
	bool operator<(const event &e) const {
		if ( x != e.x ) return x < e.x;
		return val > e.val;
	}
};

event E[2*MAXN];

void update( int node, int L, int R, int l, int r, int v ){
	if ( l == L && r == R ){
		cnt[node] += v;
		if ( cnt[node] > 0 ) len[node] = R - L + 1;
		else if ( L < R ) len[node] = len[node<<1] + len[(node<<1)|1];
		else len[node] = 0;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( r <= M ) update( node<<1, L, M, l, r, v );
	else if ( l > M ) update( (node<<1)|1, M+1, R, l, r, v );
	else {
		update(node<<1, L, M, l, M, v);
		update((node<<1)|1, M+1, R, M+1, r, v);
	}
	if ( cnt[node] > 0 ){
		len[node] = R - L + 1;
	}
	else {
		len[node] = len[node<<1] + len[(node<<1)|1];
	}
}

int main(){
	int N;
	int x1, x2;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d", &x1, Y1+i, &x2, Y2+i);
		E[2*i] = event( x1, i, +1 );
		E[2*i + 1] = event( x2, i, -1 );
	}
	sort( E, E + 2*N );
	x1 = 0;
	long long res = 0LL;
	int idx;
	for ( int i=0; i < 2*N; ){
		x2 = E[i].x;
		//printf("From [%d %d)\n", x1, x2);
		res += (1LL * len[1] * ( x2 - x1 ));
		//printf("res = %lld\n", res);
		do {
			idx = E[i].idx;
			//printf("idx = %d v = %d\n", idx, E[i].val);
			update( 1, 0, MAXC-1, Y1[idx], Y2[idx] - 1, E[i].val );
			//printf("len = %d\n", len[1]);
			i++;
		}
		while ( i < 2*N && x2 == E[i].x );
		x1 = x2;
	}
	printf("%lld\n", res);
	return 0;
}

