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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 100005;
int N, Q;
pii P1[MAXN];
pii P2[MAXN];
int type[MAXN];
int indeg[MAXN];
int nxt[MAXN];
int resX[MAXN];
int resY[MAXN];
bool vis[MAXN];

struct event {
	int x, idx;
	int t;
	event(){}
	event(int X, int I, int T){
		x = X, idx = I, t = T;
	}
	bool operator<( const event &e ) const {
		if ( x != e.x ) return x < e.x;
		return t < e.t;
	}
};
event E[3*MAXN];

bool left( const pii &A, const pii &B, const pii &C ){
	return (1LL*(B.X-A.X)*(C.Y-A.Y) - 1LL*(C.X - A.X)*(B.Y - A.Y)) > 0LL;
}

struct seg {
	int idx;
	seg(){}
	seg( int i ){ idx = i; }
	bool operator<( const seg &s ) const {
		if ( P1[idx].X > P1[s.idx].X ) return !left( P1[s.idx], P2[s.idx], P1[idx] );
		return left( P1[idx], P2[idx], P1[s.idx] );
	}
};
// for queries
int eq[MAXN];
int idSeg[MAXN];

void dfs( int u ){
	vis[u] = true;
	int v = nxt[u];
	if ( v == -1 ){
		if ( type[u] == 2 ) resX[u] = -1, resY[u] = P1[u].Y;
		else resY[u] = -1, resX[u] = ( type[u] == 0 )? P2[u].X:P1[u].X;
		return;
	}
	if ( !vis[ v ] ) dfs( v );
	resY[u] = resY[v];
	resX[u] = resX[v];
	if ( resX[u] == -1 ){
		resX[u] = ( type[u] == 0 )? P2[u].X:P1[u].X;
	}
}

int main(){
	int e;
	while ( scanf("%d %d", &N, &Q) != EOF ){
		e = 0;
		for ( int i=0; i < N; ++i ){ 
			nxt[i] = -1;
			vis[i] = false;
			indeg[i] = 0;
			scanf("%d %d %d %d", &P1[i].X, &P1[i].Y, &P2[i].X, &P2[i].Y);
			if ( P1[i].X > P2[i].X ) swap( P1[i], P2[i] );
			if ( P1[i].Y < P2[i].Y ) type[i] = 0;
			else if (  P1[i].Y > P2[i].Y ) type[i] = 1;
			else type[i] = 2;
			E[e++] = event( P1[i].X, i, 0 );
			E[e++] = event( P2[i].X, i, 2 );
		}
		for ( int i=0; i < Q; ++i ){
			scanf("%d", eq + i );
			E[e++] = event( eq[i], i, 1 );
		}
		sort( E , E + e );
		// sweep line
		set<seg> S;
		pair<set<seg>::iterator,bool> ret;
		set<seg>::iterator it;
		int x, idx;
		for ( int i=0; i < e; ){
			do {
				x = E[i].x;
				idx = E[i].idx;			
				if ( E[i].t == 0 ){ //insert segment 
					ret = S.insert( seg(idx) );
					if ( type[idx] == 1 ){ // flow up
						it = ret.first;
						if ( it != S.end() ){
							it++;
							if ( it != S.end() ) nxt[idx] = it->idx, indeg[it->idx]++;
						}
					}
				}
				else if ( E[i].t == 1 ){ // query point
					if ( S.empty() ) idSeg[idx] = -1;
					else idSeg[idx] = S.begin()->idx;
				}
				else { // remove segment
					it = S.lower_bound( seg(idx) );
					if ( type[idx] == 0 ){
						if ( it != S.end() ){
							it++;
							if ( it != S.end() ) nxt[idx] = it->idx, indeg[it->idx]++;
							it--;
						}
					}
					S.erase(it);
				}
				i++;
			}
			while ( i < e && E[i].x == x );
		}
		for ( int i=0; i < N; ++i ) if ( indeg[i] == 0 ) dfs(i);
		for ( int i=0; i < Q; ++i ){
			if ( idSeg[i] == -1 ) printf("%d\n", eq[i]);
			else {
				idx = idSeg[i];
				printf("%d", (resX[idx]==-1)? eq[i]:resX[idx]);
				if ( resY[idx] >= 0 ) printf(" %d", resY[idx]);
				puts("");
			}
		}
	}
	return 0;
}

