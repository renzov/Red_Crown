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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXN = 40005;

int N;
pii P1[MAXN];
pii P2[MAXN];
bool type[MAXN];
int nxt[MAXN];
int sum[MAXN];
int indeg[MAXN];
struct event {
	int x, y, idx;
	bool out;
	event(){}
	event(int X, int Y, int I, bool O){
		x = X, y = Y, idx = I, out = O;
	}
	bool operator<( const event &e ) const {
		if ( x != e.x ) return x < e.x;
		if ( out != e.out ) return out < e.out;
		if ( out ) return y > e.y;
		else return y < e.y;
	}
};

event E[2*MAXN];

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

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			nxt[i] = -1; 
			indeg[i] = sum[i] = 0;
			scanf("%d %d %d %d", &P1[i].X, &P1[i].Y, &P2[i].X, &P2[i].Y);
			if ( P1[i].X > P2[i].X ) swap( P1[i] , P2[i] );
			type[i] = P1[i].Y < P2[i].Y;
			E[2*i] = event( P1[i].X , P1[i].Y , i, false );
			E[2*i + 1] = event( P2[i].X, P2[i].Y, i, true );
		}
		sort( E, E + 2*N );
		set<seg> S;
		pair<set<seg>::iterator,bool> ret;
		set<seg>::iterator it;
		// Process the segments
		int lastX, x, idx, bIdx = -1;
		for ( int i=0; i < 2*N; ){
			x = E[i].x;
			if ( bIdx >= 0 ){
				sum[bIdx] += (x - lastX);
			}
			do {
				idx = E[i].idx;
				if ( !E[i].out ){ // insertion
					ret = S.insert( seg(idx) );
					if ( type[idx] ){ // flow down in left point
						it = ret.first;
						if ( it != S.begin() ){
							it--;
							nxt[idx] = it->idx;
							indeg[it->idx]++;
						}
					}
				}
				else { // deletion
					it = S.lower_bound( seg(idx) );
					if ( !type[idx] ){
						if ( it != S.begin() ){
							it--;
							nxt[idx] = it->idx;
							indeg[it->idx]++;
							it++;
						}
					}
					S.erase(it);
				}
				i++;
			}
			while ( i < 2*N && x == E[i].x );
			lastX = x;
			if ( S.empty() ) bIdx = -1;
			else bIdx = S.rbegin()->idx;
		}
		queue<int> q;
		int u, v;
		for ( int i=0; i < N; ++i )
			if ( indeg[i] == 0 ) q.push(i);
		while ( !q.empty() ){
			u = q.front();
			q.pop();
			v = nxt[u];
			if ( v >= 0 ){
				sum[v] += sum[u];
				indeg[v]--;
				if ( indeg[v] == 0 ) q.push(v);
			}
		}
		for ( int i=0; i < N; ++i ) printf("%d\n", sum[i]);
		if (runs){ 
			puts("");
		}
	}
	return 0;
}

