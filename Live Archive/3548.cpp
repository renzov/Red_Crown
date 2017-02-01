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
#include <cassert>
#include <climits>
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< bool, int > pbi;

typedef pair< int, pbi > event;

const int MAXN = 1500;

int N;
int X[MAXN];
int Y[MAXN];
event E[2*MAXN];
int seg[4*MAXN];
int prop[4*MAXN];

void build_tree( int node, int L, int R ){
	seg[node] = prop[node] = 0;
	if ( L != R ){
		build_tree( node << 1, L , (L+R) >> 1 );
		build_tree( (node << 1)|1, ((L+R)>>1) + 1, R );
	}
}

void flush( int node, int val ){
	seg[node<<1] += val;
	seg[(node<<1)|1] += val;
	prop[node<<1] += val;
	prop[(node<<1)|1] += val;
	prop[node] = 0;
}

int update( int node, int L, int R, int l, int r, int val ){
	if ( L == R ){
		seg[node] += val;
		return seg[node];
	}
	if ( l==L && r==R ){
		prop[node] += val;
		seg[node] += val;
		return seg[node];
	}
	if ( prop[node] ) flush( node, prop[node] );
	
	int M = ( L + R ) >> 1;
	if ( r <= M ) {
		update( node << 1 , L, M, l, r, val );
		return seg[node] = max( seg[node<<1] , seg[(node<<1)|1] );	
	}
	else if ( l > M ){ 
		update( (node << 1) | 1, M+1, R, l, r, val );
		return seg[node] = max( seg[node<<1] , seg[(node<<1)|1] );	
	}
	update( node << 1 , L, M, l, M, val );
	update( (node << 1) | 1, M+1, R, M+1, r, val );
	return seg[node] = max( seg[node<<1] , seg[(node<<1)|1] );
}

int main(){
	int maxX, maxY;
	int minX, minY;
	int runs;
	int A, H;
	int S;
	int y;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &A);
		minX = minY = INT_MAX;
		maxY = maxX = 0; 
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", X+i, Y+i);
			if ( X[i] > maxX ) maxX = X[i];
			if ( X[i] < minX ) minX = X[i];
			if ( Y[i] > maxY ) maxY = Y[i];
			if ( Y[i] < minY ) minY = Y[i];
		}
		if ( !N || (max( maxX - minX, 1 )*max( maxY - minY, 1 ) <= A) ){
			printf("%d\n", N);
			continue;
		}
		int res = 0;
		S = maxY - minY;
		for ( int W=1; W <= A; ++W ){
			if ( A/W == A/(W+1) ) continue;
			H = A / W;
			// fill the events
			for ( int i=0; i < N; ++i ){
				E[2*i] = event( X[i] , pbi( false, Y[i] ) );
				E[2*i + 1] = event( X[i] + W, pbi( true, Y[i] ) ); 
			}
			sort( E, E + 2*N );
			build_tree( 1 , 0 , S );
			for ( int i=0; i < 2*N; ++i ){
				y = E[i].second.second - minY;
				if ( E[i].second.first ){ // Remove
					update( 1, 0 , S, max(y - H,0), y, -1 );
				}
				else { // Insert
					res = max( res , update( 1, 0, S, max(y - H,0) , y, 1 ) );
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}

