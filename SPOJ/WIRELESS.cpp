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
typedef pair< int , int > pii;

const int MAXK = 1005;
int N, M, K;

int X[MAXK];
int Y[MAXK];
int W[MAXK];
int R[MAXK];

struct event {
	int x;
	int idx;
	bool in;
	event(){}
	event( int X, int I, bool t ){
		x = X, idx = I, in = t;
	}
	bool operator<(const event &e) const{
		if ( x != e.x ) return x < e.x;
		return in < e.in;
	}
};

vector<event> E[MAXK];

pii solve( vector<event> &E ){
	int maxB = 0;
	int cnt = 0;
	int B = 0;
	int x = 0, lastX = 0;
	int idx;
	for ( int i=0; i < (int)E.size(); ){
		x = E[i].x;
		// Update the maxB and cnt
		if ( B == maxB ) cnt += (x - lastX);
		else if ( B > maxB ) maxB = B, cnt = (x - lastX);

		while ( i < (int)E.size() && E[i].x == x ){
			idx = E[i].idx;
			if ( !E[i].in ){
				B -= W[idx];
			}
			else {
				B += W[idx];
			}
			i++;
		}
		lastX = x;
	}
	return pii(maxB, cnt);
}

int main(){
	int C;
	int delta;
	scanf("%d %d %d", &M, &N, &K);
	for ( int i=0; i < K; ++i ){
		scanf("%d %d %d %d", X+i, Y+i, R+i, W+i);
	}
	// Generate the intervals
	for ( int i=1; i <= N; ++i ){
		for ( int j=0; j < K; ++j ){
			C = (X[j] - i) * (X[j] - i);
			delta = R[j]*R[j] - C;
			if ( delta >= 0 ){
				delta = (int) sqrt( (double)delta );
				if ( ((delta+1)*(delta+1) + C) <= R[j]*R[j] )
					delta++;
				E[i].push_back( event( max(Y[j] - delta, 1), j, true ) );
				E[i].push_back( event( min(Y[j] + delta + 1, M + 1), j, false ) );
			}
		}
		sort( E[i].begin(), E[i].end() );
	}
	int maxB = -1;
	int cnt;
	pii res;
	for ( int i=1; i <= N; ++i ){
		res = solve( E[i] );
		if ( res.first > maxB ){
			maxB = res.first;
			cnt = res.second;
		}
		else if ( res.first == maxB ){
			cnt += res.second;
		}
	}
	printf("%d\n%d\n", maxB, cnt);
	return 0;
}
